"""Regression checks for relocation resolution across imported source units."""
import struct
import unittest
from collections import defaultdict
from tempfile import TemporaryDirectory
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

from compare import (resolve_function, source_data, write_translation_unit, read_object,
                     function_section, table_literal_references)


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


class CommonDataTests(unittest.TestCase):
    def run_fixture(self, bindings=None, global_bindings=None, referenced=False, ambiguous=False,
                    size=16, category='.bss', overlap=False, fixups=()):
        class CommonImage(Image):
            def section_for_address(self, address):
                if 0x2000 <= address < 0x2100:
                    return SimpleNamespace(name=category, virtual_address=0x2000, virtual_size=0x100,
                                           file_offset=0x2000, file_size=0 if category == '.bss' else 0x100,
                                           characteristics=0xc0000080 if category == '.bss' else 0xc0000040)
                raise ValueError('outside BSS')
        pe = CommonImage(b'')
        symbols = {0: dict(name='_buffer', section=0, value=size, storage=2, type=0)}
        sections, rows = [], []
        if referenced:
            for i in range(2 if ambiguous else 1):
                address = 0x1000 + i * 0x100
                symbols[i + 1] = dict(name=f'_f{i}', section=i + 1, value=0, type=0x20, storage=2)
                sections.append(dict(name='.text', data=b'\x68\0\0\0\0\xc3',
                                     relocs=[(1, 0, 6)], code=True, flags=0x60000020))
                pe.data[address:address + 6] = b'\x68' + struct.pack('<I', 0x2000 + i * 0x40) + b'\xc3'
                rows.append(dict(symbol=f'_f{i}', address=address, size=6))
        if overlap:
            symbols[10] = dict(name='_overlap', section=0, value=16, storage=2, type=0)
            bindings = dict(bindings or {}, _overlap='0x2008')
        claims = []
        def config_read(path, *args, **kwargs):
            return '[]' if path.name == 'functions.json' else __import__('json').dumps(global_bindings or {})
        with patch.object(Path, 'read_text', config_read), patch.object(Path, 'write_text'), \
                patch.object(Path, 'mkdir'), patch('compare.version_config',
                return_value={'source_bindings': {'source.c': bindings or {}}}), \
                patch('compare.base_relocations', return_value=fixups):
            target, base, complete = source_data('test', 'source.c', rows, symbols, sections, pe, claims)
        return target, base, complete, claims

    def test_common_size_becomes_allocated_bss_not_symbol_offset(self):
        target, base, complete, claims = self.run_fixture(bindings={'_buffer': '0x2000'})
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000, 0x2010)])
        self.assertEqual(target, base)
        self.assertEqual(base[0]['symbols'], [('_buffer', 0, 16, False)])
        self.assertEqual(base[0]['data'], bytes(16))

    def test_common_address_can_come_from_bounded_original_operand(self):
        _, _, complete, claims = self.run_fixture(referenced=True)
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000, 0x2010)])

    def test_global_name_only_cannot_claim_common(self):
        target, base, complete, claims = self.run_fixture(global_bindings={'_buffer': '0x2000'})
        self.assertFalse(complete)
        self.assertEqual(target, [])
        self.assertEqual(claims, [])
        self.assertEqual(len(base[0]['data']), 16)

    def test_common_full_extent_must_fit_bss(self):
        _, _, complete, claims = self.run_fixture(bindings={'_buffer': '0x20f8'})
        self.assertFalse(complete)
        self.assertEqual(claims, [])

    def test_common_cannot_claim_initialized_data(self):
        _, _, complete, claims = self.run_fixture(bindings={'_buffer': '0x2000'}, category='.data')
        self.assertFalse(complete)
        self.assertEqual(claims, [])

    def test_both_overlapping_common_allocations_remain_unclaimed(self):
        _, _, complete, claims = self.run_fixture(bindings={'_buffer': '0x2000'}, overlap=True)
        self.assertFalse(complete)
        self.assertEqual(claims, [])

    def test_conflicting_original_operands_cannot_establish_common_ownership(self):
        _, _, complete, claims = self.run_fixture(referenced=True, ambiguous=True)
        self.assertFalse(complete)
        self.assertEqual(claims, [])

    def test_common_with_pe_fixup_is_rejected(self):
        _, _, complete, claims = self.run_fixture(bindings={'_buffer': '0x2000'}, fixups=[0x2004])
        self.assertFalse(complete)
        self.assertEqual(claims, [])


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


