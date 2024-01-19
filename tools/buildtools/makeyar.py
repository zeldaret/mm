#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
from pathlib import Path
import struct
import subprocess
import crunch64

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

def writeWordAsBytes(buff: bytearray, offset: int, word: int):
    struct.pack_into(f">I", buff, offset, word)



def readFileAsBytearray(filepath: Path) -> bytearray:
    with filepath.open(mode="rb") as f:
        return bytearray(f.read())



@dataclasses.dataclass
class Symbol:
    name: str
    offset: int
    size: int

def getDataFromElf(elfPath: Path) -> tuple[bytearray, list[Symbol], int]:
    uncompressedData = bytearray()
    symbolList: list[Symbol] = []
    dataOffset = -1

    with elfPath.open("rb") as elfFile:
        elf = ELFFile(elfFile)
        for section in elf.iter_sections():
            if section.name == ".data":
                assert len(uncompressedData) == 0
                uncompressedData.extend(section.data())
                # print(section.header)
                assert len(uncompressedData) == section["sh_size"]
                dataOffset = section["sh_offset"]
                # exit()
            elif section.name == ".symtab":
                assert isinstance(section, SymbolTableSection)
                for sym in section.iter_symbols():
                    if sym["st_shndx"] == "SHN_UNDEF":
                        continue
                    if sym["st_info"]["type"] != "STT_OBJECT":
                        continue
                    symbolList.append(Symbol(sym.name, sym["st_value"], sym["st_size"]))
    return uncompressedData, symbolList, dataOffset


def align_16(val: int) -> int:
    return (val + 0xF) & ~0xF

def createArchive(uncompressedData: bytearray, symbolList: list[Symbol]) -> bytearray:
    archive = bytearray()

    firstEntryOffset = (len(symbolList) + 1) * 4

    # Fill with zeroes until the compressed data start
    archive.extend([0]*firstEntryOffset)

    writeWordAsBytes(archive, 0, firstEntryOffset)

    offset = firstEntryOffset

    i = 0
    for sym in symbolList:
        real_uncompressed_size = sym.size
        aligned_uncompressed_size = align_16(real_uncompressed_size)

        input_buf = uncompressedData[sym.offset:sym.offset + real_uncompressed_size]
        # Make sure to pad each entry to a 0x10 boundary
        input_buf.extend([0x00] * (aligned_uncompressed_size - real_uncompressed_size))

        Path(f"{offset:06X}_uncompressed").write_bytes(input_buf)

        compressed = bytearray(crunch64.yaz0.compress(input_buf))
        compressed_size = len(compressed)

        Path(f"{offset:06X}").write_bytes(compressed)

        # Pad to 0x10
        compressed.extend([0xFF] * (align_16(compressed_size) - compressed_size))

        archive.extend(compressed)

        if i > 0:
            writeWordAsBytes(archive, i * 4, offset - firstEntryOffset)

        i += 1
        offset += len(compressed)

    writeWordAsBytes(archive, i * 4, offset - firstEntryOffset)

    while len(archive) % 0x10 != 0:
        archive.extend([0])

    return archive


def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("in_file")
    parser.add_argument("out_bin")
    parser.add_argument("out_sym")

    args = parser.parse_args()

    inPath = Path(args.in_file)
    outBinPath = Path(args.out_bin)
    outSymPath = Path(args.out_sym)

    # Delete output files if they already exist
    outBinPath.unlink(missing_ok=True)
    outSymPath.unlink(missing_ok=True)

    elfBytes = readFileAsBytearray(inPath)

    uncompressedData, symbolList, dataOffset = getDataFromElf(inPath)
    assert len(uncompressedData) > 0
    assert len(symbolList) > 0
    assert dataOffset > 0

    # This should always be sorted in ascending order, but just to be sure
    # symbolList.sort(key=lambda x: x.offset)

    archive = createArchive(uncompressedData, symbolList)

    # Write the compressed archive file as a raw binary
    outBinPath.write_bytes(archive)

    # zero out data
    for i in range(dataOffset, dataOffset+len(uncompressedData)):
        elfBytes[i] = 0

    outSymPath.write_bytes(elfBytes)


if __name__ == "__main__":
    main()
