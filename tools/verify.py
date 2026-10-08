#!/usr/bin/env python3
"""Build and compare every version, then restore the active version and objdiff view."""
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
        subprocess.run([sys.executable, "configure.py", "--version", version], check=True)
        result = subprocess.run(["ninja"], capture_output=True, text=True)
        # (the comparison's summary; the build's last lines when it fails)
        print(Path(f"build/{version}/ok").read_text().rstrip() if result.returncode == 0 else result.stdout[-6000:])
        ok &= result.returncode == 0
finally:
    subprocess.run([sys.executable, 'configure.py', '--version', active_version], check=True)
    restored = subprocess.run(['ninja'], capture_output=True, text=True)
    if restored.returncode:
        print(restored.stdout[-6000:])
    ok &= restored.returncode == 0
    print(f'Restored active build and objdiff view: {active_version}')
sys.exit(0 if ok else 1)
