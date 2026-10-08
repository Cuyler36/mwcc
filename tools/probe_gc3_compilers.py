#!/usr/bin/env python3
"""Compare Windows MWCC output for unchanged-source probes against GC 3.0a5.2.

Uses the Ghidra entry-point snapshot exported to build/gc3-ghidra-functions.txt.
Matches are evidence of compatible code generation, not compiler identification.
"""
import json
import argparse
import hashlib
import os
import re
import subprocess
import sys
from pathlib import Path

from compare import read_object, function_section
from pe import PEFile


def main():
    os.chdir(Path(__file__).resolve().parents[1])
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compilers", nargs="+", default=["pro53", "pro6"])
    parser.add_argument("--report", default="build/GC_3_0a5_2/compiler-probes.json")
    options = parser.parse_args()
    settings = json.loads(Path("config/sources.json").read_text())
    baseline = json.loads(Path("config/GC_1_2_5/functions.json").read_text())
    entries = {int(m[1], 16) for m in re.finditer(r" at ([0-9a-fA-F]+)$", Path("build/gc3-ghidra-functions.txt").read_text(), re.M)}
    pe = PEFile(Path("build/compilers/GC/3.0a5.2/mwcceppc.exe"))
    sections = [(s, pe.data[s.file_offset:s.file_offset + s.file_size]) for s in pe.sections
                if s.characteristics & 0x20000000]
    results = []
    for compiler in options.compilers:
        executable = Path(f"build/compilers/{compiler}/mwcc.exe")
        version = subprocess.run([str(executable), "-version"], capture_output=True, text=True, check=True)
        banner = version.stdout + version.stderr
        digest = hashlib.sha256(executable.read_bytes()).hexdigest()
        for source in ("src/driver/Targets.c", "src/frontend/CInt64.c", "src/backend/BitVectors.c"):
            config = settings[source]
            output = f"build/GC_3_0a5_2/probes/{compiler}/{Path(source).name}.obj"
            args = ["-c", *config["flags"], "-DVERSION=3",
                    *(f"-I{d}" for d in config.get("include_dirs", [])), "-Iinclude", "-i-",
                    *(f"-I{d}" for d in config.get("system_include_dirs", [])), "-Iinclude/libc", source, "-o", output]
            compiled = subprocess.run([sys.executable, "tools/run_compiler.py", "--out", output, "--",
                                       str(executable), *args], capture_output=True, text=True)
            log = Path(output).with_suffix(".log")
            log.write_text(compiled.stdout + compiled.stderr)
            if compiled.returncode:
                raise SystemExit(f"Compile failed ({compiler}, {source}); see {log}")
            symbols, objects = read_object(Path(output))
            matches = []
            for f in baseline:
                if f.get("source") != source:
                    continue
                try:
                    section, start, end = function_section(symbols, objects, "_" + f["name"])
                except ValueError:
                    continue
                body = section["data"][start:end].rstrip(b"\x90\xcc")
                masked = {p - start for off, _, kind in section["relocs"] if kind in (6, 7, 20)
                          for p in range(off, off + 4) if start <= p < start + len(body)}
                if len(body) - len(masked) < 12:
                    continue
                pattern = re.compile(b"".join(b"." if i in masked else re.escape(bytes([b])) for i, b in enumerate(body)), re.S)
                hits = [s.virtual_address + m.start() for s, data in sections for m in pattern.finditer(data)
                        if s.virtual_address + m.start() in entries]
                if len(hits) == 1:
                    matches.append(dict(name=f["name"], address=f"0x{hits[0]:08x}", size=len(body),
                                        masked_operand_bytes=len(masked),
                                        bytes_equal=pe.read(hits[0], len(body)) == body))
            results.append(dict(compiler=compiler, compiler_banner=banner, tool_sha256=digest,
                                source=source, flags=args, matches=matches))
            print(f"{compiler}: {source}: {len(matches)} unique candidate matches")
    Path(options.report).write_text(json.dumps(results, indent=2) + "\n")


if __name__ == "__main__":
    main()
