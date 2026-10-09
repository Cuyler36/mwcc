MWCC GC 3.0a5.2
==============

[![Build Status]][actions]

[Build Status]: https://github.com/Cuyler36/mwcc/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/Cuyler36/mwcc/actions/workflows/build.yml

A matching decompilation of `mwcceppc.exe`, the Windows/x86 CodeWarrior compiler for GameCube.
This fork ports the [rayanht/mwcc](https://github.com/rayanht/mwcc) reconstruction
to GC 3.0a5.2 while retaining the earlier versions.

Current GC 3.0a5.2 status: 263 source files build, 2,336 candidate functions are
mapped, and 1,004 functions pass full-byte and relocation checks. Targets.c,
ResourceStrings.c, ParserErrors.c, CLWriteObjectFile.c, CLLicenses.c,
CLErrors.c, CLFiles.c, CLOverlays.c, CLSegs.c, CLLoadAndCache.c, CLPrefs.c,
CLAccessPaths.c, StringExtras.c, CLProj.c,
and the setjmp runtime unit are
complete reconstructed translation units. The remaining
compiler is a port in progress; mappings alone do not establish a match.

EnodeInfoHandler has all four supported native functions exact under CW94,
including HandleENodeInfo. All 59 bytes of filename, switch-table and BSS
contributions match with fixups. The scope and source-location records preserve
native allocation order and packed layouts; neighboring PCode and optimizer
families remain separate. Original physical membership is still unproven.

CPrepScanner has all 140 supported native functions attempted, with 58 exact
matches. Its eleven decoder tables reproduce 492 bytes and 123 fixups; buffers,
registration nodes, magic and the CRT initializer add 608 verified bytes. The
final source passes 1,672 bounded execution checks; 6,946 preserved baseline
checks remain applicable through identical code and relocations. Compiler probes
and the native C++ startup/member-pointer ABI support CW94. Generated switch
data and other code differences remain nonmatching.

CompilerTools has 57 native utility functions reconstructed, with 39 exact
matches and independently verified data sections. The remaining 18 bodies have
code generation differences and remain under review. Canonical utility names
use the supplied symbols; complete original source membership is still unproven.
Its nonmatching Pascal-string converter passes 2,048 bounded instruction checks
per original and compiled body, covering every length from 0 through 255.

Backend Operands has 36 bounded Windows functions reconstructed and 13 exact
matches. Its private types preserve GC3's native operand layout and calling
conventions. Eleven members still have unresolved switch relocations; those
remain nonmatching, with the other code generation differences recorded per body.

PCodeUtilities has 37 reconstructed native members and 24 exact matches. Whole-TU
objdiff reports 91.89% code similarity; all 444 bytes of rodata and 20 bytes of
data match, including relocations. Operands calls now use the recovered canonical
utility names. Generic PCode emitters remain assigned separately.

Backend PPCError.c has four retained Windows diagnostic entry points exact in
objdiff, including its filename data and PE relocations. Their canonical names
come from the supplied GC3 symbols. The original TU's full membership remains
under review; imported helper ownership is preserved separately.

RegisterInfo has 29 reconstructed native members and 13 exact matches, including
Registers_GetVarInfo and its switch table. Four named data objects match;
eight function switch relocations remain unresolved. GC3 uses a 20-byte variable
record; the imported 44-byte record and object offsets cannot be reused.

Registers has all eleven identified native bodies reconstructed, with four exact
matches. Each body passed 500 bounded instruction comparisons using modeled
helpers. Its seven BSS definitions total 248 exact bytes; target-specific arrays
remain external until their source ownership is established. Five additional Mac
helper names remain unlocated, so original object membership remains unproven.

PeepholeForward has all 11 supported native members attempted, with three
exact matches. Fourteen compiler profiles and twelve source forms were tested;
6,600 bounded instruction comparisons pass using native PCode construction and
editing helpers. Its filename and two switch tables total 42 verified bytes;
a 476-byte mask-analysis table remains unresolved. Two incompatible old
one-argument aliases were removed; the compatible mask helper alias remains.

LiveRegisters has all ten supported backend members attempted, with two exact
matches. Fourteen compiler profiles and source forms were tested; each body
passes 300 bounded native instruction comparisons, including branching and
cyclic control flow. Its filename and 64 bytes of BSS match. The eight remaining
bodies retain reviewed code generation differences.

InlineAsmPPC has all 35 supported main-cluster functions reconstructed, with
twelve exact matches. Three additional prefix candidates were attempted and
preserved separately because their physical source ownership is unproven.
Legacy helpers with changed signatures or layouts remain provisional. Generated
switch data still has unresolved addresses; these bodies remain nonmatching.

IroCounterLoop has all five identified Windows bodies reconstructed, with two
exact matches. All five passed 300 bounded instruction comparisons each, and
460 bytes of data match. The Mac MarkAll helper remains unlocated; the separately
reviewed rotation function retains unproven source ownership.

Alias has all 24 supported main-cluster functions attempted, with 14 exact
matches. Each body passes 250 bounded native instruction comparisons, including
recursive alias operations. Its initialized data and BSS match; one switch table
remains unresolved. An additional exact prefix helper stays separate until its
physical source ownership is established.

Six native bit-vector operations match exactly: copy, copy-and-change detection,
initialize, union, intersection, and empty-intersection testing. Their names use
the supplied Mac symbols. Four other Mac bit-vector names remain unmapped, and
complete original source membership is unproven.

PCode has 26 native bodies reconstructed, including the generic emitters and
graph helpers; 12 match exactly. The native flag setter takes one 64-bit value.
Incorrect imported flag-setter and predecessor-builder mappings were removed;
their old bodies remain provisional. Original state-data ownership is still open.

CError has all 57 identified native bodies reconstructed, with 25 exact matches.
Its diagnostic table, strings, rodata, and BSS match with relocations. The shared
CSV clarifies canonical names, including CError_NoMem and the error-skipping
routines. A whole-image audit also recovered an exact CError_InfoString.
Version-specific naming conflicts remain recorded. The other 32
bodies retain code generation differences after static control-flow review.

CABI has all 56 identified native bodies reconstructed, with 26 exact matches.
The shared CSV recovered names and missing class-layout helpers. Twenty-eight
bodies retain reviewed code differences; two switch tables remain unresolved.
Changed argument counts and record layouts are documented, with incompatible
legacy aliases excluded. Full original data ownership remains incomplete.

CCallGraph has all 15 identified members attempted, including its graph and IR
helpers, with 11 exact matches. Two bodies retain reviewed code differences;
two other bodies and four emitted switch tables remain unresolved. A whole-image
membership audit distinguishes graph consumers in other source families.

CBrowse has all 21 identified native members attempted, with 18 exact matches.
The three remaining bodies have complete native control-flow reviews; data and
BSS match. Native saved browser state is 20 bytes, so untouched callers using
the old 16-byte GList storage still need migration. Separate Mac helper names
without Windows bodies remain documented search limits.

The shared `mwcc.csv` is preserved as normalized name candidates in
[symbol-hints.json](config/GC_3_0a5_2/symbol-hints.json), with its input hash
and reported version 10 provenance. It supplies 1,284 code names and 1,310
other in-image names. Fifty code names lack saved Ghidra entries and need
boundary review. Names require native-code corroboration before promotion;
the hint inventory does not change build mappings or TU ownership.

CPrepLexer has all 121 identified native functions attempted, with 39 exact
matches. Sixty whole-TU compiler profiles favor CW94; seven helpers pass 4,988
bounded native instruction comparisons. Its 43 inferred BSS definitions total
19,403 verified bytes. Remaining switch tables, literal allocations, and original
object membership are documented limits. The incompatible zero-argument
1.2.5 directive mapping is removed; its legacy implementation remains provisional.

ConstantPropagation has all six supported members attempted under CW94 speed.
Twelve compiler profiles, 12 source variants and nine driver forms were tested;
23,560 bounded native comparisons pass, plus 3,690 normal-object checks. A valid
native AND path observes incoming BX, so the candidate preserves it with one
documented entry capture and the driver's native register allocation. Four
profiles fail that requirement and are rejected. No function is exact yet;
50 named data bytes verify. The native 272-byte FP table is identified, while
480 compiled anonymous table bytes remain unclaimed and two projections
remain unresolved. Original physical TU extent remains unproved.

CleanUpIR has all 19 supported members attempted, with four exact matches.
The integer constructor uses the native eight-byte by-value argument. Eleven
final Metrowerks profiles, 42 historical attempts and six MSVC compatibility
profiles were tested; 1,200 bounded native comparisons pass. CW94 noinline/nocse
reaches 61.98% weighted objdiff. Its filename and private state total 29 verified
bytes; four generated tables totaling 540 bytes remain unclaimed, leaving two
function projections unresolved. Original physical TU extent remains unproved.

IRFlowgraph has all six supported members attempted, with four exact matches.
Ten compiler profiles and 21 source forms were tested; 2,304 bounded native
comparisons pass using the original label-list and exception helpers. Its
filename, four BSS words and automatically resolved driver switch total
86 verified bytes. The second 56-byte switch remains unclaimed, leaving one
function projection unresolved. Original physical TU extent remains unproved.

cobraError.c has all four supported diagnostic wrappers matched exactly:
781 code bytes, the 15-entry format table and strings, and its generated
three-entry switch. All 1,521 compiled data bytes and their fixups match,
including alignment; no data or function projection remains unresolved.
CW94 speed matches the native variadic arithmetic, including its short
fatal-error parameter. Original physical TU extent remains unproved.

CIRStreamCallGraph has all 16 supported members attempted, with three exact
matches. Ten compiler profiles and 13 source forms were tested; 6,144 bounded
native comparisons pass, including safe returning assertions and all 28
builtin IDs. Its serialized 52-byte records describe source files. Two strings
and four BSS objects total 49 verified bytes; nine generated tables totaling
168 bytes remain unclaimed, leaving seven function projections unresolved.
Original physical TU extent remains unproved.

The block-reordering family has all 19 supported members attempted under
the provisional filename IroBlockReordering.c. Ten Metrowerks and six MSVC
profiles were tested; 936 bounded native comparisons pass. Twelve literals
total 345 verified bytes, with no unresolved function relocations. No function
is byte-exact yet; selected CW94 speed/nocse reaches 57.88% weighted objdiff.
Original filename and physical TU extent remain unproved.

CopyPropagation has all six descriptor-supported members attempted, with
three exact matches. Fourteen compiler profiles and 46 source forms were
tested; 6,000 bounded native comparisons and 300 ordered callback sequences
pass. Both callback descriptors, strings and private state total 101 verified
data/BSS bytes, with 12 exact descriptor relocations. The filename remains
an architectural inference. Its native entry takes context and mode; the old
one-argument address alias is removed.

IroExprRegeneration has all 26 supported reconstruction members attempted;
its 409-byte driver matches exactly. Ten final-source compiler/optimizer
profiles and three separate source-form experiments were tested. All 1,612
bounded instruction comparisons pass, including successful logical, conditional,
sin/cos and div/mod transformations. Eighteen literals total 435 verified bytes.
Three generated switches remain unresolved; shared optimizer state is external.

CRTTI has all 18 supported cast, typeid and typeinfo members attempted, with
six exact matches. Ten compiler profiles and four source forms were tested;
all 4,608 bounded native comparisons pass. The filename and namespace/type
names total 22 verified bytes; eight generated allocations remain unclaimed.
The zero-argument typeid parser mapping is corrected to 0x5e9500, while its
three-argument semantic helper keeps a separate address name. All retained
CRTTI objects remain unchanged, and all four version checks pass.

AddPropagation has all four descriptor-supported members attempted, with one
exact match. Fourteen compiler profiles and 15 source forms were tested; all
4,000 bounded native comparisons pass. The callback descriptor, strings and
private counter total 69 verified bytes. A 24-byte generated predicate switch
remains unresolved. Its native context argument replaces the older no-argument
entry; shared generic-engine state remains external.

TranslatorUtils has all eight supported IR conversion, type and label-list
helpers attempted, with four exact matches. Seven compiler profiles and nine
source forms were tested; all 2,048 bounded instruction comparisons pass using
native tree traversal and integer conversions. Its filename, two conversion
switches and private BSS total 90 verified bytes. A statement switch remains
unresolved; shared allocator callbacks and CleanUpIR remain separate.

CTemplateFuncInst has all 15 supported template replay members attempted,
with five exact matches. Ten compiler profiles and seven source variants were
tested; all 3,840 bounded native instruction comparisons pass. Its filename,
initializer dispatch and pending-array BSS total 36 verified bytes. Three
generated tables remain unresolved. Native pointer/argument widths are kept
private, including the constructor initializer helper whose older API differs.

CIRStreamType has all 13 supported type and namespace streaming functions
attempted. Its 1,686 bounded native comparisons pass, including a run with
native stream primitives; 39 bytes of literals and private BSS match. No
function is exact yet. Six generated switch tables remain unresolved in
five function projections after compiler and source-form experiments.

CExprConvMatch has all 36 supported native conversion and operator-matching
functions attempted, with two exact matches. Ten compiler profiles and four
source variants were tested; 6,720 bounded native execution comparisons pass.
Its 77 verified data bytes include an automatically located switch table;
31 other generated allocations remain unclaimed. Native ABI and qualifier
widths are private to this TU, and all three retained CExpr objects remain
identical after the GC3-only guards.

IroNonRegLoopAccesses has all six identified native bodies attempted, with two
exact matches. Eleven compiler profiles build; all six bodies pass 1,800 bounded
native instruction comparisons in total. All 194 emitted data and switch-table
bytes match. The native caller diagnostic confirms IRO_OptimizeNonRegAccesses;
shared optimizer state remains external and physical object membership unproven.

CMemberPointer has all 18 identified native bodies reconstructed, with eight
exact matches. Ten compiler profiles build, and eleven reviewed bodies pass
2,200 bounded native instruction comparisons. Its emitted filename data matches.
GC3 uses the native flag-based member-function type constructor; all three
retained-version CDecl objects preserve their code, data, symbols and relocations.
Changed-signature legacy helpers and nearby type-hash helpers remain separate.

SourceText has all three identified line-table functions attempted, with two
exact matches. Ten compiler profiles and 47 additional source formulations leave
one register-allocation difference. All three pass 3,600 bounded native
instruction comparisons in total, and both owned assertion strings match.
Dynamic line tables and nearby C++ runtime helpers remain separate.

CExprTools has all 46 identified expression helpers attempted, with 25 exact
matches. Ten compiler profiles build; all 46 bodies pass 7,360 bounded native
instruction comparisons in total, covering lvalues, temporary nodes, conversions
and tree walkers. Its filename, flag and two generated tables match; twenty
generated tables remain unclaimed. Eight GC3-only legacy guards preserve all
six retained-version CExpr/CExpr2 object outputs.

IroType has all 21 supported native type helpers attempted, with nine exact
matches. Eight compiler profiles build, and all bodies pass 6,300 bounded native
instruction comparisons. Its filename and 64 switch-table bytes match; 368
generated switch bytes remain unclaimed. Two neighboring formatting helpers
were separately attempted and held. The incompatible legacy DumpIR formatter
mapping is removed.

StructMoves has all 17 supported structure-copy helpers attempted, with seven
exact matches. Eleven compiler profiles build, and all bodies pass 5,100 bounded
native instruction comparisons. Both filename allocations and a 44-byte switch
table match; 464 generated switch bytes remain unresolved. Native operands use
28-byte records, and the pair-copy loop takes four arguments. An exact neighboring
register scan stays separate until its source ownership is supported.

CodeMotionPPC has all six supported backend helpers attempted, with three exact
matches. Its audit recovered two omitted callable starts. Four final compiler
profiles and additional source variants were tested; all six bodies pass 9,344
bounded native instruction comparisons. The filename and four-byte BSS cache
match completely. Shared code-motion state and neighboring engines remain separate.

PCodeInfo has all 21 identified native bodies reconstructed, including the
41-terminal instruction formatter, with eleven exact matches. Native callers
confirm that makecopyforload takes an unused context pointer before its three
other arguments; the corrected helper matches all 376 bytes and fixups and
passes 1,000 bounded execution checks. Four switch-table
relocations and one byte of string-allocation padding remain nonmatching.

ELF_Endian.c has all eight known Windows members ported and reviewed, including
the recovered conversion-block routine. Six functions match exactly; two code
nonmatches and one differing switch table remain. Its data and BSS match.

CInt64.c has all 46 identified members attempted and 41 exact matches. Numeric
printing, scanning, and floating conversions now belong to this native TU.
All original 32 exact matches are preserved; Mul also becomes exact. Two
signed-range switch tables remain unresolved. Division passes 800 bounded
instruction checks per body, and multiplication passes 564 per body against
the current compiled object. Five Mac names remain separately unlocated.

Arguments.c has all 27 retained Windows functions reviewed: 24 exact and three
equivalent instruction nonmatches. Its initialized data, switch table, and BSS
pass byte and relocation checks. The initial compiler-profile sweep covered
213 compiled TUs; that coverage does not establish functional equivalence.

The source inventory in `config/GC_3_0a5_2/translation-units.json` combines
Windows assertion callers with explicit source membership from the Mac symbol
map. It currently adds 26 original-only TU views to objdiff. The twenty
assertion-proven ownership conflicts have physical source splits. These views contain real
original functions without placeholder implementations. Unassigned functions
and data remain visible in image-section buckets. See the porting notes for
inventory generation and the per-TU attempt ledger.

Objdiff groups all GC3 sources under `src/GC_3_0a5_2`, including shared source
files; its source metadata retains their actual paths. Distinct C/C++ entries
with the same stem keep their extensions. `python tools/verify.py` tests all
versions with private Ninja files and objdiff report projects, preserving the
active build and objdiff view throughout. Imported helper groups whose original
source is unresolved appear under `provisional`.

Generated C++ initializer pointers retain a `.CRT` data view. An anonymous
startup allocation is attributed only when its mapped initializer entries,
full payload and loader fixups identify one original CRT allocation.

Supported versions:

- `GC_1_2_5`: GameCube 1.2.5
- `GC_1_2_5n`: GameCube 1.2.5n (1.2.5 with Ninji's patch)
- `GC_1_3`: GameCube 1.3
- `GC_3_0a5_2`: GameCube 3.0a5.2 (port in progress; see `config/GC_3_0a5_2/PORTING.md`)

Dependencies
============

- Python 3.11+
- [ninja](https://github.com/ninja-build/ninja)
- [unshield](https://github.com/twogood/unshield), to unpack the CodeWarrior Pro 5.3 updater
- libarchive's `bsdtar`, to unpack the portable CodeWarrior 9.4 archive

macOS: `brew install ninja unshield libarchive` (make libarchive's `bsdtar` available on `PATH`).
Linux: `apt install ninja-build unshield libarchive-tools`.

[wibo](https://github.com/decompals/wibo) runs the compilers on macOS and Linux and is downloaded automatically.
Windows runs the compilers directly; their companion DLL and license data are extracted from the original disc.
On Windows, put `unshield.exe` on `PATH` or at `build/tools/unshield.exe`.
The 3.0a5.2 compiler sources use Windows 9.4; its first download requires
`bsdtar` (libarchive), or Windows' bundled `tar.exe`, to unpack the portable archive.

Building
========

```sh
python configure.py --version GC_3_0a5_2
ninja all_source progress
```

For the baseline, use `python configure.py --version GC_1_2_5` followed by `ninja`.
The other retained versions are `GC_1_2_5n` and `GC_1_3`.
Without `--version`, configure.py selects GC 1.2.5.

The same commands work in PowerShell. To select the 3.0a5.2 target, run
`python configure.py --version GC_3_0a5_2`. Its original executable is checked against its SHA-1 and
extracted for objdiff; only explicitly enabled sources and verified function mappings contribute to its progress. To build all enabled sources and
generate the objdiff progress report, run `ninja all_source progress`.
The GC 3.0a5.2 build and compiler experiments have been verified on Windows;
its macOS/Linux wibo execution path has not yet been validated.

The build downloads what it needs but this repository does not contain:

- the original executables, from the [decomp.dev compiler archive](https://files.decomp.dev), checked against
  their published SHA-1 (`build/compilers/GC`)
- the CodeWarrior Pro 4, 5, 5.3 and 6 Windows/x86 compilers that built them, from the Internet Archive
  (`build/compilers/pro*`)
- the portable CodeWarrior Windows 9.4 compiler used by the GC 3.0a5.2 port
  (`build/compilers/cw94`)
- the MSL C library and runtime sources of CodeWarrior Pro 5, from the same Internet Archive disc (`lib/`), with
  `printf.c` patched to the revision the compiler was linked with

Each function of the compiled sources is compared with the original's; `ninja` fails when a function designated
Matching differs. `python tools/verify.py` builds and checks every version.
Run `python tools/test_compare.py` for the relocation and translation-unit
regression tests. verify.py preserves the active build and objdiff view.
Downloaded executables, compiler libraries, archives, and generated objects stay
in ignored directories and are not distributed with this repository.

Diffing
=======

Open the project in [objdiff](https://github.com/encounter/objdiff) after building.
Each source file is one objdiff unit. Its object has a consolidated `.text`
section with individually sized function symbols, plus separate `.rdata`, `.data`,
and `.bss` sections where present. Unassigned image bytes stay in section buckets.
Ninja can rebuild each source-level base object directly when objdiff requests it.

For GC 3.0a5.2, all baseline source units are enabled, with the old Targets.c
bundle split into Targets.c, ParserErrors.c, and Arguments.c. Imported functions
remain NonMatching until their complete bytes and relocations pass verification.
Use the portable CLI for individual comparisons, for example:

```sh
build/tools/objdiff-cli.exe diff -p . -u src/GC_3_0a5_2/frontend/CInt64 -o build/CInt64.diff.json
```

See [the port notes](config/GC_3_0a5_2/PORTING.md) for compiler choices,
mapping provenance, current coverage, and regeneration commands.

Project structure
=================

- `config/sources.json`: each source's compiler, flags and status (Matching or NonMatching)
- `config/<version>/config.json`: the original executable and its SHA-1; for 1.3, the compiler that replaces Pro 5.3
  and the sources Matching in that version
- A version's optional `sources` list selects files from `config/sources.json`; an empty list enables none.
  Omit it to build all shared sources. `matching` separately lists which sources count as Matching.
  Its optional `source_settings` dictionary adds or overrides compiler settings for that version.
  An optional `matching_functions` list overrides file status with function identifiers
  (`source path without extension/function name`) for strict verification.
  An optional `complete_sources` list restricts whole-unit completion to inventoried files;
  all emitted functions and attributed data must also pass their checks.
- `config/<version>/functions.json`: each function's address, size and source (none yet for a function not
  decompiled)
- `config/<version>/bindings.json`: the addresses of the data and functions the sources reference
- `src/`: the compiler (`driver`, `frontend`, `optimizer`, `backend`) and its statically linked C library and
  runtime (`msl`, `runtime`)
- `include/`: headers; `include/libc` is the C library as the compiler's sources see it
- `lib/` (downloaded): the MSL C library and runtime sources of CodeWarrior Pro 5, built by `src/msl` and
  `src/runtime`

The source is formatted with `clang-format` (`uv run clang-format -i FILE`).

License
=======

The project's files are dedicated to the public domain under CC0 (`LICENSE`); it started from
[inspiredrobot/mwcc](https://github.com/inspiredrobot/mwcc), also CC0.
