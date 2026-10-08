# GC 3.0a5.2 port

Original: `build/compilers/GC/3.0a5.2/mwcceppc.exe`.
SHA-1: `79683505e7fc6bb63e5c169f21623df272dd2262`.
Ghidra: project `City Folk`, program `/mwcc/GC 3.0/mwcceppc.exe`.
Its executable path identifies the 3.0a5.2 compiler. Use this explicit program path in MCP calls.

## TU inventory and matching order

`translation-units.json` is the source checklist and per-TU attempt ledger.
Its initial inventory contains 262 units: 209 imported compiled sources and 53
original-only Windows source views. It records 1,984 known Windows functions,
including 905 not yet implemented, and keeps the Mac-only source checklist
separate. The original's remaining code and data stay in unknown section views.
The inventory is incomplete: assertions name callers, not every function in a
file, and 20 existing mappings conflict with their recovered filenames.
Seven mixed-source and 48 header-only diagnostic callers remain ambiguous.
Missing mappings do not prove that an imported TU is obsolete.

The Windows inventory resolves all 3,032 calls to three assertion/file-line
helpers. The Mac map has 62 explicit STABS source units and 1,070 named FUN
records, plus 12,129 ordinary symbols without implied source membership.
Regenerate the evidence with local Capstone installed under `build/python`:

```sh
python tools/index_gc3_symbols.py --symbols /path/to/mwccppc_pro8_syms
python tools/index_gc3_assertions.py --exe build/compilers/GC/3.0a5.2/mwcceppc.exe --functions build/gc3-ghidra-functions-current.txt
python tools/plan_gc3_units.py
python configure.py --version GC_3_0a5_2
ninja all_source progress
```

Matching proceeds by physical TU. Resolve ownership conflicts and added
functions first, then compare every emitted function, literal, initialized
data object, and BSS contribution with objdiff-cli. Record compiler experiments
and semantic differences in `attempts`; a compile or high similarity score is
not a functional-equivalence result. Mark completion only after reviewing the
known original inventory and strict code/data/relocation checks. Push each TU
as its review finishes. `source-splits.json` preserves physical splits and
canonical symbol names when rediscovering baseline mappings.

First matching priorities are the runtime setjmp unit, ResourceStrings.c,
ParserErrors.c, CLIncludeFileCache.c, and CLBrowser.c. Then handle the remaining
driver units, frontend, optimizer, backend, MSL, and runtime sources. New
original-only units remain explicit work items, rather than empty C stubs.

## setjmp: complete runtime unit

ResourceStrings.c also passes full-TU objdiff: two functions, 405 code bytes,
128 initialized literal bytes, and 448 BSS bytes. Its GC3 implementation uses
bounded `snprintf` calls and original `Res_*`, `rlist`, and `err` names. Local
BSS references are derived from validated original operands rather than global
compiler-generated symbol bindings. The Mac map's Res_Initialize/Res_Cleanup
have no identified retained Windows bodies; adjacent code and all direct
references to this static storage were reviewed. This platform difference is
recorded in the attempt ledger.

The MSL setjmp unit also passes complete-TU objdiff: `_Setjmp` at 0x00404920
(24 bytes) and `longjmp` at 0x00404940 (31 bytes). Both are naked assembly,
including the required zero-to-one `longjmp` return conversion. There are no
relocations, PE fixups, or allocated data contributions. Neighboring code is
separate and intervening bytes are NOP padding. The attempt ledger records the
remaining limit: Windows debug metadata does not independently give this TU's
original boundary; the implementation is inherited from the MSL source.

## Targets.c: complete symbol-identified unit

The 1.2.5 reconstruction's `src/driver/Targets.c` bundles 42 functions from
multiple original source files. The supplied `mwccppc_pro8_syms` STABS file
places the actual Targets.c at four functions. All four have corresponding
contiguous functions in the Windows 3.0a5.2 binary, from 0x0041f5c9 through
0x0041f744. The next function starts at 0x0041f750 after alignment padding.
There is no evidence here of an added or removed Targets.c function.
The embedded `Targets.c` string at 0x0066c914 is referenced by SetParserToolInfo.

| Recovered name | Baseline alias / 1.2.5 address | Windows 3.0a5.2 | Bytes |
| --- | --- | --- | --- |
| SetParserToolInfo | Targets_SetTool / 0x0040fcab | 0x0041f5c9 | 56 |
| ParserToolMatchesPlugin | Targets_MatchTool / 0x0040fce8 | 0x0041f601 | 171 |
| ParserToolHandlesPanels | Targets_MatchCommandLineOptions / 0x0040fd8e | 0x0041f6ac | 106 |
| SetupParserToolOptions | Targets_RegisterOptionLists / 0x0040fdfc | 0x0041f716 | 47 |

