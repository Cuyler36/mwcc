#!/usr/bin/env python3
"""Find relocation-aware 1.2.5 function candidates in 3.0a5.2.

Requires capstone (locally: python -m pip install --target build/python capstone==5.0.6).
Only writes evidence under build/: candidates are not automatically marked Matching.
"""
import json
import re
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "build/python"))
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM
from compare import base_relocations
from pe import PEFile


def main():
    old = PEFile(Path("build/compilers/GC/1.2.5/mwcceppc.exe"))
    new = PEFile(Path("build/compilers/GC/3.0a5.2/mwcceppc.exe"))
    functions = json.loads(Path("config/GC_1_2_5/functions.json").read_text())
    entries = {int(m[1], 16) for m in re.finditer(r" at ([0-9a-fA-F]+)$", Path("build/gc3-ghidra-functions.txt").read_text(), re.M)}
    fixups = base_relocations(old)
    dis = Cs(CS_ARCH_X86, CS_MODE_32)
    dis.detail = True
    sections = [(s, new.data[s.file_offset:s.file_offset + s.file_size]) for s in new.sections
                if s.characteristics & 0x20000000]
    matches = []
    for function in functions:
        address, size = int(function["address"], 0), function["size"]
        if size < 12 or "source" not in function:
            continue
        body = old.read(address, size)
        masked = set()
        for fixup in fixups:
            if address <= fixup and fixup + 4 <= address + size:
                masked.update(range(fixup - address, fixup - address + 4))
        for insn in dis.disasm(body, address):
            if (insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP)) and insn.operands and insn.operands[0].type == X86_OP_IMM:
                target = insn.operands[0].imm
                if not address <= target < address + size:
                    start = insn.address - address + insn.imm_offset
                    masked.update(range(start, start + insn.imm_size))
        if size - len(masked) < 12:
            continue
        pattern = re.compile(b"".join(b"." if i in masked else re.escape(bytes([v])) for i, v in enumerate(body)), re.S)
        hits = [s.virtual_address + m.start() for s, data in sections for m in pattern.finditer(data)
                if s.virtual_address + m.start() in entries]
        if len(hits) == 1:
            matches.append(dict(function, baseline_address=function["address"], address=f"0x{hits[0]:08x}",
                                masked_bytes=len(masked), evidence="unique byte pattern at Ghidra function entry; relocation and external branch operands masked"))
            matches[-1]["baseline_source"] = matches[-1].pop("source")
    counts = Counter(m["address"] for m in matches)
    matches = [m for m in matches if counts[m["address"]] == 1]
    Path("build/GC_3_0a5_2/function-candidates.json").write_text(json.dumps(matches, indent=2) + "\n")
    print(f"{len(matches)} unique candidates; these require relocation and compiler verification")
    for source, count in Counter(m["baseline_source"] for m in matches).most_common(20):
        print(f"  {count:3} {source}")


if __name__ == "__main__":
    main()
