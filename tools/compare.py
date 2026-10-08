#!/usr/bin/env python3
"""python tools/compare.py {extract,compare,report,unit} VERSION [SOURCE]

extract: validate the original and prepare unassigned image-section objects.
compare: each function of a compiled source, its relocations resolved against the original (the executable is not
  relinked), compared byte for byte and its absolute addresses against the original's base relocations; writes
  source-level code/data objects and objdiff.json; fails when a Matching function differs.
unit: rebuild one source's target/base pair for objdiff's Ninja request.
report:  objdiff's progress report (build/VERSION/report.json).
"""
import hashlib
import json
import os
import re
from urllib.parse import quote
import struct
from bisect import bisect_left
import subprocess
import sys
from functools import cache
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from pe import PEFile


def original(version):
    """The original executable, checked against its published SHA-1."""
    config = json.loads(Path(f"config/{version}/config.json").read_text())
    path = Path(config["original"])
    if hashlib.sha1(path.read_bytes()).hexdigest() != config["sha1"]:
        raise SystemExit(f"{path}: SHA-1 is not {config['sha1']}")
    return config, PEFile(path)


@cache
def sources():
    return json.loads(Path("config/sources.json").read_text())


@cache
def version_config(version):
    return json.loads(Path(f"config/{version}/config.json").read_text())


def matching(version, source, unit=None):
    """Whether SOURCE's exact functions are linked in VERSION: a version can list its Matching sources itself (its
    config's "matching"), else config/sources.json's status decides."""
    if "matching_functions" in version_config(version):
        return unit in version_config(version)["matching_functions"]
    if "matching" in version_config(version):
        return source in version_config(version)["matching"]
    return sources().get(source, {}).get("status", "Matching") == "Matching"


def inventory(version):
    """The executable as rows: each function config/VERSION/functions.json maps, and the ranges between them."""
    config, pe = original(version)
    functions = json.loads(Path(f"config/{version}/functions.json").read_text())
    # Explicit Windows diagnostic ownership adds original-only functions to
    # their source TU, without inventing implementations or compiled objects.
    known = {int(f['address'], 0) for f in functions}
    plan = config.get('translation_units')
    if plan:
        for unit in json.loads(Path(plan).read_text())['units']:
            for function in unit['windows_functions']:
                address = int(function['address'], 0)
                if address not in known and function['size']:
                    functions.append(dict(function, target_source=unit['source']))
                    known.add(address)
        ordered = sorted(functions, key=lambda f: int(f['address'], 0))
        for left, right in zip(ordered, ordered[1:]):
            if int(left['address'], 0) + left['size'] > int(right['address'], 0):
                raise ValueError(f"Overlapping original functions: {left['name']} / {right['name']}")
    rows = []
    for section in pe.sections:
        code = bool(section.characteristics & 0x20000000)
        if not code and section.name in (".reloc", ".rsrc", ".idata", ".edata"):
            continue
        start, end = section.virtual_address, section.virtual_address + section.virtual_size
        cursor = start
        selected = sorted((f for f in functions if code and start <= int(f["address"], 0) < end),
                          key=lambda f: int(f["address"], 0)) if code else []
        for f in selected:
            address = int(f["address"], 0)
            if address > cursor:
                rows.append(dict(name=f"unknown/{section.name}/{cursor:08x}", address=cursor, size=address - cursor, code=code))
            # (a function without a source is one the decompilation does not have yet)
            source = f.get('source', f.get('target_source'))
            unit = Path(source).with_suffix("").as_posix() if source else "unrecovered"
            rows.append(dict(f, address=address, code=True, name=unit + "/" + f["name"],
                             # (C++-mangled names carry no C underscore in COFF)
                             symbol=f["name"] if f["name"].startswith("?") else "_" + f["name"]))
            cursor = address + f["size"]
        if cursor < end:
            rows.append(dict(name=f"unknown/{section.name}/{cursor:08x}", address=cursor, size=end - cursor, code=code))
    for row in rows:
        section = pe.section_for_address(row["address"])
        row["bss"] = bool(section.characteristics & 0x80) and section.file_size == 0
        filename = quote(row["name"], safe="/@$")
        row["target"] = f"build/{version}/target/{filename}.obj"
        if "source" in row:
            row["base"] = f"build/{version}/base/{filename}.obj"
    return config, pe, rows


