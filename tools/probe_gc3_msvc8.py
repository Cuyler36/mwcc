#!/usr/bin/env python3
"""Compile unchanged sources with local MSVC and look for GC 3.0a5.2 matches.

No installer or vcvars script is run. Environment changes apply only to cl's
child process. Results and MSVC-compatible header copies live under build/.
"""
import itertools
import argparse
import hashlib
import json
import os
import re
import subprocess
from pathlib import Path

from compare import read_object, function_section
from pe import PEFile


def main():
    root = Path(__file__).resolve().parents[1]
    os.chdir(root)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolchain", choices=("msvc6", "msvc71", "msvc8"), default="msvc8")
    toolchain = parser.parse_args().toolchain
    configurations = {
        "msvc6": ("msvc6/VC98", "12.00.8804",
            "https://github.com/itsmattkc/MSVC600/tree/001c4bafdcf2ef4b474d693acccd35a91e848f40",
            {"cl.exe": "1bf99f206271ecdbd13da2829192ea2c02e2a44c740b8d72935d5d9cb753b156",
             "c1.dll": "fc6771ed73524417877f1263604bf8b9b9cd403c8cfb72b2e25737bdc81d592e",
             "c2.dll": "3f2b5f43e3172d38651886bd2599957298d9fa42d06684a752e381c17572b12f"}),
        "msvc71": ("msvc71/Microsoft Visual C++ Toolkit 2003", "13.10.6030",
            "https://github.com/We-the-People-civ4col-mod/Compiler/tree/ca74c1a3c708dce5da3c358d169794ccce907bb6",
            {"cl.exe": "333254d73ee602f6ec14b00e9bf40f533a1b181429943e3634971642af00c9f7",
             "c1.dll": "a47ff094f591ac85777f568c44f2d0c9e94295184faa1fb785bbc6f89d887f07",
             "c2.dll": "7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5"}),
        "msvc8": ("msvc8", "14.00.50727.42",
            "https://github.com/widberg/msvc8.0/tree/936f93b9e9e92943ed5c9398d24712a32c2e9fe4", {
        "cl.exe": "3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7",
        "c1.dll": "be84b91b22bf67435525904e63db3c33afa6ea64dae9200e73db23439804254a",
        "c2.dll": "ebca6ef587d6e028b50cc79fe71dd6155230ecb51014295399e8f00e8865ff86",
        }),
    }
    directory, expected_version, tool_source, hashes = configurations[toolchain]
    compiler_root = root / "build/compilers" / directory
    compiler = compiler_root / "bin/cl.exe"
    for filename, expected in hashes.items():
        if hashlib.sha256(compiler.with_name(filename).read_bytes()).hexdigest() != expected:
            raise SystemExit(f"Unexpected {toolchain} tool contents: {filename}")
    output = root / "build/GC_3_0a5_2/probes" / toolchain
    output.mkdir(parents=True, exist_ok=True)
    headers = output / "include"
    # Translate Metrowerks' per-record packing, preserving the source headers.
    translated = []
    for header in Path("include").rglob("*.h"):
        data = header.read_bytes()
        patched = re.sub(rb"#pragma options align\s*=\s*mac68k", b"#pragma pack(push, 2)", data)
        patched = re.sub(rb"#pragma options align\s*=\s*reset", b"#pragma pack(pop)", patched)
        # VC80 requires the calling convention after the return type here.
        patched = re.sub(rb"extern (__stdcall|__cdecl) (\w+)", rb"extern \2 \1", patched)
        if patched != data:
            target = headers / header.relative_to("include")
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(patched)
            translated.append(header.as_posix())
    env = dict(os.environ, INCLUDE=str(compiler_root / "include"), CL="", _CL_="")
    version = subprocess.run([str(compiler)], env=env, capture_output=True, text=True, check=True)
    banner = version.stderr.strip() or version.stdout.strip()
    if expected_version not in banner:
        raise SystemExit(f"Unexpected compiler version: {banner}")
    settings = json.loads(Path("config/sources.json").read_text())
    baseline = json.loads(Path("config/GC_1_2_5/functions.json").read_text())
    entries = {int(m[1], 16) for m in re.finditer(r" at ([0-9a-fA-F]+)$", Path("build/gc3-ghidra-functions.txt").read_text(), re.M)}
    pe = PEFile(Path("build/compilers/GC/3.0a5.2/mwcceppc.exe"))
    sections = [(s, pe.data[s.file_offset:s.file_offset + s.file_size]) for s in pe.sections
                if s.characteristics & 0x20000000]
    results = []
    sources = ("src/driver/Targets.c", "src/frontend/CInt64.c", "src/backend/BitVectors.c")
    excluded = []
    for source in sources:
        compile_source = source
        if toolchain != "msvc8" and source == "src/driver/Targets.c":
            # Old MSVC rejects this baseline caller's conflicting local prototype.
            # Omit only that caller; retain every other function body verbatim.
            name = "Targets_ReportOperatingSystemError"
            data = Path(source).read_bytes()
            data, count = re.subn(
                rb"unsigned char Targets_ReportOperatingSystemError\([^\n]+\)\r?\n\{.*?\r?\n\}",
                b"/* Conflicting-prototype caller excluded from this compiler probe. */", data, flags=re.S)
            if count != 1:
                raise SystemExit("Unexpected Targets.c caller layout")
            adapted = output / "src/driver/Targets.c"
            adapted.parent.mkdir(parents=True, exist_ok=True)
            adapted.write_bytes(data)
            compile_source = str(adapted)
            excluded.append(name)
        tested = 0
        found = {}
        security_flags = ("",) if toolchain == "msvc6" else ("/GS", "/GS-")
        for optimization, frame, security, inline in itertools.product(
                ("/Od", "/O1", "/O2", "/Ox"), ("/Oy", "/Oy-"), security_flags, ("/Ob0", "/Ob2")):
            label = "_".join(s[1:].replace("-", "off") for s in (optimization, frame, security, inline) if s)
            directory = output / label
            directory.mkdir(exist_ok=True)
            obj = directory / (Path(source).name + ".obj")
            flags = ["/nologo", "/c", "/TC", optimization, frame, security, inline, "/Gy", "/Zl",
                     "/Dinline=__inline", "/DVERSION=3", "/I" + str(headers), "/Iinclude", "/Iinclude/libc",
                     *("/I" + d for d in settings[source].get("include_dirs", []))]
            flags = [flag for flag in flags if flag]
            command = [str(compiler), *flags, "/Fo" + str(obj), compile_source]
            result = subprocess.run(command, env=env, capture_output=True, text=True)
            (directory / (Path(source).name + ".log")).write_text(result.stdout + result.stderr)
            if result.returncode or "D9002" in result.stdout + result.stderr:
                raise SystemExit(f"Compile failed ({source}, {label}); see {directory / (Path(source).name + '.log')}")
            symbols, objects = read_object(obj)
            tested += 1
            matches = []
            for function in baseline:
                if function.get("source") != source:
                    continue
                if function["name"] in excluded:
                    continue
                try:
                    section, start, end = function_section(symbols, objects, "_" + function["name"])
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
                    match = dict(name=function["name"], address=f"0x{hits[0]:08x}", size=len(body))
                    matches.append(match)
                    found[(match["name"], match["address"])] = match
            results.append(dict(source=source, flags=flags, object=obj.relative_to(root).as_posix(),
                                matches=matches))
        print(f"{source}: {tested} flag combinations, {len(found)} unique function/address candidates", flush=True)
    report = dict(compiler=banner, tool_sha256=hashes,
                  tool_source=tool_source,
                  header_adaptation="inline=__inline; mac68k/reset -> pack(push,2)/pack(pop); reorder calling-convention declarations",
                  translated_headers=translated, excluded_functions=excluded, results=results)
    (Path("build/GC_3_0a5_2") / (toolchain + "-probes.json")).write_text(json.dumps(report, indent=2) + "\n")


if __name__ == "__main__":
    main()
