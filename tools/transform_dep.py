#!/usr/bin/env python3
"""python tools/transform_dep.py DEP OUT: MWCC's -MD dependency file (written to the working directory, its paths
Windows paths, native or as wibo maps them) as a ninja depfile for OUT."""
import os
import re
import sys
from pathlib import Path

dep, out = Path(sys.argv[1]), sys.argv[2]
paths = []
# Pro 5 quotes paths containing spaces; Pro 5.3 escapes the spaces with backslashes.
for token in re.findall(r'"[^"]*"|(?:\\[ \t]|[^\s])+', dep.read_text(encoding="latin-1").replace("\\\n", " "))[1:]:
    if token:
        path = token.strip('"').replace("\\ ", " ").replace("\\\t", "\t").replace("\\", "/")
        if os.name != "nt" and re.match(r"[A-Za-z]:/", path):
            path = path[2:]
        paths.append(os.path.relpath(path).replace("\\", "/") if os.path.isabs(path) else path)
Path(out + ".d").write_text(out + ": " + " ".join(p.replace(" ", "\\ ") for p in paths) + "\n")
dep.unlink()