def write_coff(path, data, name=None, code=True, bss_size=0):
    """One section; optional symbols also keep unassigned code visible to objdiff."""
    strings = bytearray(b"\0" * 4)
    symbols = b""
    if name:
        encoded = name.encode() + b"\0"
        symname = struct.pack("<II", 0, len(strings))
        strings.extend(encoded)
        symbols = symname + struct.pack("<IhHBB", 0, 1, 0x20 if code else 0, 2, 0)
    struct.pack_into("<I", strings, 0, len(strings))
    size = bss_size or len(data)
    section_name = b".text" if code else b".bss" if bss_size else b".data"
    flags = 0x60000020 if code else 0xC0000080 if bss_size else 0xC0000040
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 60 + len(data), bool(name), 0, 0)
    section = struct.pack(
        "<8sIIIIIIHHI",
        section_name,
        0,
        0,
        size,
        0 if bss_size else 60,
        0,
        0,
        0,
        0,
        flags,
    )
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header + section + data + symbols + strings)


def source_paths(version, source):
    filename = quote(source, safe="/@$") + ".obj"
    return (f"build/{version}/target/{filename}", f"build/{version}/base/{filename}")


def write_translation_unit(path, functions, data_sections=None):
    """Consolidated .text and distinct data classes, with sized function symbols."""
    text = bytearray()
    code_symbols = []
    for name, body in functions:
        code_symbols.append((name, len(text), len(body), True))
        text.extend(body)
    sections = [dict(name=".text", data=bytes(text), symbols=code_symbols, flags=0x60000020)]
    sections.extend(data_sections or [])
    strings = bytearray(b"\0" * 4)
    symbols, headers, bodies = bytearray(), bytearray(), bytearray()
    offset = 20 + 40 * len(sections)
    symbol_count = 0
    for index, section in enumerate(sections, 1):
        for name, value, size, code in section["symbols"]:
            name_offset = len(strings)
            strings.extend(name.encode() + b"\0")
            symbols.extend(struct.pack("<IIIhHBB", 0, name_offset, value, index, 0x20 if code else 0, 2, int(code)))
            symbol_count += 1
            if code:
                symbols.extend(struct.pack("<IIIIH", 0, size, 0, 0, 0))
                symbol_count += 1
        body = section["data"]
        bss = section["flags"] & 0x80
        headers.extend(struct.pack("<8sIIIIIIHHI", section["name"].encode(), 0, 0,
                                   section.get("size", len(body)), 0 if bss else offset + len(bodies),
                                   0, 0, 0, 0, section["flags"]))
        if not bss:
            bodies.extend(body)
    struct.pack_into("<I", strings, 0, len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, len(sections), 0,
                         offset + len(bodies), symbol_count, 0, 0)
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header + headers + bodies + symbols + strings)


def write_source_unit(version, source, rows, results, pe, claims=None):
    target, base = source_paths(version, source)
    mapped = {row["symbol"]: row for row in rows}
    target_functions = [(row["symbol"], pe.read(row["address"], row["size"])) for row in rows]
    config = version_config(version)
    if source not in config.get('sources', sources()):
        write_translation_unit(target, target_functions, [])
        return dict(name=Path(source).with_suffix('').as_posix(), target_path=target,
                    metadata=dict(complete=False, progress_categories=['code', 'data']))
    symbols, sections = read_object(Path(f"build/{version}/compiled/{source}.obj"))
    emitted = sorted((s for s in symbols.values() if s["section"] > 0 and s["type"] & 0x20
                      and sections[s["section"] - 1]["code"]),
                     key=lambda s: (s["section"], s["value"]))
    base_functions = []
    for symbol in emitted:
        name = symbol["name"]
        row = mapped.get(name) or next((r for n, r in mapped.items() if c_symbol(name) == n), None)
        body = results[row["name"]][0] if row else None
        if body is None:
            sec, begin, end = function_section(symbols, sections, name)
            body = sec["data"][begin:end]
        base_functions.append((row["symbol"] if row else name, body))
    target_data, base_data, data_complete = source_data(version, source, rows, symbols, sections, pe, claims)
    write_translation_unit(target, target_functions, target_data)
    write_translation_unit(base, base_functions, base_data)
    all_emitted_mapped = all(name in mapped for name, _ in base_functions)
    complete = bool(rows) and all_emitted_mapped and data_complete and all(
        results.get(r["name"], (None, False))[1] and matching(version, source, r["name"]) and not r.get("binary_patch")
        for r in rows)
    if "complete_sources" in config:
        complete &= source in config["complete_sources"]
    if complete:
        report_path = Path(f'build/{version}/unit-diffs/{source}.json')
        report_path.parent.mkdir(parents=True, exist_ok=True)
        cli = 'build/tools/objdiff-cli' + ('.exe' if os.name == 'nt' else '')
        subprocess.run([cli, 'diff', '-1', target, '-2', base, '-o', str(report_path)], check=True)
        diff = json.loads(report_path.read_text())
        left, right = diff['left']['sections'], diff['right']['sections']
        shape = lambda items: sorted((s['name'], s['kind'], int(s.get('size', 0))) for s in items)
        complete = shape(left) == shape(right) and all(s.get('match_percent', 100) == 100 for s in left + right)
    return dict(name=Path(source).with_suffix("").as_posix(), target_path=target, base_path=base,
                metadata=dict(complete=bool(complete), source_path=source, progress_categories=["code", "data"]))


