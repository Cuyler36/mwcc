#!/usr/bin/env python3
"""Map baseline imports, retain provenance, and gate matches with objdiff-cli and PE fixups."""
import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import re
import struct
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "build/python"))
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP, CS_GRP_RET, CS_GRP_IRET
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_INS_JMP

from compare import base_relocations, function_section, original, read_object, resolve_function, write_coff

ROOT = Path("build/GC_3_0a5_2")
CONFIG = Path("config/GC_3_0a5_2")


def unit(function):
    return Path(function["source"]).with_suffix("").as_posix() + "/" + function["name"]


def records():
    baseline = json.loads(Path("config/GC_1_2_5/functions.json").read_text())
    splits = json.loads((CONFIG / 'source-splits.json').read_text()) if (CONFIG / 'source-splits.json').exists() else {}
    renames = json.loads((CONFIG / "parser-baseline-names.json").read_text())
    renames.update(dict(Targets_SetTool="SetParserToolInfo", Targets_MatchTool="ParserToolMatchesPlugin",
                        Targets_MatchCommandLineOptions="ParserToolHandlesPanels",
                        Targets_RegisterOptionLists="SetupParserToolOptions"))
    for row in baseline:
        row = dict(row, baseline_name=row["name"], baseline_address=row["address"])
        if row["source"] == "src/driver/Targets.c":
            row["name"] = renames[row["name"]]
            filename = "Targets.c" if row["baseline_name"] in list(renames)[-4:] else (
                "Arguments.c" if row["name"].startswith("Arg_") else "ParserErrors.c")
            row["source"] = "src/GC_3_0a5_2/driver/" + filename
        # Physical GC3 splits and canonical names must survive rediscovery.
        if row['baseline_name'] in splits:
            row.update(splits[row['baseline_name']])
        row["symbol"] = row["name"] if row["name"].startswith("?") else "_" + row["name"]
        yield row


def discover():
    _, pe = original("GC_3_0a5_2")
    labels = {m[1]: int(m[2], 16) for m in re.finditer(r"^([^\n]+) at ([0-9a-f]+)$",
              Path("build/gc3-ghidra-functions-current.txt").read_text(), re.M)}
    entries = set(labels.values())
    code = [(s.virtual_address, pe.data[s.file_offset:s.file_offset+s.file_size])
            for s in pe.sections if s.characteristics & 0x20000000]
    objects, candidates, mappings = {}, [], []
    for row in records():
        obj = ROOT / "compiled" / (row["source"] + ".obj")
        if not obj.exists():
            continue
        if row["source"] not in objects:
            objects[row["source"]] = read_object(obj)
        try:
            sec, begin, end = function_section(*objects[row["source"]], row["symbol"])
        except ValueError:
            continue
        body = sec["data"][begin:end].rstrip(b"\x90\xcc")
        masked = {i-begin for off, _, kind in sec["relocs"] if kind in (6, 7, 20)
                  for i in range(off, off+4) if begin <= i < begin+len(body)}
        hits = []
        if len(body)-len(masked) >= 12:
            pattern = re.compile(b"".join(b"." if i in masked else re.escape(bytes([v]))
                                         for i, v in enumerate(body)), re.S)
            hits = [base+m.start() for base, data in code for m in pattern.finditer(data)
                    if base+m.start() in entries]
        if len(hits) == 1:
            address, evidence = hits[0], "Unique relocation-masked compiled body at a Ghidra entry"
            candidates.append(dict(row, address=f"0x{address:08x}", size=len(body)))
        elif row["name"] in labels or row["baseline_name"] in labels:
            address = labels.get(row["name"], labels.get(row["baseline_name"]))
            evidence = "Existing Ghidra label; baseline identity requires semantic review"
        else:
            continue
        mappings.append(dict(row, address=f"0x{address:08x}", mapping_evidence=evidence))
    occupied = Counter(r["address"] for r in mappings)
    mappings = [r for r in mappings if occupied[r["address"]] == 1]
    (ROOT / "selected-body-candidates.json").write_text(json.dumps(candidates, indent=2)+"\n")
    (ROOT / "baseline-mappings.json").write_text(json.dumps(mappings, indent=2)+"\n")
    print(f"{len(mappings)} mapped baseline imports; {len(candidates)} unique compiled-body candidates")


