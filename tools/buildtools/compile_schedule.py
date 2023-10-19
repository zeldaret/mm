#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT


from __future__ import annotations

import argparse
import dataclasses
import enum
from pathlib import Path
import sys


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

DEBUG = True

def debugPrint(*args, **kwargs):
    if not DEBUG:
        return
    eprint(*args, **kwargs)


class TokenType(enum.Enum):
    # Schedule commands
    IF_WEEKEVENTREG_S = "if_week_event_reg_s"
    IF_WEEKEVENTREG_L = "if_week_event_reg_l"
    IF_TIMERANGE_S = "if_time_range_s"
    IF_TIMERANGE_L = "if_time_range_l"
    RETURN_S = "return_s"
    RETURN_L = "return_l"
    RETURN_NONE = "return_none"
    RETURN_EMPTY = "return_empty"
    IF_MISC_S = "if_misc_s"
    IF_SCENE_S = "if_scene_s"
    IF_SCENE_L = "if_scene_l"
    IF_DAY_S = "if_day_s"
    IF_DAY_L = "if_day_l"
    NOP = "nop"
    RETURN_TIME = "return_time"
    IF_BEFORETIME_S = "if_before_time_s"
    IF_BEFORETIME_L = "if_before_time_l"
    BRANCH_S = "branch_s"
    BRANCH_L = "branch_l"

    # Extra tokens
    ELSE = "else"
    BRACE_OPEN = "{"
    BRACE_CLOSE = "}"
    ARGS = "(args)"

tokenLiterals: dict[str, TokenType] = {
    "if_week_event_reg_s": TokenType.IF_WEEKEVENTREG_S,
    "if_week_event_reg_l": TokenType.IF_WEEKEVENTREG_L,
    "if_time_range_s": TokenType.IF_TIMERANGE_S,
    "if_time_range_l": TokenType.IF_TIMERANGE_L,
    "return_s": TokenType.RETURN_S,
    "return_l": TokenType.RETURN_L,
    "return_none": TokenType.RETURN_NONE,
    "return_empty": TokenType.RETURN_EMPTY,
    "if_misc_s": TokenType.IF_MISC_S,
    "if_scene_s": TokenType.IF_SCENE_S,
    "if_scene_l": TokenType.IF_SCENE_L,
    "if_day_s": TokenType.IF_DAY_S,
    "if_day_l": TokenType.IF_DAY_L,
    "nop": TokenType.NOP,
    "return_time": TokenType.RETURN_TIME,
    "if_before_time_s": TokenType.IF_BEFORETIME_S,
    "if_before_time_l": TokenType.IF_BEFORETIME_L,
    "branch_s": TokenType.BRANCH_S,
    "branch_l": TokenType.BRANCH_L,

    "else": TokenType.ELSE,
    "{": TokenType.BRACE_OPEN,
    "}": TokenType.BRACE_CLOSE,
}

@dataclasses.dataclass
class Token:
    tokenType: TokenType
    tokenLiteral: str
    lineNumber: int
    columnNumber: int

class Tokenizer:
    def __init__(self, contents: str, filename: str):
        self.contents = contents.replace("\t", " ")
        self.filename = filename

    def __iter__(self):
        lineNumber = 1
        columnNumber = 1

        contentsLength = len(self.contents)
        i = 0
        while i < contentsLength:
            char = self.contents[i]

            if self.contents[i:i+2] == "/*":
                # comment
                endIndex = self.contents.find("*/", i+2)
                if endIndex == -1:
                    eprint(f"Error: Unterminated comment at {self.filename}:{lineNumber}:{columnNumber}")
                    debugPrint(f" internal index: {i}\n char: {char}")
                    exit(1)
                lineNumber += self.contents.count("\n", i+2, endIndex)
                lastNewLineIndex = self.contents.rfind("\n", i+2, endIndex)
                if lastNewLineIndex < 0:
                    columnNumber += endIndex - i
                else:
                    columnNumber += endIndex - lastNewLineIndex
                i = endIndex + 2
                continue

            if self.contents[i:i+2] == "//":
                # comment
                endIndex = self.contents.find("\n", i+2)
                if endIndex == -1:
                    eprint(f"Error: Unterminated comment at {self.filename}:{lineNumber}:{columnNumber}")
                    debugPrint(f" internal index: {i}\n char: {char}")
                    exit(1)
                lineNumber += 1
                columnNumber += endIndex - i
                i = endIndex + 1
                continue

            if char == "(":
                # Command arguments are handled in a special way
                lineNumberStart = lineNumber
                columnNumberStart = columnNumber

                # debugPrint("Tokenizer: start (")

                parenCount = 0
                subIndex = i+1
                parenEndFound = False
                while subIndex < contentsLength:
                    # We need to pair this parenthesis, allowing inner parenthesis
                    subChar = self.contents[subIndex]
                    columnNumber += 1
                    if subChar == ")":
                        parenCount -= 1
                    elif subChar == "(":
                        parenCount += 1
                    elif subChar == "\n":
                        lineNumber += 1
                        columnNumber = 1
                    if parenCount < 0:
                        parenEndFound = True
                        # debugPrint("Tokenizer: found paired )")
                        break
                    # debugPrint(f"Tokenizer: {parenCount=}")
                    subIndex += 1

                if not parenEndFound:
                    eprint(f"Error: Unterminated parenthesis at {self.filename}:{lineNumber}:{columnNumber}")
                    debugPrint(f" internal index: {i}\n char: {char}")
                    exit(1)
                parenContents = self.contents[i+1:subIndex]
                yield Token(TokenType.ARGS, parenContents, lineNumberStart, columnNumberStart)

                i = subIndex + 1
                continue

            if char == "\n":
                lineNumber += 1
                columnNumber = 1
            elif char.isspace():
                columnNumber += 1
            else:
                # Look for tokens
                lineEndIndex = self.contents.find("\n", i)
                spaceIndex = self.contents.find(" ", i)
                if lineEndIndex < 0 and spaceIndex < 0:
                    tokenEndIndex = -1
                elif lineEndIndex < 0 and spaceIndex >= 0:
                    tokenEndIndex = spaceIndex
                elif lineEndIndex >= 0 and spaceIndex < 0:
                    tokenEndIndex = lineEndIndex
                else:
                    tokenEndIndex = min(lineEndIndex, spaceIndex)
                literal = self.contents[i:tokenEndIndex]
                tokenType = tokenLiterals.get(literal)
                if tokenType is None:
                    eprint(f"Error: Unrecognized token found '{literal}' at {self.filename}:{lineNumber}:{columnNumber}")
                    debugPrint(f" internal index: {i}\n char: {char}")
                    exit(1)
                yield Token(tokenType, literal, lineNumber, columnNumber)
                columnNumber += len(literal)
                i += len(literal)
                continue

            i += 1


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

    inputContents = inputPath.read_text("UTF-8")
    for token in Tokenizer(inputContents, str(inputPath)):
        print(token)

if __name__ == "__main__":
    main()
