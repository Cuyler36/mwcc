"""Regression checks for relocation resolution across imported source units."""
import struct
import unittest
from tempfile import TemporaryDirectory
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

from compare import resolve_function, source_data, write_translation_unit, read_object, function_section


class Image:
    image_base = 0

    def __init__(self, original_string):
        self.data = bytearray(0x4000)
        self.data[0x1000:0x1006] = b'\x68' + struct.pack('<I', 0x2000) + b'\xc3'
        self.data[0x2000:0x2000 + len(original_string)] = original_string
        self.data[0x3000:0x300f] = b'Targets.c\0this\0\0'

    def read(self, address, size):
        if address < 0 or address + size > len(self.data):
            raise ValueError('outside image')
        return bytes(self.data[address:address + size])

    def contains(self, address, payload):
        return self.read(address, len(payload)) == payload

    def find(self, payload, limit=2):
        hits, position = [], 0
        while len(hits) < limit:
            position = self.data.find(payload, position)
            if position < 0:
                break
            hits.append(position)
            position += 1
        return hits


class LiteralResolutionTests(unittest.TestCase):
    def resolve(self, original_string, bindings):
        symbols = {
            0: dict(name='_function', section=1, value=0, type=0x20, storage=2),
            1: dict(name='_@33', section=2, value=0, type=0, storage=3),
        }
        sections = [
            dict(data=b'\x68\0\0\0\0\xc3', relocs=[(1, 1, 6)], code=True),
            dict(data=b'Targets.c\0this\0\0', relocs=[], code=False),
        ]
        body, _ = resolve_function(symbols, sections, '_function', 0x1000,
                                   bindings, Image(original_string), 6)
        return struct.unpack_from('<I', body, 1)[0]

    def test_original_string_survives_pool_regrouping(self):
        self.assertEqual(self.resolve(b'Targets.c\0', {}), 0x2000)

    def test_another_objects_local_ordinal_cannot_override_literal(self):
        self.assertEqual(self.resolve(b'Targets.c\0', {'_@33': 0x3500}), 0x2000)

    def test_changed_string_does_not_reuse_original_operand(self):
        self.assertEqual(self.resolve(b'Changed.c\0', {}), 0x3000)

    def resolve_zero_storage(self, original_operand):
        class BssImage(Image):
            def find(self, needle, limit=2):
                return [0x3500]  # An unrelated unique file-backed zero block.

            def section_for_address(self, address):
                if 0x2000 <= address < 0x3000:
                    return SimpleNamespace(name='.bss', virtual_address=0x2000, virtual_size=0x1000,
                                           file_offset=0, file_size=0, characteristics=0xc0000080)
                raise ValueError('outside allocated data')

        pe = BssImage(b'\0' * 8)
        struct.pack_into('<I', pe.data, 0x1001, original_operand)
        symbols = {0: dict(name='_function', section=1, value=0, type=0x20, storage=2),
                   1: dict(name='_storage', section=2, value=0, type=0, storage=3)}
        sections = [dict(data=b'\x68\0\0\0\0\xc3', relocs=[(1, 1, 6)], code=True),
                    dict(data=bytes(8), relocs=[], code=False, flags=0xc0000080)]
        return resolve_function(symbols, sections, '_function', 0x1000, {}, pe, 6)[0]

    def test_zero_storage_uses_bounded_original_reference(self):
        self.assertEqual(struct.unpack_from('<I', self.resolve_zero_storage(0x2000), 1)[0], 0x2000)

    def test_unmapped_address_is_not_treated_as_zero_storage(self):
        with self.assertRaises(ValueError):
            self.resolve_zero_storage(0x4000)