def flow_boundary(pe, address, end):
    """Conservative reachable-code extent, bounded by Ghidra's next entry point."""
    dis = Cs(CS_ARCH_X86, CS_MODE_32)
    dis.detail = True
    pending, visited, maximum, unresolved = [address], set(), address, False
    while pending:
        cursor = pending.pop()
        while address <= cursor < end and cursor not in visited:
            visited.add(cursor)
            instruction = next(dis.disasm(pe.read(cursor,min(15,end-cursor)),cursor,count=1),None)
            if instruction is None:
                unresolved = True
                break
            maximum = max(maximum,cursor+instruction.size)
            if instruction.group(CS_GRP_RET) or instruction.group(CS_GRP_IRET):
                break
            if instruction.group(CS_GRP_JUMP):
                operand = instruction.operands[0]
                if operand.type == X86_OP_IMM:
                    target = operand.imm & 0xffffffff
                    if address <= target < end:
                        pending.append(target)
                elif operand.type == X86_OP_MEM and operand.mem.scale == 4 and operand.mem.disp:
                    found = 0
                    for index in range(256):
                        try:
                            target = struct.unpack('<I',pe.read((operand.mem.disp & 0xffffffff)+index*4,4))[0]
                        except ValueError:
                            break
                        if not address <= target < end:
                            break
                        pending.append(target)
                        found += 1
                    unresolved |= not found
                else:
                    unresolved = True
                if instruction.id == X86_INS_JMP:
                    break
            cursor += instruction.size
    return maximum-address, unresolved


