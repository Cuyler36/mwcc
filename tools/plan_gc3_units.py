#!/usr/bin/env python3
"""Build the GC3 TU inventory from explicit symbol membership and Windows diagnostics.

Run the two index_gc3_* tools first. Capstone is required for conservative body
extents. This does not infer ownership from adjacent functions or nm ordering.
The checked-in inventory also drives target-only source units in objdiff.
"""
import argparse
from bisect import bisect_right
from collections import defaultdict
import json
from pathlib import Path
import re

from map_gc3_baseline import flow_boundary
from compare import original

CONFIG = Path('config/GC_3_0a5_2')


def load(path):
    return json.loads(Path(path).read_text())


def generate(args):
    config = load(CONFIG / 'config.json')
    mappings = load(CONFIG / 'functions.json')
    mapped = {int(f['address'], 0): f for f in mappings}
    assertions = load(args.assertions)
    symbols = load(args.symbols)
    entries = sorted({int(m[1], 16) for m in re.finditer(
        r' at ([0-9a-f]+)$', Path(args.functions).read_text(), re.M)})
    _, pe = original('GC_3_0a5_2')
    units = {}
    filenames = defaultdict(list)
    for source in config['sources']:
        filenames[Path(source).name].append(source)
        units[source] = dict(source=source, original_filename=Path(source).name,
                             evidence=['Imported 1.2.5 source; GC3 membership remains provisional'],
                             windows_functions=[], mac_functions=[], ownership_conflicts=[])

    def get_unit(filename):
        candidates = filenames[filename]
        if len(candidates) == 1:
            source = candidates[0]
        else:
            category = ('driver' if filename.startswith(('CL', 'Arg', 'Parser')) else
                        'optimizer' if filename.startswith('Iro') else 'frontend')
            source = f'src/GC_3_0a5_2/{category}/{filename}'
        if source not in units:
            units[source] = dict(source=source, original_filename=filename, evidence=[],
                                 windows_functions=[], mac_functions=[], ownership_conflicts=[])
        return units[source]

    owners = {}
    ambiguous = []
    for item in assertions:
        if not item['proposed_tu']:
            ambiguous.append(item)
            continue
        unit = get_unit(Path(item['proposed_tu']).name)
        address = int(item['function_address'], 0)
        owners[address] = unit['source']
        row = mapped.get(address)
        following = bisect_right(entries, address)
        if row:
            size, boundary = row['size'], row.get('boundary_evidence')
        elif following < len(entries):
            size, unresolved = flow_boundary(pe, address, entries[following])
            boundary = dict(method='Reachable x86 control flow bounded by Ghidra entries',
                            unresolved_indirect_flow=bool(unresolved))
        else:
            size, boundary = 0, {'unresolved_indirect_flow': True}
        evidence = dict(name=row['name'] if row else item['function_name'],
                        address=f'0x{address:08x}', size=size, boundary_evidence=boundary,
                        evidence='Windows assertion/file-line diagnostic',
                        call_addresses=item['call_addresses'])
        if row:
            evidence['compiled_source'] = row['source']
            if row['source'] != unit['source']:
                unit['ownership_conflicts'].append(dict(address=evidence['address'], name=row['name'],
                                                       compiled_source=row['source']))
        unit['windows_functions'].append(evidence)
        if 'Windows assertion/file-line diagnostic' not in unit['evidence']:
            unit['evidence'].append('Windows assertion/file-line diagnostic')
    # Add mapped functions without overriding stronger Windows filename evidence.
    for address, row in mapped.items():
        if address in owners:
            continue
        unit = units[row['source']]
        unit['windows_functions'].append(dict(name=row['name'], address=row['address'], size=row['size'],
            compiled_source=row['source'], evidence=row.get('mapping_evidence', 'Manually verified mapping'),
            boundary_evidence=row.get('boundary_evidence')))
    # Mac membership is an expected-name checklist, never a Windows address map.
    mac_only = []
    for item in symbols['units']:
        candidates = [u for u in units.values() if u['original_filename'] == item['source']]
        if len(candidates) == 1:
            candidates[0]['mac_functions'] = item['functions']
            candidates[0]['evidence'].append('Explicit Mac STABS SO/FUN membership')
        else:
            mac_only.append(item)
    for unit in units.values():
        unit['windows_functions'].sort(key=lambda f: int(f['address'], 0))
        unit['compiled'] = unit['source'] in config['sources']
        unit['membership_complete'] = False
    previous = load(args.output) if Path(args.output).exists() else {}
    attempts = previous.get('attempts', {})
    for unit in units.values():
        unit['status'] = attempts.get(unit['source'], {}).get('status', 'unattempted')
    result = dict(schema_version=1, original_sha1=config['sha1'], symbol_provenance=symbols['provenance'],
        limitations=[
            'Diagnostic calls prove caller filename references, not all TU members or data ownership.',
            'Mixed/header-only diagnostic callers remain unassigned.',
            'Imported sources with no mapping are provisional, not proven absent.',
            'Body extents with unresolved indirect flow are provisional.',
            'Ownership conflicts require physical source splitting before moving compiled contributions.',
            'Mac-only units are a separate checklist; they are not enabled Windows sources.'],
        units=sorted(units.values(), key=lambda u: u['source']), mac_only_units=mac_only,
        ambiguous_windows_functions=ambiguous, attempts=attempts)
    Path(args.output).write_text(json.dumps(result, indent=2) + '\n')
    print(f"{len(units)} units; {sum(not u['compiled'] for u in units.values())} target-only; "
          f"{sum(len(u['ownership_conflicts']) for u in units.values())} ownership conflicts")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--assertions', default='build/GC_3_0a5_2/inventory/assertions/functions.json')
    parser.add_argument('--symbols', default='build/GC_3_0a5_2/inventory/symbols/original-source-inventory.json')
    parser.add_argument('--functions', default='build/gc3-ghidra-functions-current.txt')
    parser.add_argument('--output', default=str(CONFIG / 'translation-units.json'))
    generate(parser.parse_args())