def read_memory(pe, address, size):
    section = pe.section_for_address(address)
    relative = address - section.virtual_address
    if relative + size > max(section.virtual_size, section.file_size):
        raise ValueError("data crosses image section")
    backed = min(size, max(0, section.file_size - relative))
    offset = section.file_offset + relative
    return pe.data[offset:offset + backed] + bytes(size - backed)


def source_data(version, source, rows, symbols, sections, pe, claims):
    """Expose compiled data; attribute retail data only through names or resolved references."""
    addresses = {k: int(v, 0) for k, v in json.loads(Path(f"config/{version}/bindings.json").read_text()).items()}
    functions = json.loads(Path(f'config/{version}/functions.json').read_text())
    addresses.update({r['name'] if r['name'].startswith('?') else '_' + r['name']: int(r['address'], 0)
                      for r in functions})
    addresses.update({r['name'] if r['name'].startswith('?') else '_' + r['name']: int(r['address'], 0)
                      for r in functions if r.get('source') == source})
    addresses.update({name: int(value, 0) for name, value in
                      version_config(version).get('source_bindings', {}).get(source, {}).items()})
    references = defaultdict(set)
    fixups = set(base_relocations(pe))
    for row in rows:
        try:
            _, resolutions = resolve_function(symbols, sections, row["symbol"], row["address"],
                                               addresses, pe, row["size"])
        except ValueError:
            continue
        for resolution in resolutions:
            references[resolution["symbol_index"]].add(resolution["address"])
    code_ranges = []
    for row in rows:
        try:
            code_section, begin, end = function_section(symbols, sections, row['symbol'])
            section_index = next(i for i, sec in enumerate(sections, 1) if sec is code_section)
            code_ranges.append((section_index, begin, end, row['address']))
        except ValueError:
            continue
    base, target, evidence = {}, {}, []
    complete = True
    for index, section in enumerate(sections, 1):
        flags = section["flags"]
        if section["code"] or not flags & (0x40 | 0x80) or section["name"].startswith(('.debug', '.stab')):
            continue
        category = ".bss" if flags & 0x80 else ".data" if flags & 0x80000000 else ".rdata"
        normalized_flags = {".rdata": 0x40000040, ".data": 0xc0000040, ".bss": 0xc0000080}[category]
        output = base.setdefault(category, dict(name=category, data=bytearray(), symbols=[], flags=normalized_flags))
        start = len(output["data"])
        body = bytearray(section["data"])
        unresolved_relocations = set()
        for offset, symbol_index, kind in section["relocs"]:
            reference = symbols[symbol_index]
            name = reference["name"]
            generated_local = reference['section'] > 0 and re.fullmatch(r'_?@\d+', name)
            location = None if generated_local else addresses.get(name, addresses.get(c_symbol(name)))
            if location is None and len(references[symbol_index]) == 1:
                location = next(iter(references[symbol_index]))
            addend = struct.unpack_from('<I', body, offset)[0] if offset + 4 <= len(body) else 0
            if location is None:
                candidates = {address + reference['value'] - begin
                              for sec, begin, end, address in code_ranges
                              if reference['section'] == sec and begin <= reference['value'] + addend < end}
                if len(candidates) == 1:
                    location = candidates.pop()
            if location is None or kind not in (6, 7) or offset + 4 > len(body):
                unresolved_relocations.add(offset)
                continue
            struct.pack_into('<I', body, offset, (location + addend - (pe.image_base if kind == 7 else 0)) & 0xffffffff)
        output["data"].extend(body)
        definitions = sorted((dict(s, symbol_index=i) for i, s in symbols.items() if s["section"] == index
                              and not s["name"].startswith('.') and s["storage"] in (2, 3)),
                             key=lambda s: s["value"])
        anonymous = not definitions
        if anonymous and body:
            section_symbols = [(i, s) for i, s in symbols.items()
                               if s['section'] == index and s['name'].startswith('.')
                               and s['storage'] == 3 and 0 <= s['value'] < len(body)]
            # CW94 refers to switch tables through .sw$ labels rather than the
            # section symbol. Both are anonymous COFF-local evidence; subtract
            # the label's offset to recover the allocated section's base.
            locations = {a - s['value'] for i, s in section_symbols for a in references[i]}
            definitions = [dict(name=f'__anonymous_section_{index}', value=0,
                                symbol_index=None, anonymous_location=next(iter(locations)) if len(locations) == 1 else None)]
        offsets = sorted({s["value"] for s in definitions} | {len(body)})
        if body and (not definitions or definitions[0]["value"] != 0):
            complete = False
        for symbol in definitions:
            name, begin = symbol["name"], symbol["value"]
            end = next((o for o in offsets if o > begin), len(body))
            payload = bytes(body[begin:end])
            output["symbols"].append((name, start + begin, len(payload), False))
            symbol_index = symbol['symbol_index']
            location = symbol.get('anonymous_location') if anonymous else (
                None if re.fullmatch(r'_?@\d+', name) else addresses.get(name))
            method = 'named binding'
            if anonymous:
                method = 'resolved function reference (anonymous section)'
            elif location is None and len(references[symbol_index]) == 1:
                location = next(iter(references[symbol_index]))
                method = 'resolved function reference'
            entry = dict(name=name, section=category, size=len(payload), method=method)
            try:
                if location is None:
                    raise ValueError('no established retail address')
                retail = read_memory(pe, location, len(payload))
                retail_section = pe.section_for_address(location)
                if (retail_section.characteristics & 0x20
                        or retail_section.name in ('.rsrc', '.reloc', '.idata', '.edata')):
                    raise ValueError('data reference is outside attributable image data sections')
                target_category = retail_section.name
                target_flags = 0xc0000080 if retail_section.characteristics & 0x80 else (
                    0xc0000040 if retail_section.characteristics & 0x80000000 else 0x40000040)
                relocation_fixups = {location + o - begin for o, _, k in section['relocs']
                                     if begin <= o < end and k == 6}
                entry.update(address=f'0x{location:08x}', bytes_exact=retail == payload,
                             target_section=target_category,
                             fixups_exact=relocation_fixups == {f for f in fixups if location <= f < location + len(payload)},
                             relocations_resolved=not any(begin <= o < end for o in unresolved_relocations))
                if anonymous and not (entry['bytes_exact'] and entry['fixups_exact']
                                      and entry['relocations_resolved'] and category == target_category):
                    raise ValueError('anonymous section payload, fixups, or category not verified')
                dest = target.setdefault(target_category, dict(name=target_category, data=bytearray(), symbols=[], flags=target_flags))
                dest["symbols"].append((name, len(dest["data"]), len(retail), False))
                dest["data"].extend(retail)
                if claims is not None:
                    claims.append((location, location + len(retail)))
                complete &= entry['bytes_exact'] and entry['relocations_resolved'] and entry['fixups_exact'] and category == target_category
            except ValueError as error:
                entry['unresolved'] = str(error)
                complete = False
            evidence.append(entry)
    output_path = Path(f'build/{version}/unit-data/{source}.json')
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(json.dumps(evidence, indent=2) + '\n')
    return list(target.values()), list(base.values()), complete