def integrate():
    _, pe = original("GC_3_0a5_2")
    fixups = set(base_relocations(pe))
    exported = json.loads((ROOT / "ghidra-import-boundaries.json").read_text())
    boundaries = {}
    for item in exported:
        match = re.search(r"Body: ([0-9a-f]+) - ([0-9a-f]+)", item["info"])
        if match and int(match[1], 16) == int(item["address"], 16):
            boundaries[int(item["address"], 16)] = int(match[2], 16)-int(match[1], 16)+1
    direct_boundaries = dict(boundaries)
    entries = sorted({int(m[1],16) for m in re.finditer(r" at ([0-9a-f]+)$",
                      Path('build/gc3-ghidra-functions-current.txt').read_text(),re.M)})
    extent_notes = {}
    for row in json.loads((ROOT / "baseline-mappings.json").read_text()):
        address = int(row['address'],0)
        if address in boundaries:
            continue
        following = bisect_right(entries,address)
        if following >= len(entries):
            continue
        size, unresolved = flow_boundary(pe,address,entries[following])
        if size:
            boundaries[address] = size
            extent_notes[row['name']] = dict(method='Reachable x86 control flow bounded by Ghidra entries',
                                             unresolved_indirect_flow=bool(unresolved))
    previous = [r for r in json.loads((CONFIG / "functions.json").read_text())
                if "mapping_evidence" not in r]
    previous_addresses = {int(r["address"], 0) for r in previous}
    rows = [r for r in json.loads((ROOT / "baseline-mappings.json").read_text())
            if int(r["address"], 0) in boundaries and int(r["address"], 0) not in previous_addresses]
    for row in rows:
        row["size"] = boundaries[int(row["address"], 0)]
        row['boundary_evidence'] = 'Ghidra function body' if int(row['address'],0) in direct_boundaries else extent_notes[row['name']]
    rows = sorted(previous + rows, key=lambda r: int(r["address"], 0))
    splits = json.loads((CONFIG / 'source-splits.json').read_text()) if (CONFIG / 'source-splits.json').exists() else {}
    for row in rows:
        split = splits.get(row.get('baseline_name', row['name']))
        if split:
            row.update(split)
            row['symbol'] = row['name'] if row['name'].startswith('?') else '_' + row['name']
    overlaps = {r["name"] for r, following in zip(rows, rows[1:])
                if int(r["address"], 0)+r["size"] > int(following["address"], 0)}
    rows = [r for r in rows if r["name"] not in overlaps]
    addresses = {k:int(v,0) for k,v in json.loads((CONFIG / "bindings.json").read_text()).items()}
    objects = {}
    for row in rows:
        symbol = row.get("symbol", "_"+row["name"])
        addresses[symbol] = int(row["address"], 0)
        if row.get("baseline_name"):
            addresses["_"+row["baseline_name"]] = int(row["address"], 0)
        if row["source"] not in objects:
            objects[row["source"]] = read_object(ROOT / "compiled" / (row["source"]+".obj"))
    # Derive addresses only from complete, uniquely located instruction patterns.
    # Conflicting observations are excluded; local data still needs content validation.
    observations = defaultdict(list)
    for row in rows:
        if not row.get("mapping_evidence", "").startswith("Unique"):
            continue
        symbols, sections = objects[row["source"]]
        sec, begin, end = function_section(symbols, sections, row["symbol"])
        body = sec["data"][begin:end].rstrip(b"\x90\xcc")
        if len(body) != row["size"]:
            continue
        expected = pe.read(int(row["address"],0), row["size"])
        for offset, index, kind in sec["relocs"]:
            if not begin <= offset < begin+len(body) or kind not in (6,7,20):
                continue
            dest = symbols[index]
            if dest["section"] != 0:
                continue
            local = offset-begin
            addend = struct.unpack_from("<I",body,local)[0]
            original_operand = struct.unpack_from("<I",expected,local)[0]
            value = (original_operand-addend+(int(row["address"],0)+local+4 if kind==20
                     else pe.image_base if kind==7 else 0)) & 0xffffffff
            observations[dest["name"]].append(dict(address=value, function=row["name"], offset=local))
    conflicts = {}
    old_evidence = CONFIG / "baseline-port-evidence.json"
    inferred = json.loads(old_evidence.read_text()).get("inferred_bindings", {}) if old_evidence.exists() else {}
    for name, evidence in observations.items():
        values = {x["address"] for x in evidence}
        if len(values) != 1 or name in addresses and addresses[name] not in values:
            conflicts[name] = evidence
            continue
        if name not in addresses:
            addresses[name] = next(iter(values))
            inferred[name] = evidence
    evidence_rows = []
    scoped_bindings = json.loads((CONFIG / 'config.json').read_text()).get('source_bindings', {})
    comparison_dir = ROOT / "objdiff-imports"
    comparison_dir.mkdir(parents=True, exist_ok=True)
    for row in rows:
        address = int(row["address"],0)
        symbol = row.get("symbol", "_"+row["name"])
        evidence = dict(name=row["name"], source=row["source"], address=row["address"], size=row["size"])
        try:
            row_addresses = dict(addresses)
            row_addresses.update({k: int(v, 0) for k, v in scoped_bindings.get(row['source'], {}).items()})
            body, resolutions = resolve_function(*objects[row["source"]], symbol, address, row_addresses, pe, row["size"])
            evidence["bytes_exact"] = body == pe.read(address,row["size"])
            evidence["fixups_exact"] = {address+r['offset'] for r in resolutions if r['kind']==6} == {
                f for f in fixups if address <= f < address+row["size"]}
            slug = f"{address:08x}"
            write_coff(comparison_dir / (slug+".target.obj"),pe.read(address,row["size"]),symbol)
            write_coff(comparison_dir / (slug+".base.obj"),body,symbol)
            evidence["objdiff_slug"] = slug
        except ValueError as error:
            evidence["unresolved"] = str(error)
        evidence_rows.append(evidence)

    def diff(evidence):
        slug = evidence.get("objdiff_slug")
        if not slug:
            return
        output = comparison_dir / (slug+".json")
        run = subprocess.run(["build/tools/objdiff-cli.exe","diff","-1",str(comparison_dir/(slug+".target.obj")),
                              "-2",str(comparison_dir/(slug+".base.obj")),"-o",str(output)],capture_output=True,text=True)
        if run.returncode:
            evidence["objdiff_error"] = run.stderr
            return
        result = json.loads(output.read_text())
        symbols = result.get("left",{}).get("symbols",[])
        evidence["objdiff_match_percent"] = next((s.get("match_percent",0) for s in symbols
                                                  if s.get("kind")=="SYMBOL_FUNCTION"),0)
    with ThreadPoolExecutor(max_workers=3) as executor:
        list(executor.map(diff,evidence_rows))
    unresolved_extents = {r['name'] for r in rows if isinstance(r.get('boundary_evidence'),dict)
                          and r['boundary_evidence'].get('unresolved_indirect_flow')}
    matching = [unit(e) for e in evidence_rows if e.get("bytes_exact") and e.get("fixups_exact")
                and e.get("objdiff_match_percent")==100 and e['name'] not in unresolved_extents]
    config = json.loads((CONFIG/"config.json").read_text())
    config["matching_functions"] = matching
    (CONFIG/"config.json").write_text(json.dumps(config,indent=2)+"\n")
    functions = [{k:v for k,v in row.items() if k not in ("symbol", "binary_patch")}
                 for row in rows]
    (CONFIG/"functions.json").write_text(json.dumps(functions,indent=2)+"\n")
    (CONFIG/"bindings.json").write_text(json.dumps({k:f"0x{v:08x}" for k,v in sorted(addresses.items())},indent=2)+"\n")
    summary = dict(enabled_sources=len(config["sources"]), mapped_functions=len(rows),
                   objdiff_verified_functions=len(matching), exact_bytes=sum(e["size"] for e in evidence_rows
                   if unit(e) in matching), inferred_bindings=inferred, binding_conflicts=conflicts,
                   overlapping_bodies_excluded=sorted(overlaps), functions=evidence_rows)
    (CONFIG/"baseline-port-evidence.json").write_text(json.dumps(summary,indent=2)+"\n")
    print(f"{len(matching)}/{len(rows)} imports pass objdiff-cli, complete bytes, and PE fixups")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode",choices=("discover","integrate"))
    {"discover":discover,"integrate":integrate}[parser.parse_args().mode]()
