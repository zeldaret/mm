#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
import libyaz0
from pathlib import Path
import struct


@dataclasses.dataclass
class ArchiveMeta:
    start: int
    end: int


def readFileAsBytearray(filepath: Path) -> bytearray:
    with filepath.open(mode="rb") as f:
        return bytearray(f.read())


def readBytesAsWord(array_of_bytes: bytearray, offset: int) -> int:
    return struct.unpack_from(f">I", array_of_bytes, offset)[0]


def getOffsetsList(archiveBytes: bytearray) -> list[ArchiveMeta]:
    archivesOffsets: list[ArchiveMeta] = []

    firstEntryOffset = readBytesAsWord(archiveBytes, 0)
    firstEntrySize = readBytesAsWord(archiveBytes, 4)

    archivesOffsets.append(ArchiveMeta(firstEntryOffset, firstEntryOffset + firstEntrySize))

    offset = 4
    while offset < firstEntryOffset - 4:
        entry = readBytesAsWord(archiveBytes, offset)
        nextEntry = readBytesAsWord(archiveBytes, offset + 4)
        # print(f"0x{entry:04X}")
        entryStart = entry + firstEntryOffset
        entryEnd = nextEntry + firstEntryOffset
        archivesOffsets.append(ArchiveMeta(entryStart, entryEnd))

        offset += 4

    return archivesOffsets


def extractArchive(archivePath: Path, outPath: Path):
    archiveBytes = readFileAsBytearray(archivePath)

    archivesOffsets = getOffsetsList(archiveBytes)

    with outPath.open("wb") as out:
        for meta in archivesOffsets:
            decompressedBytes = libyaz0.decompress(archiveBytes[meta.start:meta.end])
            out.write(decompressedBytes)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--version", help="version to process", default="mm.us.rev1")

    args = parser.parse_args()

    archivesCsvPath = Path(f"tools/filelists/{args.version}/archives.csv")

    # archivesNames: list[Path] = []
    with archivesCsvPath.open() as f:
        for line in f:
            archiveName = line.strip().split(",")[1]
            archivePath = Path(f"baserom/{archiveName}")

            extractedPath = Path(str(archivePath) + "_extracted")
            print(f"Extracting '{archivePath}' -> '{extractedPath}'")
            extractArchive(archivePath, extractedPath)
            # print()
            # archivesNames.append()


if __name__ == "__main__":
    main()
