#!/usr/bin/env python3
"""Compile the complete 1.2.5 source inventory and find conservative GC 3.0 candidates.

This discovery pass writes build/ evidence only. It never marks candidates Matching.
"""
import argparse
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from compare import function_section, original, read_object


def compile_unit(source, settings, variant):
    output = Path(f"build/GC_3_0a5_2/baseline-probes/{variant}/{source}.obj")
    flags = ["-O4", "-opt", variant, "-inline", "auto", "-sym", "off", "-Cpp_exceptions", "off"]
    args = ["-c", *flags, "-DVERSION=3", *(f"-I{x}" for x in settings.get("include_dirs", [])),
            "-Iinclude", "-i-", *(f"-I{x}" for x in settings.get("system_include_dirs", [])), "-Iinclude/libc"]
    if output.exists() and output.stat().st_mtime > max(Path(source).stat().st_mtime,
                                                      Path(__file__).stat().st_mtime):
        return dict(source=source, variant=variant, flags=args, object=output.as_posix(), success=True)
    result = subprocess.run([sys.executable, "tools/run_compiler.py", "--out", str(output), "--",
                             "build/compilers/cw94/mwcc.exe", *args, source, "-o", str(output)],
                            capture_output=True, text=True)
    output.with_suffix(".log").write_text(result.stdout + result.stderr)
    return dict(source=source, variant=variant, flags=args, object=output.as_posix(),
                success=result.returncode == 0)


def discover(compilations):
    _, pe = original("GC_3_0a5_2")
    entries = {int(m[1], 16) for m in re.finditer(r" at ([0-9a-fA-F]+)$",
               Path("build/gc3-ghidra-functions.txt").read_text(), re.M)}
    code = [(s.virtual_address, pe.data[s.file_offset:s.file_offset + s.file_size]) for s in pe.sections
            if s.characteristics & 0x20000000]
    baseline = json.loads(Path("config/GC_1_2_5/functions.json").read_text())
    by_source = defaultdict(list)
    for function in baseline:
        by_source[function["source"]].append(function)
    candidates = []
    for compilation in compilations:
        if not compilation["success"]:
            continue
        symbols, sections = read_object(Path(compilation["object"]))
        for function in by_source[compilation["source"]]:
            symbol = function["name"] if function["name"].startswith("?") else "_" + function["name"]
            try:
                sec, begin, end = function_section(symbols, sections, symbol)
            except ValueError:
                continue
            body = sec["data"][begin:end].rstrip(b"\x90\xcc")
            masked = {i - begin for off, _, kind in sec["relocs"] if kind in (6, 7, 20)
                      for i in range(off, off + 4) if begin <= i < begin + len(body)}
            if len(body) - len(masked) < 12:
                continue
            pattern = re.compile(b"".join(b"." if i in masked else re.escape(bytes([v]))
                                         for i, v in enumerate(body)), re.S)
            hits = [base + m.start() for base, data in code for m in pattern.finditer(data)
                    if base + m.start() in entries]
            if len(hits) == 1:
                candidates.append(dict(name=function["name"], symbol=symbol, source=compilation["source"],
                                       address=f"0x{hits[0]:08x}", size=len(body),
                                       variant=compilation["variant"], object=compilation["object"],
                                       masked_bytes=len(masked), baseline_address=function["address"]))
    return candidates


def main():
    os.chdir(Path(__file__).resolve().parents[1])
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--discover-only", action="store_true")
    options = parser.parse_args()
    manifest = Path("build/GC_3_0a5_2/baseline-compilations.json")
    if options.discover_only:
        compilations = json.loads(manifest.read_text())
    else:
        sources = json.loads(Path("config/sources.json").read_text())
        compilations = []
        with ThreadPoolExecutor(max_workers=3) as executor:
            pending = [executor.submit(compile_unit, source, settings, variant)
                       for source, settings in sources.items() for variant in ("speed", "space")]
            for result in as_completed(pending):
                compilation = result.result()
                compilations.append(compilation)
                if len(compilations) % 30 == 0 or not compilation["success"]:
                    print(f"{len(compilations)}/{len(pending)} compiled; "
                          f"{sum(not c['success'] for c in compilations)} failures; "
                          f"{compilation['source']} ({compilation['variant']})", flush=True)
        manifest.write_text(json.dumps(compilations, indent=2) + "\n")
    candidates = discover(compilations)
    Path("build/GC_3_0a5_2/baseline-compiled-candidates.json").write_text(json.dumps(candidates, indent=2) + "\n")
    unique = {(c["name"], c["address"]) for c in candidates}
    print(f"{len(unique)} distinct function/address candidates from {len(candidates)} compiler variants")
    print(Counter(c["source"] for c in candidates).most_common(20))


if __name__ == "__main__":
    main()
