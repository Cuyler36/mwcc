#!/usr/bin/env python3
"""Bounded, read-only compiler-profile experiments for every enabled GC 3 TU.

Writes only build/ evidence. Exact means resolved bytes AND PE fixups agree;
successful compilation, projection diffs and improvements do not finish a TU.
"""
import argparse
import hashlib
from bisect import bisect_left
from collections import Counter
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from configure import pro4_arguments
from compare import (base_relocations, function_section, original, read_object,
                     resolve_function, write_translation_unit)

VERSION = 'GC_3_0a5_2'
OUT = Path(f'build/{VERSION}/tu-sweep')


def profiles(flags, compiler):
    yield 'configured', flags
    if compiler != 'cw94':
        return
    stripped = []
    i = 0
    while i < len(flags):
        if flags[i] == '-opt' and i + 1 < len(flags):
            values = flags[i + 1].split(',')
            values = [v for v in values if v not in ('speed', 'space', 'intrinsics', 'nointrinsics')]
            if values:
                stripped.extend(('-opt', ','.join(values)))
            i += 2
        else:
            stripped.append(flags[i])
            i += 1
    for mode in ('speed', 'space'):
        for intrinsics in (False, True):
            name = mode + ('-intrinsics' if intrinsics else '-nointrinsics')
            yield name, [*stripped, '-opt', mode, '-opt', 'intrinsics' if intrinsics else 'nointrinsics']


def attempt(source, settings, compiler, profile, flags, functions, addresses, pe, fixups):
    source_hash = hashlib.sha256(Path(source).read_bytes()).hexdigest()
    directory = OUT / profile / source
    directory.mkdir(parents=True, exist_ok=True)
    inputs = dict(source_settings=settings, functions=functions, bindings=addresses,
                  compiler=compiler, flags=flags, source_sha256=source_hash)
    (directory / 'inputs.json').write_text(json.dumps(inputs, indent=2) + '\n')
    obj = directory / 'compiled.obj'
    args = ['-c', *flags, '-DVERSION=3',
            *(f'-I{d}' for d in settings.get('include_dirs', [])), '-Iinclude', '-i-',
            *(f'-I{d}' for d in settings.get('system_include_dirs', [])), '-Iinclude/libc',
            source, '-o', str(obj)]
    if compiler == 'pro4':
        args = pro4_arguments(args)
    command = [sys.executable, 'tools/run_compiler.py', '--out', str(obj), '--',
               f'build/compilers/{compiler}/mwcc.exe', *args]
    result = subprocess.run(command, capture_output=True, text=True, errors='replace', timeout=180)
    (directory / 'compile.log').write_text(result.stdout + result.stderr, encoding='utf-8')
    evidence = dict(source=source, compiler=compiler, profile=profile, flags=flags,
                    command=command, compiled=result.returncode == 0,
                    mapped_functions=len(functions), functions=[], object=str(obj),
                    source_sha256=source_hash,
                    source_stable=source_hash == hashlib.sha256(Path(source).read_bytes()).hexdigest())
    if result.returncode:
        evidence['status'] = 'compile_failed'
        return evidence
    symbols, sections = read_object(obj)
    targets, bases = [], []
    for function in functions:
        name = function['name']
        symbol = name if name.startswith('?') else '_' + name
        address, size = int(function['address'], 0), function['size']
        item = dict(name=name, address=function['address'], exact=False)
        targets.append((symbol, pe.read(address, size)))
        try:
            body, resolutions = resolve_function(symbols, sections, symbol, address, addresses, pe, size)
            expected = set(fixups[bisect_left(fixups, address):bisect_left(fixups, address + size)])
            actual = {address + r['offset'] for r in resolutions if r['kind'] == 6}
            item.update(bytes_exact=body == pe.read(address, size), fixups_exact=actual == expected)
            item['exact'] = item['bytes_exact'] and item['fixups_exact']
        except ValueError as error:
            item['unresolved'] = str(error)
            try:
                section, begin, end = function_section(symbols, sections, symbol)
                body = section['data'][begin:end]
            except ValueError:
                body = None
        if body is not None:
            bases.append((symbol, body))
        evidence['functions'].append(item)
    evidence['exact_count'] = sum(f['exact'] for f in evidence['functions'])
    evidence['unresolved_count'] = sum('unresolved' in f for f in evidence['functions'])
    evidence['status'] = 'mapped_projection_attempted' if functions else 'unmapped_needs_discovery'
    if targets:
        target, base = directory / 'target.obj', directory / 'base.obj'
        write_translation_unit(target, targets)
        write_translation_unit(base, bases)
        diff = subprocess.run(['build/tools/objdiff-cli.exe', 'diff', '-1', str(target),
                               '-2', str(base), '-o', str(directory / 'objdiff.json')],
                              capture_output=True, text=True, errors='replace', timeout=90)
        evidence['objdiff_success'] = diff.returncode == 0
        evidence['objdiff_scope'] = 'Mapped function projection only; excludes unported functions and data'
        if diff.returncode:
            evidence['objdiff_error'] = diff.stdout + diff.stderr
    return evidence


