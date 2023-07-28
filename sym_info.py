#!/usr/bin/env python3

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


def symInfoMain():
    parser = argparse.ArgumentParser(description="Display various information about a symbol or address.")
    parser.add_argument("symname", help="symbol name or VROM/VRAM address to lookup")
    parser.add_argument("-e", "--expected", dest="use_expected", action="store_true", help="use the map file in expected/build/ instead of build/")

    args = parser.parse_args()

    BUILTMAP = Path(f"build") / f"mm.map"

    mapPath = BUILTMAP
    if args.use_expected:
        mapPath = "expected" / BUILTMAP

    mapfile_parser.frontends.sym_info.doSymInfo(mapPath, args.symname)

if __name__ == "__main__":
    symInfoMain()
