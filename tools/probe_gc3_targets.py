#!/usr/bin/env python3
"""Compile the symbol-identified Targets.c and resolve every relocation for comparison."""
import json
import hashlib
import os
import subprocess
import sys
from pathlib import Path

from compare import base_relocations, original, read_object, resolve_function

FUNCTIONS = [
    ("SetParserToolInfo", 0x41f5c9, 56),
    ("ParserToolMatchesPlugin", 0x41f601, 171),
    ("ParserToolHandlesPanels", 0x41f6ac, 106),
    ("SetupParserToolOptions", 0x41f716, 47),
]
BINDINGS = dict(_pTool=0x711b48, _parseopts=0x70f380,
                _CLIO_ReportAssertionFailure=0x42ddb0, _CLPFatalError=0x41e784,
                _CLIO_CompareStringsIgnoreCase=0x424b60,
                _Options_Init=0x43082b, _Options_AddList=0x430a50,
                _Options_SortOptions=0x430935)


def main():
    os.chdir(Path(__file__).resolve().parents[1])
    _, pe = original("GC_3_0a5_2")
    fixups = set(base_relocations(pe))
    results = []
    msvc = {"msvc6": "msvc6/VC98", "msvc71": "msvc71/Microsoft Visual C++ Toolkit 2003", "msvc8": "msvc8"}
    for compiler in ("pro53", "pro6", "pro7", "pro8", "cw94", *msvc):
        optimizations = ("/Od", "/O1", "/O2", "/Ox") if compiler in msvc else (
            "-O0", "-O1", "-O2", "-O3", "-O4", "-O1,p", "-O2,p", "-O3,p", "-O4,p",
            "-O4 -opt space", "-O4 -opt schedule", "-O4 -opt lifetimes",
            "-O4 -opt space,schedule,lifetimes", "-O2 -opt schedule,lifetimes")
        for optimization in optimizations:
            label = optimization[1:].replace(',', '_').replace(' ', '_')
            output = f"build/GC_3_0a5_2/targets-probes/{compiler}/{label}.obj"
            flags = [*optimization.split(), "-opt", "intrinsics", "-sym", "off", "-Cpp_exceptions", "off",
                     "-DVERSION=3", "-Iinclude"]
            command = [sys.executable, "tools/run_compiler.py", "--out", output, "--",
                                  f"build/compilers/{compiler}/mwcc.exe", "-c", *flags,
                                  "src/GC_3_0a5_2/driver/Targets.c", "-o", output]
            if compiler in msvc:
                flags = ["/nologo", "/c", "/TC", optimization, "/Oy", "/Ob0", "/Gy", "/Zl",
                         "/DVERSION=3", "/Iinclude"]
                if compiler != "msvc6":
                    flags.append("/GS-")
                command = [f"build/compilers/{msvc[compiler]}/bin/cl.exe", *flags,
                           "/Fo" + output, "src/GC_3_0a5_2/driver/Targets.c"]
                Path(output).parent.mkdir(parents=True, exist_ok=True)
            run = subprocess.run(command, env=dict(os.environ, CL="", _CL_=""),
                                 capture_output=True, text=True)
            if run.returncode:
                raise SystemExit(run.stdout + run.stderr)
            symbols, sections = read_object(Path(output))
            functions = []
            for name, address, size in FUNCTIONS:
                body, relocations = resolve_function(symbols, sections, "_" + name,
                                                     address, BINDINGS, pe, size)
                expected = pe.read(address, size)
                body = body.rstrip(b"\x90\xcc")
                differences = [(i, a, b) for i, (a, b) in enumerate(zip(body, expected)) if a != b]
                fixups_match = {address + r['offset'] for r in relocations if r['kind'] == 6} == {
                    f for f in fixups if address <= f < address + size}
                exact = body == expected and fixups_match
                functions.append(dict(name=name, address=f"0x{address:08x}",
                                      target_size=size, compiled_size=len(body), exact=exact,
                                      differences=differences[:12], relocations=relocations,
                                      base_relocations_match=fixups_match))
            executable = Path(command[0] if compiler in msvc else f"build/compilers/{compiler}/mwcc.exe")
            results.append(dict(compiler=compiler, flags=flags, functions=functions,
                                tool_sha256=hashlib.sha256(executable.read_bytes()).hexdigest(),
                                source_sha256=hashlib.sha256(Path("src/GC_3_0a5_2/driver/Targets.c").read_bytes()).hexdigest()))
            print(f"{compiler} {optimization}: " + ", ".join(
                f"{f['name']}={'MATCH' if f['exact'] else str(f['compiled_size']) + ' bytes'}" for f in functions))
    Path("build/GC_3_0a5_2/targets-probes.json").write_text(json.dumps(results, indent=2) + "\n")


if __name__ == "__main__":
    main()
