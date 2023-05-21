#!/usr/bin/env python3

import argparse
import math
import re

def isValid(index: int, mask: int) -> bool:
    if index < 0 or index > 7:
        return False
    if mask != (1 << int(math.log2(mask))):
        return False
    return True

def getFlagMacro(index: int, mask: int) -> str:
    return f"EVENTINF_{index}{int(math.log2(mask))}"

def getCheckMacro(index: int, mask: int) -> str:
    return f"CHECK_EVENTINF({getFlagMacro(index, mask)})"

def getSetMacro(index: int, mask: int) -> str:
    return f"SET_EVENTINF({getFlagMacro(index, mask)})"

def getClearMacro(index: int, mask: int) -> str:
    return f"CLEAR_EVENTINF({getFlagMacro(index, mask)})"

NUMBER_PATTERN = r"(0[xX])?[0-9a-fA-F]+"

def applyChange(fileContents: str, compiledRegex: re.Pattern, callback) -> str:
    parsedContents = ""

    match = compiledRegex.search(fileContents)
    while match:
        index = int(match.group("index"), 0)
        mask = int(match.group("mask"), 0)

        start, end = match.span()
        parsedContents += fileContents[:start]
        if isValid(index, mask):
            parsedContents += callback(index, mask)
        else:
            parsedContents += fileContents[start:end]

        fileContents = fileContents[end:]
        match = compiledRegex.search(fileContents)

    parsedContents += fileContents
    return parsedContents


def updateCheck(fileContents: str) -> str:
    checkRegex = re.compile(rf"gSaveContext.eventInf\[(?P<index>{NUMBER_PATTERN})\]\s*\&\s*(?P<mask>{NUMBER_PATTERN})")

    return applyChange(fileContents, checkRegex, getCheckMacro)

def updateSet(fileContents: str) -> str:
    setRegex = re.compile(rf"gSaveContext.eventInf\[(?P<index>{NUMBER_PATTERN})\]\s*\|=\s*(?P<mask>{NUMBER_PATTERN})")

    return applyChange(fileContents, setRegex, getSetMacro)

def updateClear(fileContents: str) -> str:
    clearRegex = re.compile(rf"gSaveContext.eventInf\[(?P<index>{NUMBER_PATTERN})\]\s*\&=\s*(\(u8\))?~(?P<mask>{NUMBER_PATTERN})")

    return applyChange(fileContents, clearRegex, getClearMacro)


def read_file(filename):
    with open(filename) as src_file:
        return src_file.read()

def write_file(filename, contents):
    with open(filename, "w") as f:
        f.write(contents)


def main():
    parser = argparse.ArgumentParser(description="Converts a eventInf access to a macro")

    parser.add_argument("filename", help="Replace every occurrence of numeric eventInf on this file to the corresponding macro")
    args = parser.parse_args()

    fileContents = read_file(args.filename)

    parsedContents = updateCheck(fileContents)
    parsedContents = updateSet(parsedContents)
    parsedContents = updateClear(parsedContents)

    if fileContents != parsedContents:
        write_file(args.filename, parsedContents)

if __name__ == "__main__":
    main()
