#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
from pathlib import Path
import struct
import subprocess

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

def writeWordAsBytes(buff: bytearray, offset: int, word: int):
    struct.pack_into(f">I", buff, offset, word)


MAX_RUNLEN = 0xFF + 0x12

def simpleEnc(src: bytearray, pos: int) -> tuple[int, int]:
    numBytes = 1
    matchPos = 0

    startPos = pos - 0x1000
    end = len(src) - pos

    if startPos < 0:
        startPos = 0

    # maximum runlength for 3 byte encoding
    if end > MAX_RUNLEN:
        end = MAX_RUNLEN

    for i in range(startPos, pos):
        j = 0

        while j < end:
            if src[i + j] != src[j + pos]:
                break
            j += 1

        if j > numBytes:
            numBytes = j
            matchPos = i

    if numBytes == 2:
        numBytes = 1

    return numBytes, matchPos

numBytes1 = 0
matchPos = 0
prevFlag = 0

def nintendoEnc(src: bytearray, pos: int) -> tuple[int, int]:
    global numBytes1
    global matchPos
    global prevFlag
    numBytes = 1

    if prevFlag == 1:
        prevFlag = 0
        return numBytes1, matchPos

    prevFlag = 0
    numBytes, matchPos = simpleEnc(src, pos)
    pMatchPos = matchPos

    if numBytes >= 3:
        numBytes1, matchPos = simpleEnc(src, pos + 1)
        if numBytes1 >= numBytes + 2:
            numBytes = 1
            prevFlag = 1

    return numBytes, pMatchPos


def Yaz0Encode(src: bytearray) -> bytearray:
    dst = bytearray()
    srcPos = 0
    dstPos = 0
    bufPos = 0

    dst.append(ord("Y"))
    dst.append(ord("a"))
    dst.append(ord("z"))
    dst.append(ord("0"))
    dst.extend([0] * 0xC)

    writeWordAsBytes(dst, 4, len(src))

    buf = bytearray([0] * 24) # 8 codes * 3 bytes maximum

    validBitCount = 0 # number of valid bits left in "code" byte
    currCodeByte = 0 # a bitfield, set bits meaning copy, unset meaning RLE

    while srcPos < len(src):
        numBytes, matchPos = nintendoEnc(src, srcPos)

        if numBytes < 3:
            # straight copy
            buf[bufPos] = src[srcPos]
            bufPos += 1
            srcPos += 1
            # set flag for straight copy
            currCodeByte |= (0x80 >> validBitCount)
        else:
            # RLE part
            dist = srcPos - matchPos - 1

            if (numBytes >= 0x12): # 3 byte encoding
                byte1 = 0 | (dist >> 8)
                byte2 = dist & 0xFF
                buf[bufPos] = byte1
                bufPos += 1
                buf[bufPos] = byte2
                bufPos += 1
                # maximum runlength for 3 byte encoding
                if (numBytes > MAX_RUNLEN):
                    numBytes = MAX_RUNLEN
                byte3 = numBytes - 0x12
                buf[bufPos] = byte3
                bufPos += 1
            else: # 2 byte encoding
                byte1 = ((numBytes - 2) << 4) | (dist >> 8)
                byte2 = dist & 0xFF
                buf[bufPos] = byte1
                bufPos += 1
                buf[bufPos] = byte2
                bufPos += 1
            srcPos += numBytes

        validBitCount += 1

        # write eight codes
        if validBitCount == 8:
            dst.append(currCodeByte)
            for j in range(bufPos):
                dst.append(buf[j])

            currCodeByte = 0
            validBitCount = 0
            bufPos = 0

    if validBitCount > 0:
        dst.append(currCodeByte)
        for j in range(bufPos):
            dst.append(buf[j])

        currCodeByte = 0
        validBitCount = 0
        bufPos = 0

    return dst



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


def printArchive(archive: bytearray):
    for i, byte in enumerate(archive):
        print(f"{byte:02X} ", end="")
        if i % 16 == 15:
            print()
        elif i % 16 == 7:
            print(" ", end="")
    print()

def createArchive(uncompressedData: bytearray, symbolList: list[Symbol]) -> bytearray:
    archive = bytearray()

    firstEntryOffset = (len(symbolList) + 1) * 4

    # Fill with zeroes until the compressed data start
    archive.extend([0]*firstEntryOffset)

    writeWordAsBytes(archive, 0, firstEntryOffset)

    offset = len(archive)

    i = 0
    for sym in symbolList:
        compressed = bytearray(Yaz0Encode(uncompressedData[sym.offset:sym.offset + sym.size]))

        # Pad to 0x10
        while len(compressed) % 0x10 != 0:
            compressed.extend([0xFF])

        archive.extend(compressed)

        if i > 0:
            writeWordAsBytes(archive, i * 4, offset - firstEntryOffset)

        i += 1
        offset += len(compressed)

    writeWordAsBytes(archive, i * 4, offset - firstEntryOffset)

    while len(archive) % 0x10 != 0:
        archive.extend([0])

    # printArchive(archive)

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

    # Delete output files if they already exists
    outBinPath.unlink(missing_ok=True)
    outSymPath.unlink(missing_ok=True)

    elfBytes = readFileAsBytearray(inPath)

    uncompressedData, symbolList, dataOffset = getDataFromElf(inPath)
    assert len(uncompressedData) > 0
    assert len(symbolList) > 0
    assert dataOffset > 0

    # This should always be sorted in ascending order, but just to be sure
    symbolList.sort(key=lambda x: x.offset)

    archive = createArchive(uncompressedData, symbolList)

    # Write the compressed archive file as a raw binary
    outBinPath.write_bytes(archive)

    # zero out data
    for i in range(dataOffset, dataOffset+len(uncompressedData)):
        elfBytes[i] = 0

    outSymPath.write_bytes(elfBytes)


if __name__ == "__main__":
    main()
