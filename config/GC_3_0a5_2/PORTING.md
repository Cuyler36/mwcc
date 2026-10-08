# GC 3.0a5.2 port

Original: `build/compilers/GC/3.0a5.2/mwcceppc.exe`.
SHA-1: `79683505e7fc6bb63e5c169f21623df272dd2262`.
Ghidra: project `City Folk`, program `/mwcc/GC 3.0/mwcceppc.exe`.
Its executable path identifies the 3.0a5.2 compiler. Use this explicit program path in MCP calls.

## TU inventory and matching order

Frontend and backend matching now takes priority. The first backend pass ports
PPCError's four retained Windows wrappers: PPCError_ErrorTerm at 0x0056ec90,
PPCError_Message at 0x0056ed50, PPCError_Warning at 0x0056ed90, and PPCError_Error
at 0x0056ee40. All 616 code bytes, their PE fixups, and 12 filename-data bytes
match in objdiff-cli. The supplied Mac ordinary symbols recover these names,
while three native assertions independently name PPCError.c at line 52.

GC3 accepts diagnostics 1 through 165, loads resource 10001 at index code+1000,
and passes code+33000 to the shared formatter. This differs from the imported
1.2.5 range and resource offsets. The warning suppression byte, speculative
escape jump buffer, inline-assembly escape, and native variadic argument setup
are preserved. The old imported global/class-update helpers retain provisional
ownership in their separate view. No complete-TU claim is made: this Mac map
has no explicit PPCError.c SO/FUN membership, and separate Windows bodies for
PPCError_GetErrorString and PPCError_VAErrorMessage remain unproved.

`translation-units.json` is the source checklist and per-TU attempt ledger.
Its initial inventory contains 262 units: 209 imported compiled sources and 53
original-only Windows source views. It records 1,984 known Windows functions,
including 905 not yet implemented, and keeps the Mac-only source checklist
separate. The original's remaining code and data stay in unknown section views.
The inventory is incomplete: assertions name callers, not every function in a
file. The twenty initially conflicting filename mappings have since been split.
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

The GC3 objdiff tree uses logical `src/GC_3_0a5_2` paths for both shared and
version-specific sources. Actual source metadata and Ninja output paths are
unchanged. C/C++ entries with a shared stem retain their extensions to avoid
collisions. The version matrix uses private Ninja files and per-version report
projects, preserving the active Ninja file and objdiff view throughout. It
checks progress generation as well as compilation and byte comparisons.
Provisional imported helper groups with unresolved original filenames appear
under `provisional`; `original_source_units` selects the symbol-proven canonical
TU when a baseline helper grouping has the same basename.

MWCC writes basename.dep in the working directory. The compiler runner locks
each dependency basename through compilation and dependency transformation,
preventing collisions between different source paths while allowing other
basenames to compile concurrently. A two-process regression reproduces this
case and checks that each object gets its own source dependencies.

Data attribution also follows independently anchored pointer tables to local
literals. It validates the entire table's bytes and exact loader-fixup set,
then every inferred local allocation's full payload, section category, bounds
and absence of relocations. Mixed function/global/external pointers must agree
with independently established singleton destinations, including COFF addends
and mapped image bounds; their addresses are never inferred from the table.
Ambiguous identities and interior local-literal pointers are rejected.
This recovers CLIO's table-only severity strings without generated-symbol
bindings. The regression suite has 28 tests, including negative proof cases.

First matching priorities are the runtime setjmp unit, ResourceStrings.c,
ParserErrors.c, CLIncludeFileCache.c, and CLBrowser.c. Then handle the remaining
driver units, frontend, optimizer, backend, MSL, and runtime sources. New
original-only units remain explicit work items, rather than empty C stubs.

The current inventory has 266 source views: 218 compiled files and 48
original-only units. All twenty direct assertion ownership conflicts are now
split physically. CFunc.cpp and CException.cpp retain provisional C language
mode while imported pointer conversions are ported. CMiddleLayer.c,
RegisterInfo.c, and StackFrame.c contain explicitly NonMatching imports with
materially changed GC3 layouts/control flow. Their ledger entries do not claim
equivalence. Older version bodies remain behind version guards.