def read_object(path):
    """Preserve COFF symbol indices, including auxiliary entries, for linking."""
    data = path.read_bytes()
    machine, nsec, _, symoff, nsym, opts, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or opts:
        raise ValueError(f"{path}: expected relocatable i386 COFF")
    strstart = symoff + nsym * 18
    strings = data[strstart:]

    def name(raw):
        if raw.startswith(b'/') and raw.rstrip(b'\0')[1:].isdigit():
            offset = int(raw.rstrip(b'\0')[1:])
            return strings[offset:strings.index(b'\0', offset)].decode()
        if raw[:4] == b"\0" * 4:
            offset = struct.unpack_from("<I", raw, 4)[0]
            return strings[offset : strings.index(b"\0", offset)].decode()
        return raw.rstrip(b"\0").decode()

    symbols = {}
    i = 0
    while i < nsym:
        off = symoff + i * 18
        val, sec, typ, storage, aux = struct.unpack_from("<IhHBB", data, off + 8)
        symbols[i] = dict(
            name=name(data[off : off + 8]),
            value=val,
            section=sec,
            type=typ,
            storage=storage,
        )
        i += 1 + aux
    sections = []
    for i in range(nsec):
        off = 20 + i * 40
        rawsize, rawoff, reloff = struct.unpack_from("<III", data, off + 16)
        nrel = struct.unpack_from("<H", data, off + 32)[0]
        flags = struct.unpack_from("<I", data, off + 36)[0]
        sections.append(
            dict(
                name=name(data[off:off + 8]),
                flags=flags,
                code=bool(flags & 0x20),
                # CW94 may leave a nonzero raw pointer on uninitialized data.
                data=data[rawoff : rawoff + rawsize] if rawoff and not flags & 0x80 else bytes(rawsize),
                relocs=[
                    struct.unpack_from("<IIH", data, reloff + j * 10)
                    for j in range(nrel)
                ],
            )
        )
    return symbols, sections


def c_symbol(name):
    decorated = re.fullmatch(r"[_@]([A-Za-z_]\w*)@\d+", name)
    return "_" + decorated[1] if decorated else name