class BoundTableLiteralTests(unittest.TestCase):
    def run_fixture(self, invalid=None):
        class DataImage(Image):
            def section_for_address(self, address):
                if 0x2000 <= address < 0x3000:
                    return SimpleNamespace(name='.data', virtual_address=0x2000, virtual_size=0x1000,
                                           file_offset=0x2000, file_size=0x1000, characteristics=0xc0000040)
                raise ValueError('outside data')
        pe = DataImage(b'')
        symbols = {0: dict(name='_table', section=1, value=0, storage=3, type=0)}
        sections = [dict(name='.data', data=bytes(24) + b'MARK',
                         relocs=[(i*4, index, 6) for i, index in enumerate([1, 2, 3, 2, 1, 4])],
                         code=False, flags=0xc0000040)]
        payloads = [b'A\0\0\0', bytes(4), b'shared\0\0', b'B\0\0\0']
        for index, payload in enumerate(payloads, 1):
            # Two different symbols have the same COFF-local ordinal and section name.
            symbols[index] = dict(name='@1' if index in (1, 4) else '@'+str(index),
                                  section=index+1, value=0, storage=3, type=0)
            sections.append(dict(name='.data', data=payload, relocs=[], code=False, flags=0xc0000040))
            pe.data[0x2200+index*0x20:0x2200+index*0x20+len(payload)] = payload
        pointers = [0x2220, 0x2240, 0x2260, 0x2240, 0x2220, 0x2280]
        pe.data[0x2000:0x201c] = struct.pack('<6I', *pointers) + b'MARK'
        fixups = {0x2000+i*4 for i in range(6)}
        bindings = {'_table': '0x2000'}
        if invalid == 'table_bytes':
            pe.data[0x201b] ^= 1
        elif invalid == 'missing_fixup':
            fixups.remove(0x2004)
        elif invalid == 'extra_fixup':
            fixups.add(0x2018)
        elif invalid == 'payload':
            pe.data[0x2261] ^= 1
        elif invalid == 'padding':
            pe.data[0x2223] = 1
        elif invalid == 'pointed_fixup':
            fixups.add(0x2240)
        elif invalid == 'pointed_relocation':
            sections[2]['relocs'] = [(0, 1, 6)]
        elif invalid == 'category':
            sections[2]['flags'] = 0x40000040
        elif invalid == 'bounds':
            struct.pack_into('<I', pe.data, 0x2000, 0x2ffe)
        elif invalid == 'kind':
            sections[0]['relocs'][0] = (0, 1, 7)
        elif invalid == 'unbound':
            bindings = {}
        elif invalid == 'ambiguous':
            pe.data[0x2300:0x2304] = payloads[0]
            struct.pack_into('<I', pe.data, 0x2010, 0x2300)
        elif invalid == 'cross_table_ambiguity':
            symbols[5] = dict(name='_other_table', section=6, value=0, storage=3, type=0)
            sections.append(dict(name='.data', data=bytes(4), relocs=[(0, 1, 6)],
                                 code=False, flags=0xc0000040))
            bindings['_other_table'] = '0x2100'
            pe.data[0x2300:0x2304] = payloads[0]
            struct.pack_into('<I', pe.data, 0x2100, 0x2300)
            fixups.add(0x2100)
        rows = []
        if invalid == 'partial_function':
            symbols[5] = dict(name='_function', section=6, value=0, storage=2, type=0x20)
            symbols[6] = dict(name='@99', section=7, value=0, storage=3, type=0)
            symbols[7] = dict(name='_unbound_call', section=0, value=0, storage=2, type=0x20)
            code = b'\x68' + bytes(4) + b'\xe8' + bytes(4) + b'\xc3'
            sections.extend([dict(name='.text', data=code, relocs=[(1, 6, 6), (6, 7, 20)],
                                  code=True, flags=0x60000020),
                             dict(name='.data', data=b'LOG\0', relocs=[], code=False, flags=0xc0000040)])
            pe.data[0x2400:0x2404] = b'LOG\0'
            pe.data[0x1000:0x100b] = b'\x68' + struct.pack('<I', 0x2400) + code[5:]
            rows = [dict(symbol='_function', address=0x1000, size=len(code))]
        claims, written = [], []
        def config_read(path, *args, **kwargs):
            return '[]' if path.name == 'functions.json' else '{}'
        with patch.object(Path, 'read_text', config_read), \
                patch.object(Path, 'write_text', lambda self, text: written.append(text)), \
                patch.object(Path, 'mkdir'), patch('compare.version_config',
                return_value={'source_bindings': {'source.c': bindings}}), \
                patch('compare.base_relocations', return_value=fixups):
            target, base, complete = source_data('test', 'source.c', rows, symbols, sections, pe, claims)
        return complete, claims, __import__('json').loads(written[-1]), target, base

    def test_full_table_proves_empty_shared_and_duplicate_ordinal_literals(self):
        complete, claims, evidence, target, base = self.run_fixture()
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000, 0x201c), (0x2220, 0x2224), (0x2240, 0x2244),
                                  (0x2260, 0x2268), (0x2280, 0x2284)])
        self.assertEqual(target[0]['data'], base[0]['data'])
        self.assertTrue(all(e['method'] == 'verified bound data table' for e in evidence[1:]))

    def test_invalid_proof_does_not_attribute_any_pointed_allocation(self):
        for invalid in ['table_bytes', 'missing_fixup', 'extra_fixup', 'payload', 'padding',
                        'pointed_fixup', 'pointed_relocation', 'category', 'bounds', 'kind',
                        'unbound', 'ambiguous']:
            with self.subTest(invalid=invalid):
                complete, claims, _, _, _ = self.run_fixture(invalid)
                self.assertFalse(complete)
                self.assertFalse(any(start >= 0x2200 for start, end in claims))

    def test_unresolved_call_does_not_discard_verified_data_operand(self):
        complete, claims, evidence, _, _ = self.run_fixture('partial_function')
        self.assertTrue(complete)
        self.assertIn((0x2400, 0x2404), claims)
        self.assertEqual(evidence[-1]['method'], 'resolved function reference')

    def test_conflicting_independently_anchored_tables_leave_literal_unassigned(self):
        complete, claims, _, _, _ = self.run_fixture('cross_table_ambiguity')
        self.assertFalse(complete)
        self.assertNotIn((0x2220, 0x2224), claims)
        self.assertNotIn((0x2300, 0x2304), claims)