CLIncludeFileCache.c has all eight symbol-identified functions reviewed: five
exact, three equivalent nonmatches after compiler/code-shape experiments.
Its 20 initialized bytes and 12 BSS bytes match. CLBrowser.c has its nine
functions reviewed: eight exact, one equivalent serializer nonmatch. Its 131
literal payload bytes match; five alignment bytes in the 136-byte original
span remain unassigned. WriteBrowseData belongs to CLWriteObjectFile.c, proven
by STABS parameters and behavior, and joins WriteObjectFile there. Both writer
functions now match with the GC3 record ABI. Static cache bindings are scoped to the
source file to avoid contaminating unrelated file-local names.

## CLPlugins.c: reviewed native plugin unit

All 45 recovered Windows bodies are ported and statically reviewed; 25 pass
strict byte/fixup checks. The native Plugin is 544 bytes with a 516-byte spec
at 0x1c, and base callbacks are 40 bytes with a tool-version callback at 0x24.
GetToolVersionInfo reads native Windows version resources. The no-argument
Plugin_GetToolVersionInfo is distinct from the Windows Plugin-argument accessor,
which retains the address name fn_00415170.

The 9,201 original code bytes compare at 90.92271%; all 2,436 initialized data
bytes and 100 BSS bytes match. Twenty instruction nonmatches have per-function
branch/write/error reviews in the ledger. Four Mac members remain unmapped;
unknown Windows helper names and the static fallback record's unreferenced tail
are explicit limits. Exact completion is false. Native layouts stay private
to the port until the remaining imported callers are reconstructed.

## OSLib/MacSpecs.c: recovered canonical spec-conversion unit

Thirteen canonical Windows functions are reconstructed; eleven pass strict
byte/fixup checks. ResolveVolDir and OS_GetRsrcOSSpec remain reviewed equivalent
code-generation nonmatches. All 2,145 original code bytes compare at 96.24106%,
all 132 initialized data bytes and 1,616 BSS bytes match, and every function's
fixups resolve and agree. OS_VolDir_To_OSNameSpec remains unmapped. A possible
unused stpath allocation has no original reference and is not claimed.

Three baseline helpers (short_predecessor, MacSpecs_LoadMacResource and the
DBCS-byte helper) are preserved separately until their actual Windows source
ownership is established. They are excluded from canonical MacSpecs membership;
the imported view is explicitly provisional. Version guards include version.h
directly, preserving the older builds and excluding moved definitions for GC3.

## MacFileTypes.c: reviewed native type-mapping unit

Six retained Windows functions are reconstructed with canonical Mac names.
Five pass strict byte/fixup checks; OS_GetMacFileTypeMagic remains a reviewed
equivalent loop/register nonmatch after seven source experiments. The original
865 code bytes compare at 95.39854%; all 36 initialized data bytes and eight
BSS bytes match. Native specs are 516 bytes, and OS_SetMacFileCreatorAndType
uses the observed three-argument Windows ABI while ignoring creator.
GetMacFileType preserves the Windows open-error/hook/resource-fork fallbacks.
OS_UseFileTypeMappings has no recovered standalone Windows implementation;
the saved whole-text relocation audit documents the fmList/defaultList
reference limits rather than adding a stub.

## OSLib/FileHandles.c: recovered file-handle unit

Five native Windows bodies are recovered from the seven-member Mac source:
OS_LoadFileHandle, OS_WriteFileHandle, OS_NewFileHandle, OS_LockFileHandle and
OS_FreeFileHandle. Four pass strict byte/fixup checks; the loader differs only
in the temporary register holding the size-output address. Four compiler
profiles and six declaration-order probes did not improve that match.
The native record is 528 bytes: 516-byte spec, eight-byte handle and three
state flags at 0x20c..0x20e. All 691 original code bytes compare at 99.95604%,
all fixups match, and there is no owned data. OS_UnlockFileHandle and
OS_GetFileHandleSpec remain unmapped; no placeholder implementations are added.

## CLTarg.c: native target-list port