`src/GC_3_0a5_2/driver/Targets.c` reproduces all four functions (380 bytes),
including every resolved relocation and the PE loader's absolute fixup locations.
It builds with Windows 9.4's x86 compiler, version 3.2.5 build 428, using
`-O4 -opt space -sym off -Cpp_exceptions off`. This establishes complete
compatibility for this unit; it does not uniquely identify the original compiler.

Ported changes include the `parseopts.toolVersion` exception in the assertion,
the `????` language wildcard, and the Options_SortOptions call. The symbol file
also establishes the parameter order type/lang/cpu/os and the ParserTool fields.
Only the needed parseopts prefix is declared. Shared 1.2.5 common types are reused.
The assertion macro is in driver/OSAssert.h and is shared with the baseline
CLOverlays.c; its declaration is shared through CLIOAssert.h and CLIO.h.
CLIO_ReportAssertionFailure reuses the baseline interface name at 0x00414a90
for the 3.0 helper at 0x0042ddb0, with its observed four-argument ABI. The Mac
STABS file does not export this helper, so this name is a baseline port rather
than a symbol-verified original spelling. Other unresolved helpers retain aliases.

### Compiler experiments on the complete unit

`python tools/probe_gc3_targets.py` runs 82 compiler/flag combinations against
all four functions. Results include tool/source SHA256, complete relocation
resolutions, byte differences, sizes, and PE base-relocation checks in
`build/GC_3_0a5_2/targets-probes.json`. The target executable's SHA-1 is checked.
All toolchains are local portable extracts; the MSVC environment is scoped to
its child process. No global compiler installation is used.

| Compiler package | Best exact coverage in this matrix |
| --- | --- |
| Pro 5.3 | 0/4 |
| Pro 6 | 0/4 |
| Pro 7 | 0/4 |
| Pro 8 | 3/4 with -O4 -opt space |
| Windows 9.4 | 4/4 with -O4 -opt space |
| MSVC 6 / 7.1 / 8 | 0/4 each |

Pro 8 differs in ParserToolHandlesPanels (104 versus 106 bytes); the other
three match exactly. Earlier Pro versions and the tested MSVC settings do not
reproduce any complete function. MSVC 7.0 and Windows 9.2 remain untested.

### Correction to the earlier six matches

Those matches belong to ParserErrors.c (five) and Arguments.c (one), rather
than the original Targets.c. They remain exact with the baseline Pro 5.3 flags
and are now built from separate version-specific files using recovered names:

| Original source | Recovered function | Previous baseline alias | Windows address |
| --- | --- | --- | --- |
| ParserErrors.c | CLPReportError_V | Targets_FormatAndDispatchMessage | 0x0041e529 |
| ParserErrors.c | CLPReportWarning_V | Targets_ReportFormattedMessage | 0x0041e55e |
| ParserErrors.c | CLPStatus_V | format_and_forward_message | 0x0041e58c |
| ParserErrors.c | CLPAlert_V | format_and_report_message | 0x0041e5b4 |
| ParserErrors.c | CLPOSAlert_V | report_operating_system_error | 0x0041e5e7 |
| Arguments.c | Arg_UndoToken | Targets_DecrementCountAndGetTokenText | 0x0041f277 |

All 13 baseline reporting functions and 25 baseline argument functions are now
imported into these separate files, using the recovered symbol names and shared
baseline interfaces. The symbol file lists 15 and 28 functions respectively;
the additional functions and changed bodies still need porting. The baseline's
38 reporting/argument functions are not part of Targets.c's denominator.
The original ten verified Windows functions are renamed in Ghidra to match
the symbols. Shared compatibility changes preserve the 1.2.5 output.

## Compiler investigation

Do not assume the entire binary uses the 1.2.5 toolchain.

- Pro 5.3 (Windows/x86 2.3) and Pro 6 (Windows/x86 2.4 build 0131) both reproduce
  the same six baseline driver-bundle candidates under the existing per-source flags. This
  establishes compatibility for those functions, not the compiler's identity.
- Neither reproduces unique candidate bodies for the CInt64.c or BitVectors.c
  probes under the existing flags. Changed source and flags remain possible causes.
