#!/usr/bin/env python3
"""Run a CodeWarrior compiler with the same environment on Windows and Unix."""
import argparse
from contextlib import contextmanager
import os
from pathlib import Path
import subprocess
import sys


@contextmanager
def dependency_lock(dep):
    """MWCC writes basename.dep in cwd; serialize only colliding basenames."""
    if not dep:
        yield
        return
    lock_path = Path('build/compiler-locks') / (Path(dep).name + '.lock')
    lock_path.parent.mkdir(parents=True, exist_ok=True)
    with lock_path.open('a+b') as lock:
        if lock.tell() == 0:
            lock.write(b'\0')
            lock.flush()
        lock.seek(0)
        if os.name == 'nt':
            import msvcrt
            msvcrt.locking(lock.fileno(), msvcrt.LK_LOCK, 1)
        else:
            import fcntl
            fcntl.flock(lock, fcntl.LOCK_EX)
        try:
            yield
        finally:
            lock.seek(0)
            if os.name == 'nt':
                msvcrt.locking(lock.fileno(), msvcrt.LK_UNLCK, 1)
            else:
                fcntl.flock(lock, fcntl.LOCK_UN)


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
    with dependency_lock(args.dep):
        result = subprocess.run(command, env=env)
        if result.returncode:
            raise SystemExit(result.returncode)
        if args.dep:
            subprocess.run([sys.executable, "tools/transform_dep.py", args.dep, args.out], check=True)


if __name__ == "__main__":
    main()
