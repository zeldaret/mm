#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
# import libyaz0
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
                break;
            j += 1

        if j > numBytes:
            numBytes = j
            matchPos = i

    if numBytes == 2:
        numBytes = 1;

    return numBytes, matchPos

numBytes1 = 0
matchPos = 0
prevFlag = 0

# a lookahead encoding scheme for ngc Yaz0
def nintendoEnc(src: bytearray, pos: int) -> tuple[int, int]:
    global numBytes1
    global matchPos
    global prevFlag
    numBytes = 1

    # if prevFlag is set, it means that the previous position
    # was determined by look-ahead try.
    # so just use it. this is not the best optimization,
    # but nintendo's choice for speed.
    if prevFlag == 1:
        prevFlag = 0;
        return numBytes1, matchPos

    prevFlag = 0;
    numBytes, matchPos = simpleEnc(src, pos);
    pMatchPos = matchPos;

    # if this position is RLE encoded, then compare to copying 1 byte and next position(pos+1) encoding
    if numBytes >= 3:
        numBytes1, matchPos = simpleEnc(src, pos + 1);
        # if the next position encoding is +2 longer than current position, choose it.
        # this does not guarantee the best optimization, but fairly good optimization with speed.
        if numBytes1 >= numBytes + 2:
            numBytes = 1;
            prevFlag = 1;

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

        numBytes, matchPos = nintendoEnc(src, srcPos);
        if numBytes < 3:
            # straight copy
            buf[bufPos] = src[srcPos];
            bufPos += 1
            srcPos += 1
            # set flag for straight copy
            currCodeByte |= (0x80 >> validBitCount);
        else:
            # RLE part
            dist = srcPos - matchPos - 1;
            # byte1, byte2, byte3;

            if (numBytes >= 0x12): # 3 byte encoding
                byte1 = 0 | (dist >> 8);
                byte2 = dist & 0xFF;
                buf[bufPos] = byte1
                bufPos += 1
                buf[bufPos] = byte2
                bufPos += 1
                # maximum runlength for 3 byte encoding
                if (numBytes > MAX_RUNLEN):
                    numBytes = MAX_RUNLEN;
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
            srcPos += numBytes;

        validBitCount += 1

        # write eight codes
        if validBitCount == 8:
            dst.append(currCodeByte)
            for j in range(bufPos):
                # TODO: extend
                dst.append(buf[j])

            currCodeByte = 0;
            validBitCount = 0;
            bufPos = 0;

    if validBitCount > 0:
        dst.append(currCodeByte)
        for j in range(bufPos):
            dst.append(buf[j])

        currCodeByte = 0;
        validBitCount = 0;
        bufPos = 0;

    return dst



@dataclasses.dataclass
class Symbol:
    name: str
    offset: int
    size: int

    # compressedData: bytearray = bytearray()


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

    # for sym in symbolList:
    #     sym.compressedData = bytearray(libyaz0.compress(uncompressedData[sym.offset:sym.offset + sym.size]))

    firstEntryOffset = (len(symbolList) + 1) * 4

    # Fill with zeroes until the compressed data start
    archive.extend([0]*firstEntryOffset)

    writeWordAsBytes(archive, 0, firstEntryOffset)

    # libyaz0.compress()

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

    # for i in range(4, firstEntryOffset-4, 4):
    #

    # printArchive(archive)

    return archive


def invokeCommand(cmd: str):
    # print(cmd)
    try:
        subprocess.check_call(cmd, shell=True)
    except subprocess.CalledProcessError as e:
        # Return the same error code for the wrapper if z64compress fails
        exit(e.returncode)



def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("in_file")
    parser.add_argument("out_file")
    parser.add_argument("--binutils-prefix", default="mips-linux-gnu-")

    args = parser.parse_args()

    inPath = Path(args.in_file)
    outPath = Path(args.out_file)

    uncompressedData = bytearray()
    symbolList: list[Symbol] = []

    with open(inPath, "rb") as elf_file:
        elf = ELFFile(elf_file)
        for section in elf.iter_sections():
            if section.name == ".data":
                assert len(uncompressedData) == 0
                # print(section)
                uncompressedData.extend(section.data())
                # print()
            elif section.name == ".symtab":
                # print(section)
                assert isinstance(section, SymbolTableSection)
                for sym in section.iter_symbols():
                    if sym["st_shndx"] == "SHN_UNDEF":
                        continue
                    if sym["st_info"]["type"] != "STT_OBJECT":
                        continue
                    # print(sym, sym.name, sym.entry)
                    symbolList.append(Symbol(sym.name, sym["st_value"], sym["st_size"]))
                # print()

    # This should always be sorted in ascending order, but just to be sure
    symbolList.sort(key=lambda x: x.offset)

    archive = createArchive(uncompressedData, symbolList)
    binPath = outPath.with_suffix(".bin")

    binPath.write_bytes(archive)

    outPath.unlink(missing_ok=True)

    binutils_prefix = args.binutils_prefix
    invokeCommand(f"{binutils_prefix}objcopy -I binary -O elf32-big {binPath} {outPath}")

    # invokeCommand(f"{binutils_prefix}objcopy -I elf32-big --strip-all {outPath}")

    for sym in symbolList:
        invokeCommand(f"{binutils_prefix}objcopy -I elf32-big --add-symbol {sym.name}=.data:0x{sym.offset:X} {outPath}")



if __name__ == "__main__":
    main()