- Ghidra's `CInt64_And` at `0x004d9140` loads the second operand into ECX;
  both probes load it into EAX. This is a concrete difference to test with newer
  x86 compiler versions and scheduling options, before altering otherwise equivalent C.
- Startup and runtime code also differ. A single compiler choice for every
  translation unit has not been established.

Raw probe results are in `build/GC_3_0a5_2/compiler-probes.json`.
Re-run with `python tools/probe_gc3_compilers.py` after installing the Pro 5.3
and Pro 6 tools through `tools/download_tool.py`.

### Newer Windows/x86 MWCC comparison

The same three unchanged baseline source files were compiled with the existing
per-source flags and VERSION=3. All nine compilations succeed. No source or
header adaptations were needed. Results count unique candidates at Ghidra
function entries, ignoring four-byte COFF relocation operands and trailing
alignment padding; they are not yet additions to the verified build map.

| Product package | Compiler banner | Runtime build date | Baseline driver-bundle candidates | CInt64.c candidates | BitVectors.c candidates |
| --- | --- | --- | --- | --- | --- |
| Pro 7 | 2.4.5 build 199 | 2001-08-24 | 6 | 0 | 0 |
| Pro 8 | 3.0 build 314 | 2002-05-21 | 5 | 4 | 0 |
| Windows 9.4 | 3.2.5 build 428 | 2005-01-05 | 5 | 15 | 0 |

Pro 8 matches CInt64_And, CInt64_IsInURange, CInt64_Sub, and CInt64_Inv.
CInt64_And matches all 25 bytes without masking: this resolves the EAX/ECX
register-selection difference observed with Pro 5.3, Pro 6, and Pro 7.

Windows 9.4 produces eight CInt64 bodies that match without masking any bytes:

| Function | Target address | Bytes |
| --- | --- | --- |
| CInt64_And | 0x004d9140 | 25 |
| CInt64_NotEqual | 0x004d9420 | 31 |
| CInt64_Equal | 0x004d9440 | 31 |
| CInt64_GreaterU | 0x004d96c0 | 74 |
| CInt64_LessU | 0x004d97f0 | 74 |
| CInt64_ShrU | 0x004d9920 | 98 |
| CInt64_Shl | 0x004d9a10 | 88 |
| CInt64_Add | 0x004da370 | 86 |

The other seven candidates are CInt64_IsInURange, CInt64_ModU, CInt64_Mod,
CInt64_DivU, CInt64_Div, CInt64_Sub, and CInt64_Inv. Their relocation targets
(including CInt64_Add, CInt64_DivMod, cint64_one, and a switch table) still need
validation. There are 27 baseline CInt64 functions in the probe inventory; these
results do not establish a full-file match. BitVectors.c has only two baseline
mapped functions, neither of which matches these compilers under the tested flags.

This is strong evidence of compatibility between the target's arithmetic code
and the Windows 9.4 x86 compiler. It does not uniquely identify the original
compiler version or establish one toolchain for every source file. Retain the
arithmetic candidates separately until their references are validated. Targets.c now has its own complete verification above.

Tool provenance:

