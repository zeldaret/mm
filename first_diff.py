#!/usr/bin/env python3

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path
import rabbitizer


def decodeInstruction(bytesDiff: bytes, mapFile: mapfile_parser.MapFile) -> str:
    word = (bytesDiff[0] << 24) | (bytesDiff[1] << 16) | (bytesDiff[2] << 8) | (bytesDiff[3] << 0)
    instr = rabbitizer.Instruction(word)
    immOverride = None

    if instr.isJumpWithAddress():
        # Instruction is a function call (jal)

        # Get the embedded address of the function call
        symAddress = instr.getInstrIndexAsVram()

        # Search for the address in the mapfile
        symInfo = mapFile.findSymbolByVramOrVrom(symAddress)
        if symInfo is not None:
            # Use the symbol from the mapfile instead of a raw value
            immOverride = symInfo.symbol.name

    return instr.disassemble(immOverride=immOverride, extraLJust=-20)

def firstDiffMain():
    parser = argparse.ArgumentParser(description="Find the first difference(s) between the built ROM and the base ROM.")

    parser.add_argument("-c", "--count", type=int, default=5, help="find up to this many instruction difference(s)")
    parser.add_argument("-v", "--version", help="Which version should be processed", default="us.rev1")
    parser.add_argument("-a", "--add-colons", action='store_true', help="Add colon between bytes" )

    args = parser.parse_args()

    buildFolder = Path("build")

    BUILTROM = Path(f"mm.{args.version}.rom_uncompressed.z64")
    BUILTMAP = buildFolder / f"mm.map"

    EXPECTEDROM = Path("baserom_uncompressed.z64")
    EXPECTEDMAP = "expected" / BUILTMAP

    exit(mapfile_parser.frontends.first_diff.doFirstDiff(BUILTMAP, EXPECTEDMAP, BUILTROM, EXPECTEDROM, args.count, mismatchSize=True, addColons=args.add_colons, bytesConverterCallback=decodeInstruction))

if __name__ == "__main__":
    firstDiffMain()