The four canonical Mac members Target_New, Target_Free, Targets_Term and
Target_Add all match exactly. Two additional Windows cache helpers remain
address-named: initialization matches; cleanup has a reviewed EBX/EBP register
swap. The native target is 0x1440 bytes, with 997 cache buckets at 0x4a8 and
next at 0x143c; TargetInfo is 820 bytes. Initialization invokes all component
initializers unconditionally, and termination also frees TargetInfo. All six
bodies total 551 original code bytes at 99.80604%; all 20 initialized data
bytes match. Helper original names and exact source-membership proof remain
limited, so the TU is recorded as a reviewed attempt rather than complete.

## CLToolExec.c: reviewed linker-driver equivalent nonmatch

All seven Mac-named Windows functions are reconstructed. Six pass strict byte
and loader-fixup checks. ExecuteLinker remains nonmatching after 19 recorded
source experiments; its original branch, memory and call behavior was reviewed
through executable lookup, nmw-prefixed/fallback tool names, explicit overrides,
argv/env ownership, dry-run printing, distinct execution/exit-code reports and
cleanup. Native file specs are 516 bytes. The command trailer is two newlines.
The complete original code inventory totals 2,714 bytes at 80.53141%; all 184
initialized data bytes match. Static review found no unported behavior, but
execution testing was not performed and strict completion remains false.

## CLIO.c and TextUtils.c: reviewed native diagnostic and string ports

CLIO.c now has all 42 emitted Windows cluster bodies mapped and reviewed,
including console setup/cancellation, handle/file output, text wrapping,
formatter variants and diagnostic dispatch. Twenty-nine functions pass strict
byte and loader-fixup checks. The private diagnostic source layout has native
516-byte specs, sourceLine at 0x408, line at 0x40c and column at 0x410.
The IDE callback takes eleven arguments; dispatch retains original logging,
severity limits, style-five formatting, CR/LF normalization and flush behavior.
Its 8,283 original code bytes compare at 80.67977%; all 800 initialized data
bytes and 1,300 BSS bytes match, including table-only severity strings.
CLPrintDispatch's empty-string code operand remains ambiguous, and four Mac
members lack Windows mappings. Completion is deliberately false.

TextUtils.c separately owns c2pstr and p2cstr, both strict exact, and the
reviewed equivalent GetIndString instruction nonmatch. The three mapped bodies
total 517 original bytes at 99.45856%; all 44 data bytes match. The additional
getindstring wrapper is emitted but has no established Windows body, and seven
other Mac members remain unresolved. This TU also remains incomplete. Original
severity names distinguish CLPrint and CLPrintErr; CLPrintWarning has no
retained mapping in the reviewed cluster.

## CLProj.c and OSLib/Generic.c: restored original ownership

CLProj.c contains only Proj_Initialize and Proj_Terminate, as established by
the explicit Mac unit and adjacent Windows bodies. Both match exactly; its
72 code bytes and 40 initialized data bytes pass objdiff-cli. Initialization
uses the native 516-byte Project.mcp file spec.

Nine imported CLProj path helpers belong to OSLib/Generic.c. They are now
preserved there alongside OS_GetDirName, OS_FindProgram, OS_CopyHandle and
OS_AppendHandle, all 13 strict exact. The handle helpers were previously
grouped into CLFileOps.cpp; their old bodies are excluded for GC3. The final
Windows path-splitting helper retains an unknown-name address alias and a
reviewed register-allocation nonmatch. Generic.c has 3,623 code bytes at
99.92298%, 44 initialized data bytes and 1,299 BSS bytes at 100%. Its Mac
OS_CompactPaths has no recovered standalone Windows body, so membership
remains incomplete and no replacement stub is invented.

## StringExtras.c: complete Windows unit

The four explicit Mac members are strcatn, strcpyn, ustrcmp and ustrncmp.
All four retained Windows bodies match exactly, with native stdcall argument
sizes and no allocated data. The 316-byte text section passes objdiff-cli.
The old definitions in CLProj.c, CLIO.c and ClientGlue.c are excluded for GC3;
canonical mappings preserve their baseline aliases. This includes the former
fn_004050e0, whose identity is ustrncmp rather than a ClientGlue helper.

