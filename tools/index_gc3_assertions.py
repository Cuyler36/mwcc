"""Read-only GC 3.0a5.2 Windows source-string and assertion caller inventory.

Requires capstone (pip install --target build/python capstone), or an installed
capstone module. Uses tools/pe.py; it never executes or mutates the input PE.
Example, from the repository root:
  python tools/index_gc3_assertions.py --exe build/compilers/GC/3.0a5.2/mwcceppc.exe \
      --functions build/gc3-ghidra-functions-current.txt

The function export contains one "name at 00401000" line per Ghidra function.
Helpers and signatures are specific to the original PE with SHA1
79683505e7fc6bb63e5c169f21623df272dd2262. No inferred linker-order TU boundaries
are asserted. Header assertions and mixed-source callers retain ambiguity.
"""
import sys, re, json, argparse, hashlib
from pathlib import Path
from collections import defaultdict, Counter
ROOT = Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description=__doc__,formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument('--exe',type=Path,required=True,help='Original GC 3.0a5.2 Windows PE')
parser.add_argument('--functions',type=Path,required=True,help='Ghidra function export, one name at ADDRESS per line')
parser.add_argument('--output',type=Path,default=ROOT/'build/GC_3_0a5_2/inventory/assertions',help='Output directory; defaults to the build inventory')
args=parser.parse_args()
OUT=args.output
OUT.mkdir(parents=True,exist_ok=True)
sys.path[:0] = [str(ROOT/'build/python'), str(ROOT/'tools')]
from pe import PEFile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_ESP
if hashlib.sha1(args.exe.read_bytes()).hexdigest() != '79683505e7fc6bb63e5c169f21623df272dd2262':
    parser.error('helper addresses are verified only for the original GC 3.0a5.2 PE')
pe = PEFile(args.exe)
starts = []
for line in args.functions.read_text().splitlines():
    m = re.fullmatch(r'(.+) at ([0-9a-fA-F]{8})',line)
    if m: starts.append((int(m[2],16),m[1]))
starts = sorted(dict(starts).items())
if not starts: parser.error('function export contains no name at ADDRESS records')
strings = {}
for sec in pe.sections:
    if sec.characteristics & 0x20000000 or not sec.file_size: continue
    data = pe.read(sec.virtual_address,sec.file_size)
    for m in re.finditer(rb'[ -~]{2,}\x00',data):
        val = m[0][:-1].decode('ascii')
        if re.fullmatch(r'(?:[A-Za-z]:)?[A-Za-z0-9_./\\: -]+\.(?:c|cp|cpp|cxx|h|hpp)',val,re.I):
            strings[sec.virtual_address+m.start()] = val
helpers = {0x42ddb0:('CLIO_ReportAssertionFailure',1),0x45a250:('CError_Internal',0),0x44ca40:('FUN_0044ca40_preprocessor_file_line_report',2)}
helper_evidence=[
    {'address':'0x0042ddb0','name':'CLIO_ReportAssertionFailure','arguments':['expression','file','function','line'],'evidence':'Existing GC3 assertion ABI; include/driver/CLIOAssert.h. Baseline name identifies the analogous helper; Mac symbols do not directly export it.'},
    {'address':'0x0045a250','name':'CError_Internal','arguments':['file','line'],'evidence':'Windows Ghidra decompile confirms file/line forwarded to snprintf then report_diagnostic and longjmp. Baseline src/frontend/CError.c and include/compiler/CError.h give the name/signature.'},
    {'address':'0x0044ca40','name':'FUN_0044ca40','arguments':['diagnostic_kind','diagnostic_code','file','unused','line'],'evidence':'Windows Ghidra decompile formats literal while executing in file %s, line using arguments 3 and 5, then calls FUN_00459800. No original symbol name is asserted.'}
]
(OUT/'helper-evidence.json').write_text(json.dumps(helper_evidence,indent=2)+'\n')
def filename_at(address):
    if address in strings: return strings[address]
    if not address: return None
    try: value=pe.read(address,256).split(b'\0',1)[0].decode('ascii')
    except (ValueError,UnicodeDecodeError): return None
    if re.fullmatch(r'(?:[A-Za-z]:)?[A-Za-z0-9_./\\: -]+\.(?:c|cp|cpp|cxx|h|hpp)',value,re.I):
        strings[address]=value
        return value
    return None
cs = Cs(CS_ARCH_X86, CS_MODE_32); cs.detail=True; cs.skipdata=True
refs=[]; calls=[]
def immediate(ins):
    return ins.operands[0].imm & 0xffffffff if ins.operands and ins.operands[0].type == X86_OP_IMM else None
