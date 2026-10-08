MWCC GC 3.0a5.2
==============

[![Build Status]][actions]

[Build Status]: https://github.com/Cuyler36/mwcc/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/Cuyler36/mwcc/actions/workflows/build.yml

A matching decompilation of `mwcceppc.exe`, the Windows/x86 CodeWarrior compiler for GameCube.
This fork ports the [rayanht/mwcc](https://github.com/rayanht/mwcc) reconstruction
to GC 3.0a5.2 while retaining the earlier versions.

Current GC 3.0a5.2 status: 219 source files build, 1,236 candidate functions are
mapped, and 462 functions pass full-byte and relocation checks. Targets.c,
ResourceStrings.c, ParserErrors.c, CLWriteObjectFile.c, CLLicenses.c,
CLErrors.c, CLFiles.c, CLOverlays.c, CLSegs.c, CLLoadAndCache.c, CLPrefs.c,
CLAccessPaths.c, StringExtras.c, CLProj.c,
and the setjmp runtime unit are
complete reconstructed translation units. The remaining
compiler is a port in progress; mappings alone do not establish a match.

Backend PPCError.c has four retained Windows diagnostic entry points exact in
objdiff, including its filename data and PE relocations. Their canonical names
come from the supplied GC3 symbols. The original TU's full membership remains
under review; imported helper ownership is preserved separately.

Arguments.c has all 27 retained Windows functions reviewed: 24 exact and three
equivalent instruction nonmatches. Its initialized data, switch table, and BSS
pass byte and relocation checks. The initial compiler-profile sweep covered
213 compiled TUs; that coverage does not establish functional equivalence.

The source inventory in `config/GC_3_0a5_2/translation-units.json` combines
Windows assertion callers with explicit source membership from the Mac symbol
map. It currently adds 48 original-only TU views to objdiff. The twenty
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
regression tests. verify.py leaves GC 1.2.5 selected; reconfigure GC 3.0a5.2 afterward.
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
build/tools/objdiff-cli.exe diff -p . -u src/frontend/CInt64 -o build/CInt64.diff.json
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