## CLAccessPaths.c: complete Windows unit

All 22 retained Windows functions match, including 18 canonical Mac members
and four Windows helpers whose original names remain unknown. The port uses
native 516-byte specs and the recovered 16-byte path record. The four-argument
recursive-copy functions preserve the plugin parameter. The complete unit
passes objdiff-cli for 2,323 code bytes and 88 initialized data bytes, including
strict loader-fixup checks. Mac framework helpers outside this Windows cluster
remain explicit inventory differences, without a whole-binary absence claim.

## CLPrefs.c: complete Windows unit

All eight retained Windows functions match, including the seven named Mac
preference functions and the additional Windows callback helper. The native
16-byte panel contains its name, an eight-byte memory buffer, and its next
pointer. The constructor previously imported into CLIO.c is PrefPanel_New;
its baseline body is excluded for GC3 and its canonical ownership is recorded.
The complete unit passes objdiff-cli for 607 code bytes, 64 initialized data
bytes, and four BSS bytes, with strict original loader-fixup checks.

## CLLoadAndCache.c: complete Windows unit

All three formerly unmapped functions match: FixTextHandle, LoadAndCacheFile,
and CopyFileText. Full-TU objdiff verifies 518 code bytes and 20 initialized
bytes. The Windows loader takes four arguments, including the plugin, uses
native eight-byte MemBuffer records, checks plugin flags before line-ending
conversion, and exits on allocation failure. Original error-path behavior,
including the get-size failure's open descriptor, is preserved. The old
CLPrefs line-ending helper belongs to this TU as FixTextHandle.

## CLDependencies.c: reviewed equivalent nonmatch

All twenty retained Windows functions are inventoried and reviewed; nineteen
match exactly. Incls_FindFileInPaths remains a 463-byte equivalent nonmatch
after compiler/source-shape attempts, chiefly register and stack allocation.
Its full-TU code similarity is 98.60921%; all 200 initialized bytes, 16 read-only
switch-table bytes, and eight BSS bytes match with exact fixups. GC3 uses native
516-byte specs, new include-search behavior, saved currentsrcfss state, and a
fatal allocation path during dependency output. The Mac QuickFindFileInIncls
body is replaced by a six-argument Windows search helper whose original name
remains unresolved. The source stays NonMatching as a complete TU.

## CLSegs.c: complete Windows unit

All eight Windows functions match 642 code bytes and 76 initialized bytes.
The canonical Segment_/Segments_ names and static GrowSegments come from the
Mac map. Windows has no retained InsertSegment/DeleteSegment bodies in the
reviewed cluster. Segment_New and Segment_Free were missing from the initial
inventory. The imported free_if_not_null match at 0x00421770 was a false
identity: it calls CRT free, while Segment_Free at 0x0043c500 calls xfree.
The displaced 16-byte body remains in the original image with unknown name
and ownership; it is not treated as removed code. Full-TU objdiff and strict
relocation checks pass.

## CLOverlays.c: complete Windows unit

All seventeen Windows functions match 1,772 code bytes and 144 initialized
bytes under CW94 speed/intrinsic settings. Original Overlays_, OvlGroup_, and
Overlay_ names and record fields are restored. The assertion-free Overlay_New
was missing from the initial inventory; the Mac-only Overlays_AddFileToOverlay
has no standalone Windows body in the reviewed cluster. Negative-index and
allocation-failure behavior is preserved. The baseline's unrelated timestamp
conversion helpers belong to CLDropinCallbacks_V10.cpp and are excluded from
this physical TU. Full-TU objdiff and strict fixup checks pass.

## CLFiles.c: complete Windows unit

All fifteen Windows functions match 1,098 code bytes and 104 initialized
bytes. Fourteen use their original File_, Files_, VFile_, and VFiles_ names.
The added file-map helper asserts CLFiles.c and is called by Files_GetFile;
its unavailable static name remains an address alias. GC3 expands File to
0x8b4 bytes, embeds native handles/specs, and lazily rebuilds an indexed file
map. Insertions renumber following files and invalidate that map. Full-TU
objdiff and strict relocation checks pass with CW94 speed/intrinsic settings.

