#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT


from __future__ import annotations

import argparse
from pathlib import Path
import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("input", help="Schedule script path", type=Path)
    parser.add_argument("-o", "--output", help="Output path. Will print to stdout if omitted", type=Path)

    args = parser.parse_args()

    inputPath: Path = args.input
    outputPath: Path|None = args.output

    if not inputPath.exists():
        eprint(f"Error: Input file '{inputPath}' not found")
        exit(1)

if __name__ == "__main__":
    main()
