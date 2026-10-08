#!/usr/bin/env python3
"""Build and compare every version without replacing the active build or objdiff view."""
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))
from configure import VERSIONS

configured = Path('build.ninja')
active_match = re.search(r'^version = (\S+)$', configured.read_text(), re.MULTILINE) if configured.exists() else None
active_version = active_match.group(1) if active_match else VERSIONS[0]
if active_version not in VERSIONS:
    raise ValueError(f'Unknown active version: {active_version}')
ok = True
try:
    for version in [*VERSIONS[1:], VERSIONS[0]]:
        build_file = f'build/verify_{version}.ninja'
        subprocess.run([sys.executable, "configure.py", "--version", version,
                        '--build-file', build_file, '--no-active-objdiff'], check=True)
        result = subprocess.run(["ninja", '-f', build_file, 'progress'], capture_output=True, text=True)
        # (the comparison's summary; the build's last lines when it fails)
        print(Path(f"build/{version}/ok").read_text().rstrip() if result.returncode == 0 else result.stdout[-6000:])
        ok &= result.returncode == 0
finally:
    # The active Ninja file and objdiff project stay in place throughout.
    # Refresh their outputs if shared inputs changed during verification.
    restored = subprocess.run(['ninja', 'progress'], capture_output=True, text=True)
    if restored.returncode:
        print(restored.stdout[-6000:])
    ok &= restored.returncode == 0
    print(f'Preserved active build and objdiff view: {active_version}')
sys.exit(0 if ok else 1)