## StringUtils.c: reviewed mapped functions, incomplete membership

Seven of eight Windows functions match exactly. HPrintF is equivalent after
review of its varargs, append/error, conditional-free, and return paths; its
remaining register and zero-test differences score 95.67308%. Full-TU code
similarity is 99.17875%. All 48 initialized bytes and the 256-byte original
pfbuf match. The Mac map additionally names _pstrcat, _pstrcharcat, pstrncpy,
and pstrncat. Their Windows existence remains unresolved beyond this contiguous
eight-function cluster, so the unit remains incomplete.

## CLErrors.c: complete Windows unit

All nine functions use their original CLGetErrorString, CLMessageReporter,
CLReport*, CLInternalError, and CLFatalError names. CW94 speed/intrinsic
optimization reproduces 895 code bytes, 56 initialized bytes, and 512 BSS
bytes. Original stmsg/stbuf names, signed-short resource IDs, varargs handling,
new diagnostic IDs, optional log output, and fatal cleanup are ported. The
fatal function ends after its noreturn exit call; nine following NOP alignment
bytes belong to the unassigned image range rather than the function.

## CLLicenses.c: complete Windows unit

All ten Windows functions match 1,544 code bytes, 204 initialized bytes, and
268 BSS bytes with CW94 speed/intrinsic optimization. The Mac unit's six tiny
License_* stubs do not describe this Windows licensing implementation. Four
previously unmapped Windows functions are included. The port preserves the
larger state, path-search fallbacks, checkout checks, and cleanup behavior.

COFF common symbols are allocated BSS contributions even though their section
index is zero. Comparison now accounts for their full size and rejects unknown
addresses, non-BSS locations, nonzero data, fixups, bounds violations, and
overlapping allocations. Twenty-one comparison regressions and the complete
version build matrix pass.

## MemUtils.c: exact mapped code, provisional wrapper ownership

The five symbol-named allocation functions and two adjacent Windows allocation
wrappers match all 406 code bytes and 116 initialized data bytes. Windows uses
the stdcall GlobalAlloc/GlobalReAlloc/GlobalFree path. The two additional
wrappers retain address-based names; their TU attribution remains provisional,
so the source is not marked complete. The imported MemUtils_CallPluginEntry
belongs to CLPluginRequests.cpp and is restored there as CallPlugin, using its
STABS identity and matching context call. Its Windows body remains exact.

## CLWriteObjectFile.c: complete Windows unit

WriteObjectFile and WriteBrowseData match all 496 code bytes and 56 initialized
data bytes under CW94 speed/intrinsic optimization. The Windows File embeds
516-byte native specs; its object and browse handles and compiler pointer use
the recovered GC3 offsets. Original STABS names supply the source, parameters,
local variables, and record fields. Full-TU objdiff and strict loader-fixup
checks pass, with no additional emitted functions or BSS contributions.

## Arguments.c: reviewed equivalent nonmatches

All 27 retained Windows functions are mapped and reviewed; 24 match exactly
with CW94 space/intrinsic optimization. Arg_AddToken, Arg_Parse, and
Arg_GetTokenName remain instruction nonmatches after compiler and source-shape
experiments. The ledger records their branch, memory, error and input behavior
reviews. The Windows cluster adds Arg_InsertArg and Arg_FreeToolArgs; the Mac
Arg_Stop has no retained body between Arg_Reset and Arg_PeekToken. Arg_Terminate
is one 72-byte function despite a false Ghidra entry in its loop.

The full-TU CLI reports 98.64162% code similarity over 3,602 original bytes.
All 384 initialized bytes, the 24-byte read-only switch table, and 572 BSS bytes
match, including loader fixups. Private bindings remain source scoped. The
three code nonmatches prevent marking this TU exact.

## CInt64: partial arithmetic unit

