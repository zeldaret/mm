#!/usr/bin/env python3

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


def firstDiffMain():
    parser = argparse.ArgumentParser(description="Find the first difference(s) between the built ROM and the base ROM.")

    parser.add_argument("-c", "--count", type=int, default=5, help="find up to this many instruction difference(s)")
    parser.add_argument("-v", "--version", help="Which version should be processed", default="us.rev1")

    args = parser.parse_args()

    cwd = Path(".")
    buildFolder = Path("build")

    BUILTROM = cwd / f"mm.{args.version}.rom_uncompressed.z64"
    BUILTMAP = buildFolder / f"mm.map"

    EXPECTEDROM = cwd / "baserom_uncompressed.z64"
    EXPECTEDMAP = "expected" / BUILTMAP

    exit(mapfile_parser.frontends.first_diff.doFirstDiff(BUILTMAP, EXPECTEDMAP, BUILTROM, EXPECTEDROM, args.count, mismatchSize=True))

if __name__ == "__main__":
    firstDiffMain()