for idx,(start,name) in enumerate(starts):
    sec = pe.section_for_address(start)
    if not sec.characteristics & 0x20000000: continue
    end = min(starts[idx+1][0] if idx+1<len(starts) else start+0x10000,sec.virtual_address+sec.file_size)
    hist=[]; pushes=[]; stack={}; registers={}
    for ins in cs.disasm(pe.read(start,end-start),start):
        if ins.id == 0: continue
        ops=ins.operands
        hist.append({'address':f'0x{ins.address:08x}','instruction':ins.mnemonic+' '+ins.op_str})
        hist=hist[-18:]
        for op in ops:
            ptr=(op.imm&0xffffffff) if op.type==X86_OP_IMM else (op.mem.disp&0xffffffff) if op.type==X86_OP_MEM and not op.mem.base and not op.mem.index else None
            if filename_at(ptr):
                refs.append({'function_address':f'0x{start:08x}','function_name':name,'instruction_address':f'0x{ins.address:08x}','instruction':ins.mnemonic+' '+ins.op_str,'string_address':f'0x{ptr:08x}','source_string':strings[ptr]})
        if ins.mnemonic == 'push':
            value=immediate(ins)
            if value is None and ops[0].type==X86_OP_REG: value=registers.get(ops[0].reg)
            pushes.append(value)
        if ins.mnemonic=='mov' and len(ops)==2:
            value = (ops[1].imm&0xffffffff) if ops[1].type==X86_OP_IMM else registers.get(ops[1].reg) if ops[1].type==X86_OP_REG else None
            if ops[0].type==X86_OP_REG: registers[ops[0].reg]=value
            elif ops[0].type==X86_OP_MEM and ops[0].mem.base==X86_REG_ESP and not ops[0].mem.index: stack[ops[0].mem.disp//4]=value
        if ins.mnemonic=='call':
            dest=immediate(ins)
            if dest in helpers:
                helper,argidx=helpers[dest]
                ptr = pushes[-1-argidx] if len(pushes)>argidx else stack.get(argidx)
                source=filename_at(ptr)
                line_idx={0x42ddb0:3,0x45a250:1,0x44ca40:4}[dest]
                line=pushes[-1-line_idx] if len(pushes)>line_idx else stack.get(line_idx)
                calls.append({'function_address':f'0x{start:08x}','function_name':name,'call_address':f'0x{ins.address:08x}','helper':helper,'source_string':source,'source_string_address':f'0x{ptr:08x}' if ptr else None,'source_line':line,'confidence':'direct_argument' if source else 'unresolved_argument','context':hist.copy()})
            pushes=[];stack={};registers={}
        elif ins.mnemonic in ('ret','jmp'):
            pushes=[];stack={};registers={}
groups=defaultdict(list)
for c in calls:
    if c['source_string']: groups[c['function_address']].append(c)
functions=[]
for addr,items in groups.items():
    srcs=sorted(set(x['source_string'] for x in items)); tus=[s for s in srcs if re.search(r'\.(c|cp|cpp|cxx)$',s,re.I)]
    functions.append({'function_address':addr,'function_name':items[0]['function_name'],'source_files':srcs,'proposed_tu':tus[0] if len(tus)==1 else None,'confidence':'direct_assertion_single_source' if len(tus)==1 else 'ambiguous_or_header_only','call_addresses':[i['call_address'] for i in items]})
summary={'filename_strings':len(strings),'distinct_filename_strings':len(set(strings.values())),'filename_references':len(refs),'assertion_calls':len(calls),'resolved_assertion_calls':sum(bool(c['source_string']) for c in calls),'functions_with_source_assertions':len(functions),'single_source_tu_functions':sum(bool(f['proposed_tu']) for f in functions),'source_files':sorted(set(s for f in functions for s in f['source_files'])),'limitations':['Function ranges use exported Ghidra entry points; gaps are not automatically code.','Direct call argument recovery is a straight-line conservative heuristic. Context is retained for audit.','Source assertions identify callers; no attribution of intervening functions is made.','Header filenames do not establish translation unit membership.']}
for filename,obj in [('strings.json',[{'address':f'0x{a:08x}','value':s} for a,s in sorted(strings.items())]),('references.json',refs),('calls.json',calls),('functions.json',functions),('summary.json',summary)]:
    (OUT/filename).write_text(json.dumps(obj,indent=2)+'\n')
current=json.loads((ROOT/'config/GC_3_0a5_2/functions.json').read_text())
byaddr={x['address']:x for x in current}
conflicts=[dict(x,existing_source=byaddr[x['function_address']]['source']) for x in functions if x['proposed_tu'] and x['function_address'] in byaddr and Path(byaddr[x['function_address']]['source']).name!=x['proposed_tu']]
(OUT/'mapping-conflicts.json').write_text(json.dumps(conflicts,indent=2)+'\n')
baseline=json.loads((ROOT/'config/GC_1_2_5/functions.json').read_text())
baseline_names={Path(x['source']).name for x in baseline}
source_inventory=[]
for source in sorted(set(strings.values())):
    source_calls=[x for x in calls if x['source_string']==source]
    source_functions=[x for x in functions if source in x['source_files']]
    source_inventory.append({'source':source,'present_in_baseline_by_filename':source in baseline_names,'is_header':bool(re.search(r'\.(h|hpp)$',source,re.I)),'assertion_calls':len(source_calls),'asserting_functions':len(source_functions),'single_source_functions':sum(x['proposed_tu']==source for x in source_functions),'function_addresses':[x['function_address'] for x in source_functions],'reference_count':sum(x['source_string']==source for x in refs)})
(OUT/'source-inventory.json').write_text(json.dumps(source_inventory,indent=2)+'\n')
inline=[]
for ref in refs:
    if ref['source_string'] in ('CError.c','CPreprocessor.c'):
        inline.append(dict(ref,confidence='filename_reference_inline_diagnostic_needs_review'))
(OUT/'inline-diagnostic-references.json').write_text(json.dumps(inline,indent=2)+'\n')
print(json.dumps(summary,indent=2))