The CInt64 attempt now matches 24 of 26 mapped Windows functions. Equivalent
comparison control flow, helper placement, and local declaration order recover
the signed comparisons and arithmetic right shift. Mul and MulU remain
nonmatches after compiler/code-shape experiments; instruction/dataflow review
and 564 bounded cases per original/compiled body agree on modulo-2^64 products.
This is not exhaustive proof. Four constants contribute 32 verified data bytes;
the unreferenced zero constant was removed because its Windows address is
unproven. The Mac ordinary-symbol list has 51 CInt64 names, with 25 still lacking
Windows mappings. The TU is explicitly incomplete despite the 24 exact bodies.

## ParserErrors.c: complete Windows unit

All 11 retained Windows functions match under CW94 with space and intrinsic
optimization: 654 code bytes, 24 literal bytes, and 1024 BSS bytes. The original
static `errorbuf` belongs to this TU. Resource IDs are signed shorts; resource
lookup calls the stdcall Pascal lookup/conversion functions directly. Correct
varargs calculations reproduce the report wrappers. The Mac-only CLPReport,
CLPReport_V, CLPAlert, and CLPProgress are absent from the reviewed Windows
range. The full-TU CLI diff and strict relocation checks both pass.

## ResourceStrings.c: complete Windows unit

ResourceStrings.c also passes full-TU objdiff: two functions, 405 code bytes,
128 initialized literal bytes, and 448 BSS bytes. Its GC3 implementation uses
bounded `snprintf` calls and original `Res_*`, `rlist`, and `err` names. Local
BSS references are derived from validated original operands rather than global
compiler-generated symbol bindings. The Mac map's Res_Initialize/Res_Cleanup
have no identified retained Windows bodies; adjacent code and all direct
references to this static storage were reviewed. This platform difference is
recorded in the attempt ledger.

## setjmp: complete runtime unit

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

Initial baseline-import result: **217/1,079 mapped functions exact and linked (20,772 bytes)**.
At that stage, all **209 enabled source units built**: the 207 baseline units, replacing the
old Targets.c bundle with the three symbol-identified files. This includes the
driver, frontend, backend, optimizer, MSL, and runtime. The 862 remaining mapped
functions remain inspectable inside their source-level objdiff units and remain NonMatching.
This is a baseline import, not a completed reconstruction of the compiler.

The initial build used CW 9.4 speed/space settings from the whole-source
sweep for compiler/driver units. ParserErrors.c and Arguments.c initially retained Pro 5.3;
MSL/runtime retain their baseline Pro 4/5-family settings and headers. Successful
compilation and selected matches do not establish which compiler built every
unit. Current per-TU results and revised compiler settings are recorded above
and in the attempt ledger; these import figures are historical.

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

Objdiff has 261 source views and six unassigned image-section buckets.
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

Data attribution uses allocated COFF symbols with named bindings, or resolved
references from mapped functions. `build/GC_3_0a5_2/unit-data/<source>.json`
records addresses, section classes, bytes, fixups, and unresolved spans.
Sizes derived from compiled symbol boundaries are provisional until the target
inventory confirms them. Unassigned target data stays in the appropriate
unknown section bucket. Pooled constants can appear in multiple TU views;
global data progress counts physical image ranges only once.

CW 9.4 defaults to read-only strings, but the observed target strings are in
writable `.data`. Its source settings now include `-str noreadonly`. This
preserved the initial 217 exact function matches and matched Targets.c's 112 data
bytes. The completed units are listed in the README and per-TU reviews above.
`complete_sources` gates additional whole-unit claims until their
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

To repeat the current bounded compiler-profile sweep (logs and objects stay under build):

```sh
python tools/sweep_gc3_units.py
python tools/sweep_gc3_units.py --source src/GC_3_0a5_2/driver/Arguments.c
```

The sweep records each profile's source hash, bindings, function mappings,
compiler flags, strict byte/fixup results, and mapped-code objdiff projection.
It tests configured settings and CW94 speed/space with intrinsic variations.
Unmapped units remain discovery tasks, and no compiler-profile result alone
establishes semantic equivalence, original membership, or complete TU data.
Partial refreshes also cover new source paths after physical TU replacements.

To reproduce the initial compiler-selection import:

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