class CRTInitializerTests(unittest.TestCase):
    def fixture(self, invalid=None):
        class CRTImage(Image):
            def section_for_address(self, address):
                if 0x2000 <= address < 0x3000:
                    return SimpleNamespace(name='.data' if invalid == 'category' else '.CRT',
                                           virtual_address=0x2000,
                                           virtual_size=2 if invalid == 'bounds' else 0x1000,
                                           file_offset=0x2000, file_size=0x1000,
                                           characteristics=0xc0000040)
                raise ValueError('outside CRT')
        pe = CRTImage(b'')
        symbols = {0: dict(name='_initializer', section=1, value=0, type=0x20, storage=2),
                   1: dict(name='.text', section=1, value=0, type=0, storage=3),
                   2: dict(name='.CRT$XCU', section=2, value=0, type=0, storage=3)}
        sections = [dict(name='.text', data=b'\xc3\xc3', relocs=[], code=True, flags=0x60000020),
                    dict(name='.CRT$XCU', data=bytes(4), relocs=[(0, 1, 6)],
                         code=False, flags=0xc0300040)]
        pe.data[0x1000:0x1002] = b'\xc3\xc3'
        struct.pack_into('<I', pe.data, 0x2000, 0x1000)
        rows = [dict(symbol='_initializer', address=0x1000, size=2)]
        fixups = {0x2000}
        if invalid == 'ambiguous':
            struct.pack_into('<I', pe.data, 0x2010, 0x1000)
            fixups.add(0x2010)
        elif invalid == 'missing_fixup':
            fixups.clear()
        elif invalid == 'extra_fixup':
            fixups.add(0x2001)
        elif invalid == 'interior_entry':
            sections[1]['data'] = struct.pack('<I', 1)
            struct.pack_into('<I', pe.data, 0x2000, 0x1001)
        elif invalid == 'wrong_pointer':
            struct.pack_into('<I', pe.data, 0x2000, 0x1100)
        elif invalid == 'relocation_kind':
            sections[1]['relocs'] = [(0, 1, 7)]
        elif invalid == 'unmapped_entry':
            rows = []
        elif invalid == 'ordinary_data':
            sections[1]['name'] = '.data'
        elif invalid == 'two_entries':
            symbols[3] = dict(name='_second', section=1, value=1, type=0x20, storage=2)
            rows = [dict(symbol='_initializer', address=0x1000, size=1),
                    dict(symbol='_second', address=0x1100, size=1)]
            sections[1]['data'] = struct.pack('<2I', 0, 1)
            sections[1]['relocs'].append((4, 1, 6))
            struct.pack_into('<I', pe.data, 0x2004, 0x1100)
            fixups.add(0x2004)
        claims, written = [], []
        def config_read(path, *args, **kwargs):
            return '[]' if path.name == 'functions.json' else '{}'
        with patch.object(Path, 'read_text', config_read), \
                patch.object(Path, 'write_text', lambda self, text: written.append(text)), \
                patch.object(Path, 'mkdir'), patch('compare.version_config', return_value={}), \
                patch('compare.base_relocations', return_value=fixups):
            target, base, complete = source_data('test', 'source.cpp', rows, symbols, sections, pe, claims)
        return complete, claims, __import__('json').loads(written[-1]), target, base

    def test_unique_initializer_pointer_is_attributed_and_keeps_crt_section(self):
        complete, claims, evidence, target, base = self.fixture()
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000, 0x2004)])
        self.assertEqual(target[0]['name'], '.CRT')
        self.assertEqual(base[0]['name'], '.CRT')
        self.assertEqual(target[0]['data'], base[0]['data'])
        self.assertEqual(evidence[0]['method'], 'unique relocated CRT initializer entries')

    def test_all_initializer_entries_must_match(self):
        complete, claims, _, target, base = self.fixture('two_entries')
        self.assertTrue(complete)
        self.assertEqual(claims, [(0x2000, 0x2008)])
        self.assertEqual(target[0]['data'], base[0]['data'])

    def test_ambiguous_or_incomplete_identity_stays_unassigned(self):
        for invalid in ['ambiguous', 'missing_fixup', 'extra_fixup', 'interior_entry',
                        'wrong_pointer', 'relocation_kind', 'unmapped_entry', 'ordinary_data',
                        'category', 'bounds']:
            with self.subTest(invalid=invalid):
                complete, claims, _, target, _ = self.fixture(invalid)
                self.assertFalse(complete)
                self.assertFalse(claims)
                self.assertFalse(target)