class AnonymousDataTests(unittest.TestCase):
    def fixture(self, invalid=False, unreferenced=False, missing_fixup=False, writable=False,
                switch_label=False):
        class TableImage(Image):
            def section_for_address(self, address):
                if 0x2000 <= address < 0x3000:
                    return SimpleNamespace(name='.data' if writable else '.rdata',
                                           virtual_address=0x2000, virtual_size=0x1000,
                                           file_offset=0x2000, file_size=0x1000,
                                           characteristics=0xc0000040 if writable else 0x40000040)
                raise ValueError('outside data')
        pe = TableImage(b'')
        symbols, sections, rows, fixups = {}, [], [], set()
        for i in range(2):
            address, table_address = 0x1000 + i * 0x100, 0x2000 + i * 0x100
            function_index, text_index, table_index = i * 3, i * 3 + 1, i * 3 + 2
            symbols[function_index] = dict(name=f'_f{i}', section=i+1, value=0, type=0x20, storage=2)
            symbols[text_index] = dict(name='.text', section=i+1, value=0, type=0, storage=3)
            symbols[table_index] = dict(name='.rdata', section=i+3, value=0, type=0, storage=3)
            code = b'\x68\0\0\0\0\xc3' + bytes([0xc3])*6
            sections.append(dict(name='.text', data=code, relocs=[(1, table_index, 6)], code=True, flags=0x60000020))
            pe.data[address:address+len(code)] = b'\x68'+struct.pack('<I',table_address)+code[5:]
            rows.append(dict(symbol=f'_f{i}', address=address, size=len(code)))
            fixups.add(address+1)
            for j in range(6):
                struct.pack_into('<I', pe.data, table_address+j*4, address+6+j)
                fixups.add(table_address+j*4)
        for i in range(2):
            sections.append(dict(name='.rdata', data=struct.pack('<6I', *range(6,12)),
                                 relocs=[(j*4, i*3+1, 6) for j in range(6)], code=False, flags=0x40000040))
        if invalid:
            symbols[6] = dict(name='_unbound', section=0, value=0, type=0, storage=2)
            sections[2]['relocs'][0] = (0, 6, 6)
        if unreferenced:
            sections.append(dict(name='.rdata', data=b'unclaimed', relocs=[], code=False, flags=0x40000040))
        if missing_fixup:
            fixups.remove(0x2000)
        if switch_label:
            for i in range(2):
                symbols[6+i] = dict(name='.sw$1508', section=i+3, value=4, type=0, storage=3)
                sections[i]['relocs'] = [(1, 6+i, 6)]
                struct.pack_into('<I', pe.data, 0x1001+i*0x100, 0x2004+i*0x100)
        return pe, symbols, sections, rows, fixups

    def run_fixture(self, **options):
        pe, symbols, sections, rows, fixups = self.fixture(**options)
        claims = []
        def config_read(path, *args, **kwargs):
            return '[]' if path.name == 'functions.json' else '{}'
        with patch.object(Path, 'read_text', config_read), patch.object(Path, 'write_text'), \
                patch.object(Path, 'mkdir'), patch('compare.version_config', return_value={}), \
                patch('compare.base_relocations', return_value=fixups):
            target, base, complete = source_data('test', 'source.c', rows, symbols, sections, pe, claims)
        return target, base, complete, claims, pe

    def test_two_anonymous_tables_use_symbol_indices_and_local_code_labels(self):
        target, base, complete, claims, pe = self.run_fixture()
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000,0x2018), (0x2100,0x2118)])
        expected = pe.read(0x2000,24) + pe.read(0x2100,24)
        self.assertEqual(bytes(target[0]['data']), expected)
        self.assertEqual(bytes(base[0]['data']), expected)

    def test_unbound_table_relocation_prevents_claim(self):
        target, base, complete, claims, _ = self.run_fixture(invalid=True)
        self.assertFalse(complete)
        self.assertEqual(claims, [(0x2100,0x2118)])
        self.assertEqual(len(target[0]['data']),24)
        self.assertEqual(len(base[0]['data']),48)

    def test_unreferenced_anonymous_section_remains_unassigned(self):
        _, _, complete, claims, _ = self.run_fixture(unreferenced=True)
        self.assertFalse(complete)
        self.assertEqual(len(claims),2)

    def test_table_fixup_mismatch_prevents_claim(self):
        _, _, complete, claims, _ = self.run_fixture(missing_fixup=True)
        self.assertFalse(complete)
        self.assertEqual(claims, [(0x2100,0x2118)])

    def test_anonymous_switch_label_recovers_section_base(self):
        target, base, complete, claims, pe = self.run_fixture(switch_label=True)
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000,0x2018), (0x2100,0x2118)])
        self.assertEqual(bytes(target[0]['data']), pe.read(0x2000,24)+pe.read(0x2100,24))
        self.assertEqual(target[0]['data'], base[0]['data'])

    def test_table_category_mismatch_prevents_claim(self):
        target, _, complete, claims, _ = self.run_fixture(writable=True)
        self.assertFalse(complete)
        self.assertEqual(claims, [])
        self.assertEqual(target, [])


class TranslationUnitTests(unittest.TestCase):
    def test_bss_ignores_nonzero_raw_pointer(self):
        Path('build').mkdir(exist_ok=True)
        with TemporaryDirectory(dir='build', prefix='test-compare-') as directory:
            path = Path(directory) / 'bss.obj'
            write_translation_unit(path, [('_function', b'\xc3')], [
                dict(name='.bss', data=bytes(1), symbols=[('_storage', 0, 1, False)], flags=0xc0000080)])
            data = bytearray(path.read_bytes())
            # Simulate CW94's BSS pointer into another section's raw payload.
            struct.pack_into('<I', data, 20 + 40 + 20, 20 + 2 * 40)
            path.write_bytes(data)
            _, sections = read_object(path)
            self.assertEqual(sections[1]['data'], b'\0')

    def test_consolidates_text_and_preserves_data_classes(self):
        Path('build').mkdir(exist_ok=True)
        with TemporaryDirectory(dir='build', prefix='test-compare-') as directory:
            self.assertTrue(Path(directory).resolve().is_relative_to(Path('build').resolve()))
            path = Path(directory) / 'unit.obj'
            write_translation_unit(path, [('_first', b'\x31\xc0\xc3'), ('_second', b'\xc3')], [
                dict(name='.rdata', data=b'read\0', symbols=[('_literal', 0, 5, False)], flags=0x40000040),
                dict(name='.data', data=b'\x01\0\0\0', symbols=[('_value', 0, 4, False)], flags=0xc0000040),
                dict(name='.bss', data=bytes(16), symbols=[('_buffer', 0, 16, False)], flags=0xc0000080),
            ])
            symbols, sections = read_object(path)
            self.assertEqual([s['name'] for s in sections], ['.text', '.rdata', '.data', '.bss'])
            self.assertEqual(sections[0]['data'], b'\x31\xc0\xc3\xc3')
            self.assertEqual(sections[3]['data'], bytes(16))
            self.assertEqual(struct.unpack_from('<I', path.read_bytes(), 20 + 3 * 40 + 20)[0], 0)
            for name, expected in [('_first', b'\x31\xc0\xc3'), ('_second', b'\xc3')]:
                section, start, end = function_section(symbols, sections, name)
                self.assertEqual(section['data'][start:end], expected)


if __name__ == '__main__':
    unittest.main()
