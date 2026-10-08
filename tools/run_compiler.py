#!/usr/bin/env python3
"""Run a CodeWarrior compiler with the same environment on Windows and Unix."""
import argparse
import os
from pathlib import Path
import subprocess
import sys


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--dep")
    parser.add_argument("--out", required=True)
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    Path(args.out).parent.mkdir(parents=True, exist_ok=True)
    command = args.command[1:] if args.command[:1] == ["--"] else args.command
    env = dict(os.environ, MWCIncludes="include/libc")
    if os.name == "nt":
        license_file = Path(command[0]).resolve().with_name("license.dat")
        if license_file.exists():
            env["LM_LICENSE_FILE"] = str(license_file)
    result = subprocess.run(command, env=env)
    if result.returncode:
        raise SystemExit(result.returncode)
    if args.dep:
        subprocess.run([sys.executable, "tools/transform_dep.py", args.dep, args.out], check=True)


if __name__ == "__main__":
    main()