class MixedTableLiteralTests(unittest.TestCase):
    def fixture(self, invalid=None):
        class MixedImage(Image):
            def section_for_address(self, address):
                for name, start, flags in [('.text', 0x1000, 0x60000020),
                                           ('.data', 0x2000, 0xc0000040)]:
                    if start <= address < start + 0x1000:
                        return SimpleNamespace(name=name, virtual_address=start, virtual_size=0x1000,
                                               file_offset=start, file_size=0x1000, characteristics=flags)
                raise ValueError('outside image')
        pe = MixedImage(b'')
        symbols = {
            0: dict(name='_table', section=1, value=0, storage=3, type=0),
            1: dict(name='@1', section=2, value=0, storage=3, type=0),
            2: dict(name='_callback@4', section=0, value=0, storage=2, type=0x20),
            3: dict(name='_external', section=0, value=0, storage=2, type=0),
            4: dict(name='_referenced_global', section=0, value=0, storage=2, type=0),
        }
        sections = [
            dict(name='.data', data=struct.pack('<4I', 0, 0, 4, 8) + b'TAIL', code=False,
                 flags=0xc0000040, relocs=[(i*4, i+1, 6) for i in range(4)]),
            dict(name='.data', data=b'local\0\0\0', code=False, flags=0xc0000040, relocs=[]),
        ]
        pe.data[0x2000:0x2014] = struct.pack('<4I', 0x2200, 0x1100, 0x2304, 0x2408) + b'TAIL'
        pe.data[0x2200:0x2208] = b'local\0\0\0'
        addresses = {'_table': 0x2000, '_callback': 0x1100, '_external': 0x2300}
        references = defaultdict(set, {4: {0x2400}})
        fixups = {0x2000, 0x2004, 0x2008, 0x200c}
        if invalid == 'unknown':
            addresses.pop('_external')
        elif invalid == 'named_reference_conflict':
            references[3] = {0x2310}
        elif invalid == 'two_references':
            references[4].add(0x2410)
        elif invalid == 'canonical_name_conflict':
            addresses['_callback@4'] = 0x1110
        elif invalid == 'wrong_addend':
            sections[0]['data'] = struct.pack('<4I', 0, 0, 5, 8) + b'TAIL'
        elif invalid == 'wrong_pointer':
            struct.pack_into('<I', pe.data, 0x2004, 0x1110)
        elif invalid == 'outside_image':
            addresses['_external'] = 0x5000
            struct.pack_into('<I', pe.data, 0x2008, 0x5004)
        elif invalid == 'outside_virtual_extent':
            addresses['_external'] = 0x2fff
            struct.pack_into('<I', pe.data, 0x2008, 0x3003)
        elif invalid == 'ordinary_missing_fixup':
            fixups.remove(0x2008)
        elif invalid == 'extra_fixup':
            fixups.add(0x2010)
        elif invalid == 'tail':
            pe.data[0x2010] ^= 1
        elif invalid == 'literal_payload':
            pe.data[0x2206] = 1
        elif invalid == 'literal_reference_conflict':
            references[1] = {0x2210}
        return table_literal_references(symbols, sections, pe, addresses, references, fixups)

    def test_mixed_table_accepts_named_function_external_addend_and_resolved_global(self):
        # Only the independently payload-verified local allocation is inferred.
        self.assertEqual(dict(self.fixture()), {1: {0x2200}})

    def test_unverified_ordinary_destination_rejects_all_local_inference(self):
        for invalid in ['unknown', 'named_reference_conflict', 'two_references',
                        'canonical_name_conflict', 'wrong_addend', 'wrong_pointer',
                        'outside_image', 'outside_virtual_extent']:
            with self.subTest(invalid=invalid):
                self.assertFalse(self.fixture(invalid))

    def test_mixed_table_still_requires_full_payload_and_exact_fixup_set(self):
        for invalid in ['ordinary_missing_fixup', 'extra_fixup', 'tail',
                        'literal_payload', 'literal_reference_conflict']:
            with self.subTest(invalid=invalid):
                self.assertFalse(self.fixture(invalid))


if __name__ == '__main__':
    unittest.main()