def function_section(symbols, sections, symbol_name):
    found = [
        s for s in symbols.values() if s["name"] == symbol_name and s["section"] > 0
    ]
    if not found:
        # Win32 stdcall decorates the same C name with its stack-argument size.
        found = [
            s
            for s in symbols.values()
            if s["section"] > 0 and c_symbol(s["name"]) == symbol_name
        ]
    if len(found) != 1:
        raise ValueError("candidate function not emitted uniquely")
    symbol = found[0]
    sec = sections[symbol["section"] - 1]
    begin = symbol["value"]
    # Only code/function boundaries: debug/section labels are not function ends.
    ends = [
        s["value"]
        for s in symbols.values()
        if s["section"] == symbol["section"]
        and s["value"] > begin
        and (s["type"] & 0x20 or s["storage"] == 2)
    ]
    end = min(ends, default=len(sec["data"]))
    return sec, begin, end


def resolve_function(symbols, sections, symbol_name, target_address, addresses, pe, target_size=None):
    sec, begin, end = function_section(symbols, sections, symbol_name)
    if target_size and end-begin > target_size and all(b in (0x90,0xcc) for b in sec['data'][begin+target_size:end]):
        end = begin+target_size
    # Immediates the original function itself uses: an ambiguous literal
    # (a short string that occurs many times) is resolved to one of these.
    referenced = set()
    if target_size:
        original = pe.read(target_address, target_size)
        referenced = {struct.unpack_from("<I", original, i)[0] for i in range(max(len(original) - 3, 0))}

    def locate(needle, shift=0):
        """Where NEEDLE is in the original: its one occurrence, else the one the function references (at +SHIFT); two
        or more addresses when that is ambiguous."""
        found = pe.find(needle, limit=2)
        if len(found) > 1 and referenced:
            narrowed = [v - shift for v in referenced if pe.contains(v - shift, needle)]
            if len(narrowed) == 1:
                return narrowed
        return found
    section_index = next(i + 1 for i, section in enumerate(sections) if section is sec)
    body = bytearray(sec["data"][begin:end])
    resolutions = []
    for offset, index, kind in sec["relocs"]:
        if not begin <= offset < end:
            continue
        local = offset - begin
        if local + 4 > len(body):
            raise ValueError("relocation crosses function boundary")
        dest = symbols[index]
        addend = struct.unpack_from("<I", body, local)[0]
        # Compiler-generated local ordinals are translation-unit scoped; a
        # same-named binding from another object must not override their data.
        generated_local = dest["section"] > 0 and re.fullmatch(r"_?@\d+", dest["name"])
        if dest["name"] in addresses and not generated_local:
            address = addresses[dest["name"]]
        elif c_symbol(dest["name"]) in addresses and not generated_local:
            address = addresses[c_symbol(dest["name"])]
        elif dest["section"] == section_index and begin <= dest["value"] < end:
            address = target_address + dest["value"] - begin
        elif dest["section"] > 0 and dest["section"] != section_index:
            literal = sections[dest["section"] - 1]
            if literal.get("code"):
                raise ValueError(f"unbound local function: {dest['name']}")
            literal_end = min(
                (other['value'] for other in symbols.values()
                 if other['section'] == dest['section']
                 and other['value'] > dest['value']
                 and not other['name'].startswith('.')),
                default=len(literal['data']),
            )
            payload = bytearray(literal["data"][dest["value"] : literal_end])
            for table_offset, table_index, table_kind in literal['relocs']:
                if table_offset + 4 <= dest['value'] or table_offset >= literal_end:
                    continue
                position = table_offset - dest['value']
                if position < 0 or position + 4 > len(payload) or table_kind not in (6, 7):
                    payload = bytearray()
                    break
                reference = symbols[table_index]
                table_addend = struct.unpack_from('<I', payload, position)[0]
                reference_name = reference['name']
                if reference_name in addresses:
                    resolved = addresses[reference_name] + table_addend
                elif c_symbol(reference_name) in addresses:
                    resolved = addresses[c_symbol(reference_name)] + table_addend
                elif reference['section'] == section_index and begin <= reference['value'] + table_addend < end:
                    resolved = target_address + reference['value'] + table_addend - begin
                elif reference['section'] == -1:
                    resolved = reference['value'] + table_addend
                else:
                    payload = bytearray()
                    break
                if table_kind == 7:
                    resolved -= pe.image_base
                struct.pack_into('<I', payload, position, resolved & 0xffffffff)
            # A literal ends at the next COFF symbol, which in a merged translation unit can lie past the
            # last table entry: zero bytes after the last relocated entry are alignment padding.
            last_entry = max((o + 4 - dest['value'] for o, _, _ in literal['relocs']
                              if dest['value'] <= o < literal_end), default=None)
            if payload and last_entry is not None and len(payload) > last_entry and not any(payload[last_entry:]):
                payload = payload[:last_entry]
            # Verify the entire literal up to the next COFF data symbol, not
            # unrelated literals that happen to share its section. Every entry
            # in this range must resolve and occur together in the original.
            matches = locate(bytes(payload)) if payload else []
            # Zero storage is not a uniquely identifiable literal. Its address
            # must come from the original operand and a bounded data section.
            if payload and not any(payload):
                matches = []
            # Macro expansion can change string-pool grouping without changing
            # a string's contents. Prefer the original operand when its complete
            # NUL-terminated string agrees, rather than another identical copy.
            start = dest["value"] + addend
            tail = literal["data"][start:]
            stop = tail.find(b"\0")
            string = tail[:stop + 1] if stop > 0 else b""
            original_string_address = None
            if (kind == 6 and target_size and local + 4 <= len(original)
                    and string and all(c in (9, 10, 13) or 32 <= c < 127 for c in string[:-1])
                    and not any(start <= off < start + len(string) for off, _, _ in literal["relocs"])):
                raw = struct.unpack_from("<I", original, local)[0]
                try:
                    if pe.read(raw, len(string)) == string:
                        original_string_address = (raw - addend) & 0xFFFFFFFF
                except ValueError:
                    pass
            if original_string_address is not None:
                address = original_string_address
            elif len(matches) == 1:
                address = matches[0]
            else:
                # COFF section references can point into a merged string pool.
                start = dest["value"] + addend
                tail = literal["data"][start:]
                stop = tail.find(b"\0")
                string = tail[: stop + 1] if stop > 0 else b""
                printable = string and all(
                    c in (9, 10, 13) or 32 <= c < 127 for c in string[:-1]
                )
                hits = (
                    locate(string, addend)
                    if kind == 6
                    and printable
                    and not any(
                        start <= off < start + len(string)
                        for off, _, _ in literal["relocs"]
                    )
                    else []
                )
                if len(hits) != 1 and target_size and local + 4 <= len(original):
                    # Ambiguous or bss literal: take the original's own reference and
                    # accept it only when the literal's contents are found there.
                    raw = struct.unpack_from("<I", original, local)[0]
                    derived = ((raw - addend) if kind == 6 else (raw + target_address + local + 4 - addend)
                               if kind == 20 else None)
                    if derived is not None:
                        derived &= 0xFFFFFFFF
                        try:
                            if hasattr(pe, 'section_for_address'):
                                target_section = pe.section_for_address(derived)
                                if (target_section.characteristics & 0x20000000 or
                                        target_section.name in ('.rsrc', '.reloc', '.idata', '.edata')):
                                    raise ValueError('literal reference is not allocated data')
                                there = read_memory(pe, derived, len(payload))
                            else:
                                there = pe.read(derived, len(payload))
                        except ValueError:
                            there = None
                        if there == bytes(payload):
                            hits = [derived + addend]
                if len(hits) != 1:
                    raise ValueError(
                        f"unbound literal: {dest['name']} ({len(matches)} retail blocks, {len(hits)} strings)"
                    )
                address = hits[0] - addend
        elif dest["section"] == -1:
            address = dest["value"]
        else:
            raise ValueError(f"unbound relocation: {dest['name']}")
        addend = struct.unpack_from("<I", body, local)[0]
        if kind == 6:
            value = address + addend
        elif kind == 7:
            value = address - pe.image_base + addend
        elif kind == 20:
            value = address + addend - (target_address + local + 4)
        else:
            raise ValueError(f"unsupported i386 relocation {kind}")
        struct.pack_into("<I", body, local, value & 0xFFFFFFFF)
        resolutions.append(
            dict(
                offset=local,
                symbol=dest["name"],
                symbol_index=index,
                address=address,
                kind=kind,
                addend=addend,
            )
        )
    return bytes(body), resolutions




