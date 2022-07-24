#!/usr/bin/env python3

import argparse
import re

def getFlagMacro(index: int, mask: int) -> str:
    return f"WEEKEVENTREG_{index:02}_{mask:02X}"

def getGetMacro(index: int, mask: int) -> str:
    return f"CHECK_WEEKEVENTREG({getFlagMacro(index, mask)})"

def getSetMacro(index: int, mask: int) -> str:
    return f"SET_WEEKEVENTREG({getFlagMacro(index, mask)})"

def getClearMacro(index: int, mask: int) -> str:
    return f"CLEAR_WEEKEVENTREG({getFlagMacro(index, mask)})"

NUMBER_PATTERN = r"(0[xX])?[0-9a-fA-F]+"

def applyChange(fileContents: str, compiledRegex: re.Pattern, callback) -> str:
    parsedContents = ""

    match = compiledRegex.search(fileContents)
    while match:
        index = int(match.group("index"), 0)
        mask = int(match.group("mask"), 0)

        start, end = match.span()
        parsedContents += fileContents[:start]
        parsedContents += callback(index, mask)

        fileContents = fileContents[end:]
        match = compiledRegex.search(fileContents)

    parsedContents += fileContents
    return parsedContents


def updateGet(fileContents: str) -> str:
    # gSaveContext.save.weekEventReg[86] & 2
    getRegex = re.compile(rf"gSaveContext.save.weekEventReg\[(?P<index>{NUMBER_PATTERN})\]\s*\&\s*(?P<mask>{NUMBER_PATTERN})")

    return applyChange(fileContents, getRegex, getGetMacro)

def updateSet(fileContents: str) -> str:
    # gSaveContext.save.weekEventReg[51] |= 0x10
    setRegex = re.compile(rf"gSaveContext.save.weekEventReg\[(?P<index>{NUMBER_PATTERN})\]\s*\|=\s*(?P<mask>{NUMBER_PATTERN})")

    return applyChange(fileContents, setRegex, getSetMacro)

def updateClear(fileContents: str) -> str:
    # gSaveContext.save.weekEventReg[85] &= (u8)~0x80
    clearRegex = re.compile(rf"gSaveContext.save.weekEventReg\[(?P<index>{NUMBER_PATTERN})\]\s*\&=\s*(\(u8\))?~(?P<mask>{NUMBER_PATTERN})")

    return applyChange(fileContents, clearRegex, getClearMacro)


def read_file(filename):
    with open(filename) as src_file:
        return src_file.read()

def write_file(filename, contents):
    with open(filename, "w") as f:
        f.write(contents)


def main():
    parser = argparse.ArgumentParser(description="Converts a weekEventReg access to a macro")

    parser.add_argument("filename", help="Replace every occurrence of numeric weekEventReg on this file to the corresponding macro")
    args = parser.parse_args()

    fileContents = read_file(args.filename)

    parsedContents = updateGet(fileContents)
    parsedContents = updateSet(parsedContents)
    parsedContents = updateClear(parsedContents)

    write_file(args.filename, parsedContents)

if __name__ == "__main__":
    main()