def main():
    os.chdir(Path(__file__).resolve().parents[1])
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--workers', type=int, choices=(1, 2), default=2)
    parser.add_argument('--source', action='append', help='Rerun selected TUs, retaining other evidence')
    options = parser.parse_args()
    config = json.loads(Path(f'config/{VERSION}/config.json').read_text())
    selected_sources = list(options.source or config['sources'])
    for source in selected_sources:
        if source not in config['sources']:
            parser.error(f'Source is not enabled: {source}')
    settings = json.loads(Path('config/sources.json').read_text())
    settings.update(config.get('source_settings', {}))
    functions = json.loads(Path(f'config/{VERSION}/functions.json').read_text())
    addresses = {k: int(v, 0) for k, v in json.loads(Path(f'config/{VERSION}/bindings.json').read_text()).items()}
    for f in functions:
        addresses[f['name'] if f['name'].startswith('?') else '_' + f['name']] = int(f['address'], 0)
    _, pe = original(VERSION)
    fixups = base_relocations(pe)
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / 'input-snapshot.json').write_text(json.dumps(dict(config=config, functions=functions, settings=settings), indent=2))
    attempts = []
    if options.source and (OUT / 'attempts.json').exists():
        attempts = [a for a in json.loads((OUT / 'attempts.json').read_text())
                    if a['source'] in config['sources'] and a['source'] not in selected_sources]
        # A physical source split can replace an earlier enabled path. Fill
        # missing sources so a partial refresh still yields a complete summary.
        configured = {a['source'] for a in attempts if a['profile'] == 'configured'}
        selected_sources.extend(s for s in config['sources']
                                if s not in configured and s not in selected_sources)
    retained_count = len(attempts)
    with ThreadPoolExecutor(max_workers=options.workers) as executor:
        pending = []
        for source in selected_sources:
            unit_settings = settings[source]
            compiler = config.get('compilers', {}).get(unit_settings['compiler'], unit_settings['compiler'])
            selected = [f for f in functions if f.get('source') == source]
            scoped = dict(addresses)
            scoped.update({f['name'] if f['name'].startswith('?') else '_' + f['name']:
                           int(f['address'], 0) for f in selected})
            scoped.update({k: int(v, 0) for k, v in config.get('source_bindings', {}).get(source, {}).items()})
            for profile, flags in profiles(unit_settings['flags'], compiler):
                pending.append(executor.submit(attempt, source, unit_settings, compiler, profile,
                                               flags, selected, scoped, pe, fixups))
        for future in as_completed(pending):
            attempts.append(future.result())
            if (len(attempts) - retained_count) % 25 == 0:
                print(f'{len(attempts) - retained_count}/{len(pending)} profiles attempted', flush=True)
                temporary = OUT / 'attempts.tmp.json'
                temporary.write_text(json.dumps(attempts, indent=2) + '\n')
                temporary.replace(OUT / 'attempts.json')
    (OUT / 'attempts.json').write_text(json.dumps(attempts, indent=2) + '\n')
    units = []
    for source in config['sources']:
        variants = [a for a in attempts if a['source'] == source]
        baseline = next(a for a in variants if a['profile'] == 'configured')
        baseline_exact = {f['name'] for f in baseline['functions'] if f['exact']}
        improvements = []
        for variant in variants:
            exact = {f['name'] for f in variant['functions'] if f['exact']}
            if exact - baseline_exact:
                improvements.append(dict(profile=variant['profile'], gained=sorted(exact - baseline_exact),
                                         lost=sorted(baseline_exact - exact)))
        units.append(dict(source=source, status=baseline['status'],
                          mapped_functions=baseline['mapped_functions'],
                          configured_exact=baseline.get('exact_count', 0),
                          best_exact=max(a.get('exact_count', 0) for a in variants),
                          improvements=improvements, profiles=len(variants),
                          completed_tu=False))
    summary = dict(enabled_tus=len(units), profiles=len(attempts),
                   compiled_profiles=sum(a['compiled'] for a in attempts),
                   statuses=dict(Counter(u['status'] for u in units)),
                   units_with_improvements=sum(bool(u['improvements']) for u in units), units=units)
    (OUT / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps({k: v for k, v in summary.items() if k != 'units'}, indent=2))


if __name__ == '__main__':
    main()