def extract(version):
    _, pe, rows = inventory(version)
    unknown_units(version, rows, pe, [])
    for row in rows:
        if 'source' in row or 'target_source' in row or row['name'].startswith('unknown/'):
            continue
        data = b"" if row["bss"] else pe.read(row["address"], row["size"])
        write_coff(row["target"], data, row.get("symbol") or (f"__unknown_{row['address']:08x}" if row["code"] else None),
                   row["code"], row["size"] if row["bss"] else 0)
    Path(f"build/{version}/target/ok").touch()


def base_relocations(pe):
    """The addresses of the absolute (HIGHLOW) fixups in the original's base relocation table."""
    coff = struct.unpack_from("<I", pe.data, 0x3C)[0] + 4
    rva, size = struct.unpack_from("<II", pe.data, coff + 20 + 96 + 5 * 8)
    offset = pe.address_to_offset(pe.image_base + rva)
    end, fixups = offset + size, set()
    while offset < end:
        page, block = struct.unpack_from("<II", pe.data, offset)
        for i in range((block - 8) // 2):
            entry = struct.unpack_from("<H", pe.data, offset + 8 + 2 * i)[0]
            if entry >> 12 == 3:
                fixups.add(pe.image_base + page + (entry & 0xFFF))
        offset += block
    return sorted(fixups)


def check(version, source=None):
    """(rows, {row name: (body or None, exact)}) for each function with a source: its compiled bytes, relocations
    resolved, and whether they are the original's."""
    _, pe, rows = inventory(version)
    fixups = base_relocations(pe)
    addresses = {name: int(value, 0) for name, value in json.loads(Path(f"config/{version}/bindings.json").read_text()).items()}
    addresses.update({r["symbol"]: r["address"] for r in rows if "symbol" in r})
    objects, results = {}, {}
    for row in rows:
        if "source" not in row:
            continue
        if source is not None and row["source"] != source:
            continue
        if row["source"] not in objects:
            objects[row["source"]] = read_object(Path(f"build/{version}/compiled/{row['source']}.obj"))
        scoped_addresses = dict(addresses)
        scoped_addresses.update({r['symbol']: r['address'] for r in rows if r.get('source') == row['source']})
        scoped_addresses.update({name: int(value, 0) for name, value in
                                 version_config(version).get('source_bindings', {}).get(row['source'], {}).items()})
        try:
            body, resolutions = resolve_function(*objects[row["source"]], row["symbol"], row["address"], scoped_addresses, pe,
                                                 row["size"])
        except ValueError:
            # Keep an inspectable instruction diff for imported NonMatching
            # functions, even while some external addresses remain unbound.
            if matching(version, row["source"], row["name"]):
                results[row["name"]] = (None, False)
                continue
            try:
                symbols, sections = objects[row["source"]]
                sec, begin, end = function_section(symbols, sections, row["symbol"])
                partial = bytearray(sec["data"][begin:end])
                for relocation in sec["relocs"]:
                    offset = relocation[0]
                    if not begin <= offset < end:
                        continue
                    isolated = dict(sec, relocs=[relocation])
                    isolated_sections = [isolated if s is sec else s for s in sections]
                    try:
                        resolved, _ = resolve_function(symbols, isolated_sections, row["symbol"],
                                                       row["address"], scoped_addresses, pe, row["size"])
                        partial[offset - begin:offset - begin + 4] = resolved[offset - begin:offset - begin + 4]
                    except ValueError:
                        pass
                results[row["name"]] = (bytes(partial), False)
            except ValueError:
                results[row["name"]] = (None, False)
            continue
        # (the same bytes, and an absolute address exactly where the original's loader fixes one up: a source cannot
        # write an address as a number where the original has a reference, or the reverse)
        results[row["name"]] = (body, body == pe.read(row["address"], row["size"]) and (
            {row["address"] + r["offset"] for r in resolutions if r["kind"] == 6}
            == set(fixups[bisect_left(fixups, row["address"]):bisect_left(fixups, row["address"] + row["size"])])))
    return rows, results


def compare(version):
    rows, results = check(version)
    _, pe = original(version)
    grouped = defaultdict(list)
    units, exact, linked, failed, nonmatching, patched = [], 0, 0, [], [], []
    for row in rows:
        if "source" not in row:
            if 'target_source' in row:
                grouped[row['target_source']].append(row)
                continue
            if not row['name'].startswith('unknown/'):
                units.append(dict(name=row['name'], target_path=row['target'],
                                  metadata=dict(complete=False, progress_categories=['code'])))
            continue
        grouped[row["source"]].append(row)
        _, same = results[row["name"]]
        exact += same
        if row.get("binary_patch"):
            # (Ninji's hand-written patch in 1.2.5n, not compiler output: never matched)
            patched.append(row["name"])
        elif same and matching(version, row["source"], row["name"]):
            linked += 1
        elif not same:
            (failed if matching(version, row["source"], row["name"]) else nonmatching).append(row["name"])
    enabled = dict(sources())
    enabled.update(version_config(version).get("source_settings", {}))
    selected = version_config(version).get("sources", list(enabled))
    claims = []
    for source in dict.fromkeys([*selected, *grouped]):
        units.append(write_source_unit(version, source, grouped[source], results, pe, claims))
    units.extend(unknown_units(version, rows, pe, claims))
    Path("objdiff.json").write_text(json.dumps({
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "min_version": "3.8.0",
        "custom_make": "ninja",
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["src/**/*.c", "src/**/*.cpp", "include/**/*.h", "config/**/*.json"],
        "units": units,
        "progress_categories": [{"id": "code", "name": "Code"}, {"id": "data", "name": "Data"}],
    }, indent=2) + "\n")
    summary = [f"{version}: {exact}/{sum('source' in r for r in rows)} functions exact, {linked} linked"]
    if nonmatching:
        summary.append("  NonMatching: " + (str(len(nonmatching)) + " functions (see objdiff)" if len(nonmatching)>20
                       else " ".join(n.rsplit("/", 1)[1] for n in nonmatching)))
    if patched:
        summary.append("  binary patch: " + " ".join(n.rsplit("/", 1)[1] for n in patched))
    summary += ["  not exact: " + name for name in failed]
    print("\n".join(summary))
    if failed:
        raise SystemExit(1)
    Path(f"build/{version}/ok").write_text("\n".join(summary) + "\n")


def unknown_units(version, rows, pe, claims):
    """Keep unassigned image ranges in section buckets without inventing source membership."""
    sections = defaultdict(list)
    for row in rows:
        if not row['name'].startswith('unknown/'):
            continue
        remaining = [(row['address'], row['address'] + row['size'])]
        if not row['code']:
            for left, right in sorted(claims):
                remaining = [(a, b) for start, end in remaining for a, b in (
                    [(start, end)] if right <= start or left >= end else
                    [(start, min(end, left)), (max(start, right), end)]) if a < b]
        sections[row['name'].split('/')[1]].extend(remaining)
    units = []
    for section_name, spans in sections.items():
        if not spans:
            continue
        section = pe.section_for_address(spans[0][0])
        code = bool(section.characteristics & 0x20)
        bss = bool(section.characteristics & 0x80)
        target = f'build/{version}/target/unknown/{section_name}.obj'
        size = sum(end - start for start, end in spans)
        data = b'' if bss else b''.join(read_memory(pe, start, end - start) for start, end in spans)
        write_coff(target, data, name='__unknown_' + section_name.strip('.') if code else None,
                   code=code, bss_size=size if bss else 0)
        units.append(dict(name='unknown/' + section_name, target_path=target,
                          metadata=dict(complete=False, progress_categories=['code' if code else 'data'])))
    return units


def unit(version, source):
    rows, results = check(version, source)
    _, pe = original(version)
    selected = [r for r in rows if r.get("source", r.get('target_source')) == source]
    write_source_unit(version, source, selected, results, pe)
    failed = [r["name"] for r in selected if 'source' in r and matching(version, source, r["name"])
              and not results[r["name"]][1] and not r.get("binary_patch")]
    if failed:
        raise SystemExit("Not exact: " + ", ".join(failed))


def report(version):
    objdiff = "build/tools/objdiff-cli" + (".exe" if os.name == "nt" else "")
    subprocess.run([objdiff, "report", "generate", "-o", f"build/{version}/report.json"], check=True)
    report = json.loads(Path(f"build/{version}/report.json").read_text())
    # (an unknown code range carries a symbol only so objdiff keeps its bytes: it is not a function)
    removed = 0
    for unit in report["units"]:
        if unit["name"].startswith("unknown/"):
            removed += unit["measures"].get("total_functions", 0)
            unit.pop("functions", None)
            unit["measures"]["total_functions"] = 0
            unit["measures"]["matched_functions_percent"] = 0.0
    for measures in [report["measures"], *(c["measures"] for c in report.get("categories", []) if c["id"] == "code")]:
        measures["total_functions"] = measures.get("total_functions", 0) - removed
        total = measures["total_functions"]
        measures["matched_functions_percent"] = 100.0 * measures.get("matched_functions", 0) / total if total else 0.0
    # Pooled constants can occur in multiple TU views. Count physical image
    # bytes once in global data progress, and require resolved relocations.
    _, pe = original(version)
    total_data = sum(s.virtual_size for s in pe.sections if not s.characteristics & 0x20
                     and s.name not in ('.reloc', '.rsrc', '.idata', '.edata'))
    spans = []
    enabled = dict(sources())
    enabled.update(version_config(version).get('source_settings', {}))
    for source in version_config(version).get('sources', list(enabled)):
        path = Path(f'build/{version}/unit-data/{source}.json')
        if not path.exists():
            continue
        for entry in json.loads(path.read_text()):
            if (entry.get('bytes_exact') and entry.get('fixups_exact') and entry.get('relocations_resolved')
                    and entry['section'] == entry.get('target_section')):
                address = int(entry['address'], 0)
                spans.append((address, address + entry['size']))
    matched_data, end = 0, 0
    for left, right in sorted(spans):
        matched_data += max(0, right - max(end, left))
        end = max(end, right)
    for measures in [report['measures'], *(c['measures'] for c in report.get('categories', []) if c['id'] == 'data')]:
        measures['total_data'] = str(total_data)
        measures['matched_data'] = str(matched_data)
        measures['matched_data_percent'] = 100.0 * matched_data / total_data if total_data else 0.0
    Path(f"build/{version}/report.json").write_text(json.dumps(report, indent=2) + "\n")


if __name__ == "__main__":
    command, version = sys.argv[1:3]
    if command == "unit":
        unit(version, sys.argv[3])
    else:
        {"extract": extract, "compare": compare, "report": report}[command](version)
