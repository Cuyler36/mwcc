"""Read Mac nm/STABS symbols without assigning ordinary nm symbols to STABS units."""
import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--symbols', type=Path, required=True, help='Path to mwccppc_pro8_syms (read-only input)')
    parser.add_argument('--output', type=Path, default=ROOT/'build/GC_3_0a5_2/inventory/symbols', help='Output directory for the inventory JSON files')
    args = parser.parse_args()
    out = args.output
    out.mkdir(parents=True, exist_ok=True)
    data = args.symbols.read_bytes()
    lines = data.decode('utf-8', errors='strict').splitlines()
    stab_re = re.compile(r'^([0-9a-fA-F]{8})\s+-\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\w+)\s*(.*)$')
    nm_re = re.compile(r'^([0-9a-fA-F]{8})\s+([A-Za-z?])\s+(\S+)$')
    units, ordinary, unowned, kinds = [], [], [], Counter()
    directory, active = '', None
    for number, line in enumerate(lines, 1):
        match = stab_re.match(line)
        if match:
            address, segment, desc, kind, payload = match.groups()
            kinds[kind] += 1
            if kind == 'SO':
                if active is not None:
                    active['next_so_line'] = number
                    active['next_so_address'] = '0x' + address.lower()
                active = None
                if payload.endswith('/'):
                    directory = payload
                elif payload:
                    active = dict(source=payload, path=directory + payload, address='0x' + address.lower(), line=number, functions=[], data_symbols=[])
                    units.append(active)
            elif kind in ('FUN', 'STSYM', 'LCSYM', 'GSYM') and payload:
                name = payload.split(':', 1)[0]
                entry = dict(name=name, address='0x' + address.lower(), kind=kind, line=number, descriptor=payload)
                if active is not None:
                    active['functions' if kind == 'FUN' else 'data_symbols'].append(entry)
                else:
                    unowned.append(entry)
            continue
        match = nm_re.match(line)
        if match:
            address, kind, raw = match.groups()
            ordinary.append(dict(name=raw[1:] if raw.startswith('_') else raw, raw_name=raw, address='0x' + address.lower(), kind=kind, line=number))

    baseline = json.loads((ROOT/'config/GC_1_2_5/functions.json').read_text())
    current = json.loads((ROOT/'config/GC_3_0a5_2/functions.json').read_text())
    config = json.loads((ROOT/'config/GC_3_0a5_2/config.json').read_text())
    renames = json.loads((ROOT/'config/GC_3_0a5_2/parser-baseline-names.json').read_text())
    renames.update(Targets_SetTool='SetParserToolInfo', Targets_MatchTool='ParserToolMatchesPlugin', Targets_MatchCommandLineOptions='ParserToolHandlesPanels', Targets_RegisterOptionLists='SetupParserToolOptions')
    base_by_name, curr_by_name, base_by_file = defaultdict(list), defaultdict(list), defaultdict(list)
    for row in baseline:
        base_by_name[renames.get(row['name'], row['name'])].append(row)
        base_by_file[Path(row['source']).name].append(row)
    for row in current:
        curr_by_name[row['name']].append(row)
    nm_by_address = defaultdict(list)
    for row in ordinary:
        if row['kind'].lower() == 't':
            nm_by_address[row['address']].append(row['name'])
    ghidra = defaultdict(list)
    for line in (ROOT/'build/gc3-ghidra-functions-current.txt').read_text().splitlines():
        match = re.fullmatch(r'(.+) at ([0-9a-fA-F]+)', line)
        if match:
            ghidra[match[1]].append('0x'+match[2].lower())
    for unit in units:
        names = [row['name'] for row in unit['functions']]
        for function in unit['functions']:
            function['linkage_names'] = nm_by_address[function['address']]
            source_candidates = base_by_file[unit['source']]
            function['baseline_same_file_candidates'] = [dict(name=r['name'], source=r['source'], address=r['address']) for r in source_candidates if r['name'] == function['name'] or r['name'].endswith('_' + function['name'])]
            function['candidate_warning'] = 'Same-file suffix/name similarity is a proposed identity, not a confirmed Windows mapping.'
        unit['baseline_same_filename'] = sorted({row['source'] for row in base_by_file[unit['source']]})
        unit['baseline_name_overlap'] = [dict(name=name, sources=sorted({r['source'] for r in base_by_name[name]})) for name in names if name in base_by_name]
        unit['windows_mappings'] = [dict(name=name, mappings=curr_by_name[name]) for name in names if name in curr_by_name]
        unit['windows_ghidra_labels'] = [dict(name=name, addresses=ghidra[name]) for name in names if name in ghidra]
        unit['unmapped_windows_names'] = [name for name in names if name not in curr_by_name]
        unit['completeness_evidence'] = 'Explicit SO unit and all FUN records until next SO; this is Mac debug coverage, not proof of Windows completeness.'
    ordinary_functions = [r for r in ordinary if r['kind'].lower() == 't']
    ordinary_overlap = [dict(r, baseline=base_by_name[r['name']], current=curr_by_name.get(r['name'], []), windows_labels=ghidra.get(r['name'], [])) for r in ordinary_functions if r['name'] in base_by_name]
    summary = dict(symbol_file=str(args.symbols), sha256=hashlib.sha256(data).hexdigest(), lines=len(lines), stab_kinds=dict(kinds), unit_records=len(units), unique_source_names=len({u['source'] for u in units}), stab_function_records=sum(len(u['functions']) for u in units), stab_function_names=len({r['name'] for u in units for r in u['functions']}), ordinary_symbols=len(ordinary), ordinary_kinds=dict(Counter(r['kind'] for r in ordinary)), ordinary_text_symbols=len(ordinary_functions), ordinary_text_names=len({r['name'] for r in ordinary_functions}), ordinary_baseline_overlap=len(ordinary_overlap), current_config_sources=len(config['sources']), current_function_mappings=len(current), limitations=['Mac PowerPC symbols are architecture-related evidence, not Windows addresses or unit completeness.', 'Ordinary nm symbols never receive source membership from surrounding SO records.', 'Exact duplicate static function names require address and semantic evidence.', 'GSYM addresses may be zero and require separate nm resolution.', 'FUN count includes empty function-end records; stab_function_records counts only named records.'])
    (out/'inventory.json').write_text(json.dumps(dict(summary=summary, units=units, ordinary_symbols=ordinary, ordinary_baseline_overlap=ordinary_overlap, unowned_debug_symbols=unowned), indent=2)+'\n', encoding='utf-8')
    (out/'summary.json').write_text(json.dumps(summary, indent=2)+'\n', encoding='utf-8')
    compact = dict(schema_version=1, provenance=dict(sha256=summary['sha256'], artifact='mwccppc_pro8_syms', architecture='Mac PowerPC', evidence='Explicit STABS SO/FUN source membership'), limitations=summary['limitations'], units=[dict(source=u['source'], original_path=u['path'], mac_address=u['address'], line=u['line'], functions=[dict(name=f['name'], mac_address=f['address'], linkage_names=f['linkage_names']) for f in u['functions']], data_symbols=u['data_symbols'], baseline_same_filename=u['baseline_same_filename']) for u in units])
    (out/'original-source-inventory.json').write_text(json.dumps(compact, indent=2)+'\n', encoding='utf-8')
    print(json.dumps(summary, indent=2))
    print('\nUnit inventory:')
    for u in units:
        print(f"{u['source']}: {len(u['functions'])} FUN, {len(u['windows_mappings'])} mapped, {len(u['windows_ghidra_labels'])} labels; baseline={','.join(u['baseline_same_filename'])}")

if __name__ == '__main__':
    main()