- Pro 7: [original Windows tools disc](https://archive.org/details/CodeWarrior_Pro7).
  Extracted mwcc.exe from the InstallShield group Other Tools - Command Line Tools,
  plus its bundled license and CodeWarrior IDE/lmgr326b.dll.
  Compiler SHA256: `962fa567ca629a28f9952e9c5674e8f25f97352f4e5bec1b4aff2df2ee123e05`.
- Pro 8: [Windows package](https://archive.org/details/cwpro8).
  Extracted only original data1.cab/data1.hdr/data2.cab contents: mwcc.exe,
  lmgr326b.dll, and the bundled license. No installer or patch was run.
  Compiler SHA256: `68108b15594fdeefe83efea3dea090c9f1bc25d1b7570a62a1ca45f54c7c3947`.
- Windows 9.4: [portable package](https://archive.org/details/CodewarriorForWindows).
  The wrapper was not run. Its CodeWarrior94.dat contains a standalone compiler
  PE at offset 204406784, length 2449408; LMGR8C.dll at offset 37879808, length
  851968; and the bundled license at offset 168391676, length 452. These files
  were extracted unchanged to build/compilers/cw94.
  Compiler SHA256: `683338f8c8475015259b94d7ee5408aa5dd4a9d9d7cc615bb250f1fef49f11ed`.
  An independent comparison with the original 9.4 updater was attempted, but
  Internet Archive's extraction endpoint returned HTTP 504. Package labeling,
  compiler banner, date, and exact hashes are recorded rather than assuming
  equivalence to that unavailable installer.

No global installation or persistent environment changes were made. Windows
9.2 remains untested: searches of the available archive collections and the full
Metrowerks FTP archive index found no accessible standalone Windows 9.2 package.
The FTP index contains Windows 9.3 and 9.4 updaters, but no 9.2 installer.

To reproduce using the extracted local tools:

```sh
python tools/probe_gc3_compilers.py --compilers pro7 pro8 cw94 --report build/GC_3_0a5_2/mwcc-newer-probes.json
```

The JSON records compiler banners, tool hashes, exact flags, candidate addresses,
masked operand counts, and whether the unmasked bytes are identical. Compile
logs and objects are under build/GC_3_0a5_2/probes/{pro7,pro8,cw94}.
Package and runtime hashes are in build/GC_3_0a5_2/mwcc-probe-toolchains.json.

### MSVC 8 comparison

A local, compile-only VC80 environment is in `build/compilers/msvc8` (about 15.8 MB
of working files, excluding Git metadata). It was fetched from the portable
[widberg/msvc8.0 repository](https://github.com/widberg/msvc8.0), pinned at
`936f93b9e9e92943ed5c9398d24712a32c2e9fe4`. Only `bin`, `include`, and
`redist/x86/Microsoft.VC80.CRT` are checked out. No global installer, registry
changes, vcvars script, or persistent environment changes were used.

The compiler is Visual C++ 2005 RTM, `14.00.50727.42`. PowerShell's
`Get-AuthenticodeSignature` reports a valid Microsoft signature on `cl.exe`.
The CRT's manifest and DLLs are also copied to `bin/Microsoft.VC80.CRT` for local
runtime resolution. The probe script records and checks SHA-256 hashes of
`cl.exe`, `c1.dll`, and `c2.dll`.

Run `python tools/probe_gc3_msvc8.py`. It compiles the existing `Targets.c`,
`CInt64.c`, and `BitVectors.c`, without changing their source bodies, across:

- `/Od`, `/O1`, `/O2`, `/Ox`;
- `/Oy` and `/Oy-`;
- `/GS` and `/GS-`;
- `/Ob0` and `/Ob2`.

All 96 compilations succeed, with zero unique function/address candidates under
the relocation-masked comparison. The probes use C mode, `/Gy`, and `/Zl`.
Compatibility header copies translate `mac68k` packing to `pack(push,2)` and
`reset` to `pack(pop)`, and reorder calling-convention declarations for VC80.
`inline` is mapped to `__inline`. These copies and all logs/objects stay in
`build/GC_3_0a5_2/probes/msvc8`; the source headers remain unchanged.

For `CInt64_And` at `0x004d9140`, GC 3.0a5.2 emits a 25-byte body that updates
the argument stack slots before loading EAX/EDX. VC80 `/O1`, `/O2`, and `/Ox`
with frame omission emit a different 17-byte body that computes directly in
EAX/EDX. This does not support VC80 for that source under these settings.
It does not exclude MSVC-compiled code elsewhere or with different source/flags.

Results are in `build/GC_3_0a5_2/msvc8-probes.json`. The Codex sandbox causes
VC80 startup to fail with WinError 623 (DLL relocation); the same local compiler
runs successfully outside that sandbox. The probe matrix was run outside it.

## MSVC 6 and 7.1 probes

Workspace-local compiler binaries and headers were fetched with sparse Git
checkouts. No installer, vcvars script, registry change, or global environment
change was used. MSVC 6 additionally needs MSPDB60.DLL copied beside CL.EXE
from its Common/MSDev98/Bin directory.

| Toolchain | Compiler banner | Repository revision | Successful compilations | Unique candidates |
| --- | --- | --- | --- | --- |
| MSVC 6 | 12.00.8804 | itsmattkc/MSVC600, 001c4bafdcf2ef4b474d693acccd35a91e848f40 | 48 | 0 |
| MSVC 7.1 | 13.10.6030 | We-the-People-civ4col-mod/Compiler, ca74c1a3c708dce5da3c358d169794ccce907bb6 | 96 | 0 |

The source files are Targets.c, CInt64.c, and BitVectors.c. Both matrices vary
`/Od`, `/O1`, `/O2`, `/Ox`, frame omission, and `/Ob0` versus `/Ob2`.
MSVC 7.1 also varies `/GS`; MSVC 6 does not support that switch. Unknown-option
warning D9002 is treated as a failed probe. Tool SHA256 hashes are checked by
the script and recorded in each JSON report.

Both older compilers reject the baseline Targets_ReportOperatingSystemError
caller's local report_operating_system_error declaration, which conflicts with
the existing declaration and definition. A temporary source copy excludes only
that caller; all other function bodies are retained verbatim. The excluded
function is not compared. The original source and headers are unchanged.
Header adaptations are the same as for the MSVC 8 probes above.

With `/O2 /Oy /Ob0` (and `/GS-` for 7.1), CInt64_And is 21 bytes for both
compilers. Both compute the result in registers, unlike the target's 25-byte
body that updates argument stack slots. Their instruction ordering also differs
from each other. These tests do not support either compiler for the tested
source bodies/settings. They do not exclude MSVC elsewhere, changed source, or
other flags. MSVC 7.0 (13.00) has not been tested.

To reproduce, using the local toolchains outside the legacy-DLL sandbox:

```sh
python tools/probe_gc3_msvc8.py --toolchain msvc6
python tools/probe_gc3_msvc8.py --toolchain msvc71
```

Results are in `build/GC_3_0a5_2/msvc6-probes.json` and
`build/GC_3_0a5_2/msvc71-probes.json`. Logs, objects, and compatibility copies
are under `build/GC_3_0a5_2/probes/msvc6` and `probes/msvc71`.

## Mapping and source names

`porting-candidates.json` records 30 conservative, unique byte-pattern matches at
Ghidra function entry points. Absolute relocation operands and external relative
branches are masked. These are candidates, not proof of semantic equivalence:
validate function boundaries, all references, and final compiler output before
adding them to `functions.json` or the Matching list. `baseline_source` describes
the 1.2.5 file and does not establish the target's source filename.

Use embedded filenames and their assertion references when available. For example,
3.0a5.2 contains `CException.cpp`, `CFunc.cpp`, `CPrepScanner.cpp`, and `CLFileOps.c`;
do not mechanically carry over the older file extensions. New names include
`CIRStream.c`, `CIRTransform.c`, `IroPointerAnalysis.c`, and `BuildAgentCommon.c`.
The local source-string scan is saved in `build/GC_3_0a5_2/source-strings.json`;
confirm raw string candidates in Ghidra before treating them as filenames.

To regenerate the conservative map, export the MCP `list_functions` text for the
explicit Ghidra program to `build/gc3-ghidra-functions.txt`, then run:

```sh
python -m pip install --target build/python capstone==5.0.6
python tools/match_functions.py
```

The generated map is `build/GC_3_0a5_2/function-candidates.json`. Keep unverified
candidates separate from the build's verified function map. No Ghidra annotations
were changed during that first pass; the later symbol-verified names are recorded above.

## Build

```sh
python configure.py --version GC_3_0a5_2
ninja all_source progress
```

Current result: **217/1,079 mapped functions exact and linked (20,772 bytes)**.
All **209 enabled source units build**: the 207 baseline units, replacing the
old Targets.c bundle with the three symbol-identified files. This includes the
driver, frontend, backend, optimizer, MSL, and runtime. The 862 remaining mapped
functions remain inspectable inside their source-level objdiff units and remain NonMatching.
This is a baseline import, not a completed reconstruction of the compiler.

The build uses CW 9.4 speed/space settings selected from the initial whole-source
sweep for compiler/driver units. ParserErrors.c and Arguments.c retain Pro 5.3;
MSL/runtime retain their baseline Pro 4/5-family settings and headers. Successful
compilation and selected matches do not establish which compiler built every
unit. Targets.c remains complete at 4/4, while CInt64.c has 15 exact functions
among 24 mapped imports. CInt64_Mul is close (99.94326% in objdiff) but is not exact.

Shared OS_ASSERT_AT handles the observed three- versus four-argument assertion
ABIs. The baseline CLIO assertion implementation is excluded for GC 3.0a5.2,
whose helper is still an external binding. CLBrowser_ReleaseBuffer now uses
OS_FreeHandle directly for GC 3.0a5.2, as established by its call to 0x00411d40;
the baseline retains Memory_FreeHandle. All 3,575 GC 1.2.5 functions remain exact.
The repository's all-version verification passes. Its stricter local-literal
resolver exposed a pre-existing GC 1.3 duplicate: CMangler_ConversionFuncName and
CMangler_RTTIObjectName both pointed to 0x004fe050. That function references
`__RTTI__`, so the incorrect conversion-name row was removed. GC 1.3 now has
999 mapped functions, with 645 complete and its existing 67 NonMatching bodies.

### Matching and evidence

`baseline-port-evidence.json` records each fully resolved objdiff-cli result,
full-byte equality, PE HIGHLOW fixup equality, unresolved references, and
inferred-binding observations. Only functions passing all three comparisons
and having no unresolved control-flow extent enter `matching_functions`.
Unresolved imports get partial relocation resolution for inspection and cannot
count as strictly verified functions. Objdiff's raw instruction-match totals can
exceed that count. Whole-unit completion is a separate final check, including data.

### Source-level objdiff units and data

Objdiff now has 209 source units and six unassigned image-section buckets.
Targets.c is one unit containing all four functions, not four separate units.
Every source object has one consolidated `.text` section and sized function
symbols. Compiler data is grouped separately into `.rdata`, `.data`, and `.bss`;
target data retains its original PE section class. BSS has a virtual size and no
file-backed payload. Additional unassigned PE sections such as `.exc` and `.CRT`
remain visible in their own buckets.

The source-level objects are resolved comparison views, rather than executable
objects intended for linking. Their packed offsets are synthetic; the original
compiler outputs remain under `compiled/`. Unmapped emitted functions and data
are visible on the base side and prevent whole-unit completion.

Data attribution uses defined COFF symbols with named bindings, or resolved
references from mapped functions. `build/GC_3_0a5_2/unit-data/<source>.json`
records addresses, section classes, bytes, fixups, and unresolved spans.
Sizes derived from compiled symbol boundaries are provisional until the target
inventory confirms them. Unassigned target data stays in the appropriate
unknown section bucket. Pooled constants can appear in multiple TU views;
global data progress counts physical image ranges only once.

CW 9.4 defaults to read-only strings, but the observed target strings are in
writable `.data`. Its source settings now include `-str noreadonly`. This
preserves all 217 exact function matches and also matches Targets.c's 112 data
bytes. Targets.c is the one inventoried complete TU: 380 code bytes and 112
data bytes. `complete_sources` gates additional whole-unit claims until their
inventories are established and their code/data checks pass.
Whole-unit completion also requires an objdiff-cli comparison with matching
section classes/sizes and 100% section matches, recorded under `unit-diffs/`.

Both objects for a source are explicit Ninja outputs. For example:

```sh
ninja build/GC_3_0a5_2/base/src/driver/ClientGlue.c.obj
build/tools/objdiff-cli.exe diff -p . -u src/GC_3_0a5_2/driver/Targets -o build/Targets.diff.json
```

This fixes objdiff's previous unknown-target error. The old per-function CLI
probe objects under `objdiff-imports` remain internal verification artifacts;
they are not project units.

`functions.json` preserves baseline names/addresses and mapping/boundary evidence.
Most mappings use existing Ghidra labels and require semantic review; others
have unique relocation-masked compiled bodies at Ghidra entries. These mappings
are candidates until comparison succeeds. Source paths inherited from 1.2.5
describe the reconstruction's organization, not independently verified original
GC 3.0a5.2 file membership. Use STABS source records or assertion references
before changing those attributions. Ordinary `t` symbols in the supplied Mac map
also recover names omitted from its STABS FUN records, but do not establish
source-file membership or Windows addresses.

The import corrected two pre-existing Ghidra mislabels using their bodies and
call sites: 0x00426300 is xmalloc, while memcpy is at 0x00404850;
0x00407fd0 is snprintf, while sprintf is at 0x00408000. The xmalloc name is also
present in the supplied Mac symbol map. Corrected bindings eliminate the
conflicting call-target observations found in the initial pass.

To repeat the compiler sweep (logs and objects stay under build):

```sh
python tools/port_gc3_baseline.py
```

To refresh mappings after building, save MCP list_functions output from the
explicit Ghidra program to `build/gc3-ghidra-functions-current.txt`. The existing
`build/GC_3_0a5_2/ghidra-import-boundaries.json` contains direct Ghidra body
exports; other extents use reachable x86 control flow bounded by the next entry.
The mapper requires local Capstone under build/python as described above.

```sh
python tools/map_gc3_baseline.py discover
python tools/map_gc3_baseline.py integrate
python configure.py --version GC_3_0a5_2
ninja all_source progress
```

The integrate step runs objdiff-cli on every fully resolved imported function
and writes reports under `build/GC_3_0a5_2/objdiff-imports`. It preserves the ten
original manually verified mappings and regenerates the bulk imports.
