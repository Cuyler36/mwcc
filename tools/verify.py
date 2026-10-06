#!/usr/bin/env python3
"""python tools/verify.py: build and compare every version; leaves the build configured for the first."""
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))
from configure import VERSIONS

ok = True
for version in [*VERSIONS[1:], VERSIONS[0]]:
    subprocess.run([sys.executable, "configure.py", "--version", version], check=True)
    result = subprocess.run(["ninja"], capture_output=True, text=True)
    # (the comparison's summary; the build's last lines when it fails)
    print(Path(f"build/{version}/ok").read_text().rstrip() if result.returncode == 0 else result.stdout[-6000:])
    ok &= result.returncode == 0
sys.exit(0 if ok else 1)
