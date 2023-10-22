#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT


from __future__ import annotations

import argparse
import dataclasses
import enum
from pathlib import Path
from typing import Iterator
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
    IF_AFTERTIME_S = "if_since_time_s"
    IF_AFTERTIME_L = "if_since_time_l"
    BRANCH_S = "branch_s" # TODO
    BRANCH_L = "branch_l" # TODO

    # Extra tokens
    ELSE = "else"
    BRACE_OPEN = "{"
    BRACE_CLOSE = "}"
    ARGS = "(args)"
    NOT = "not"

    def canBeStartingToken(self) -> bool:
        if self in { TokenType.ELSE, TokenType.BRACE_OPEN, TokenType.BRACE_CLOSE, TokenType.ARGS, TokenType.NOT }:
            return False
        return True

    def isBranch(self) -> bool:
        if self in {
            TokenType.IF_WEEKEVENTREG_S,
            TokenType.IF_WEEKEVENTREG_L,
            TokenType.IF_TIMERANGE_S,
            TokenType.IF_TIMERANGE_L,
            TokenType.IF_MISC_S,
            TokenType.IF_SCENE_S,
            TokenType.IF_SCENE_L,
            TokenType.IF_DAY_S,
            TokenType.IF_DAY_L,
            TokenType.IF_BEFORETIME_S,
            TokenType.IF_BEFORETIME_L,
            TokenType.IF_AFTERTIME_S,
            TokenType.IF_AFTERTIME_L,
        }:
            return True
        return False

    def isReturn(self) -> bool:
        if self in { TokenType.RETURN_S, TokenType.RETURN_L, TokenType.RETURN_NONE, TokenType.RETURN_EMPTY, TokenType.RETURN_TIME }:
            return True
        return False

    def hasArguments(self) -> bool:
        if self in {
            TokenType.IF_WEEKEVENTREG_S,
            TokenType.IF_WEEKEVENTREG_L,
            TokenType.IF_TIMERANGE_S,
            TokenType.IF_TIMERANGE_L,
            TokenType.RETURN_S,
            TokenType.RETURN_L,
            TokenType.IF_MISC_S,
            TokenType.IF_SCENE_S,
            TokenType.IF_SCENE_L,
            TokenType.IF_DAY_S,
            TokenType.IF_DAY_L,
            TokenType.RETURN_TIME,
            TokenType.IF_BEFORETIME_S,
            TokenType.IF_BEFORETIME_L,
            TokenType.IF_AFTERTIME_S,
            TokenType.IF_AFTERTIME_L,
        }:
            return True
        return False

    def needsToInvert(self) -> bool:
        if self in {
            TokenType.IF_WEEKEVENTREG_S,
            TokenType.IF_WEEKEVENTREG_L,
            TokenType.IF_TIMERANGE_S,
            TokenType.IF_TIMERANGE_L,
            TokenType.IF_MISC_S,
            TokenType.IF_BEFORETIME_S,
            TokenType.IF_BEFORETIME_L,
            }:
            return True
        return False

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
    "if_since_time_s": TokenType.IF_AFTERTIME_S,
    "if_since_time_l": TokenType.IF_AFTERTIME_L,
    "branch_s": TokenType.BRANCH_S,
    "branch_l": TokenType.BRANCH_L,

    "else": TokenType.ELSE,
    "{": TokenType.BRACE_OPEN,
    "}": TokenType.BRACE_CLOSE,
    "not": TokenType.NOT,
}

@dataclasses.dataclass
class Token:
    tokenType: TokenType
    tokenLiteral: str
    lineNumber: int
    columnNumber: int


class TokenIterator:
    def __init__(self, tokens: Iterator[Token]):
        self.tokens = list(tokens)
        self.index = 0

    def get(self) -> Token|None:
        if self.index >= len(self.tokens):
            return None
        token = self.tokens[self.index]
        self.index += 1
        return token

    def unget(self) -> None:
        self.index -= 1
        if self.index < 0:
            raise RuntimeError()

    def remainingTokens(self) -> int:
        return len(self.tokens) - self.index


def tokenize(contents: str, filename: str) -> Iterator[Token]:
    lineNumber = 1
    columnNumber = 1

    contentsLength = len(contents)
    i = 0
    while i < contentsLength:
        char = contents[i]

        if contents[i:i+2] == "/*":
            # comment
            endIndex = contents.find("*/", i+2)
            if endIndex == -1:
                eprint(f"Error: Unterminated comment at {filename}:{lineNumber}:{columnNumber}")
                debugPrint(f" internal index: {i}\n char: {char}")
                exit(1)
            lineNumber += contents.count("\n", i+2, endIndex)
            lastNewLineIndex = contents.rfind("\n", i+2, endIndex)
            if lastNewLineIndex < 0:
                columnNumber += endIndex - i
            else:
                columnNumber += endIndex - lastNewLineIndex
            i = endIndex + 2
            continue

        if contents[i:i+2] == "//":
            # comment
            endIndex = contents.find("\n", i+2)
            if endIndex == -1:
                eprint(f"Error: Unterminated comment at {filename}:{lineNumber}:{columnNumber}")
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
                subChar = contents[subIndex]
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
                eprint(f"Error: Unterminated parenthesis at {filename}:{lineNumber}:{columnNumber}")
                debugPrint(f" internal index: {i}\n char: {char}")
                exit(1)
            parenContents = contents[i+1:subIndex]
            yield Token(TokenType.ARGS, parenContents, lineNumberStart, columnNumberStart)

            i = subIndex + 1
            columnNumber += 1
            continue

        if char in "{}":
            if char == "{":
                tokenType = TokenType.BRACE_OPEN
            else:
                tokenType = TokenType.BRACE_CLOSE
            yield Token(tokenType, char, lineNumber, columnNumber)
            i += 1
            columnNumber += 1
            continue

        if char == "\n":
            lineNumber += 1
            columnNumber = 1
        elif char.isspace():
            columnNumber += 1
        else:
            # Look for tokens
            lineEndIndex = contents.find("\n", i)
            spaceIndex = contents.find(" ", i)
            if lineEndIndex < 0 and spaceIndex < 0:
                tokenEndIndex = len(contents)
            elif lineEndIndex < 0 and spaceIndex >= 0:
                tokenEndIndex = spaceIndex
            elif lineEndIndex >= 0 and spaceIndex < 0:
                tokenEndIndex = lineEndIndex
            else:
                tokenEndIndex = min(lineEndIndex, spaceIndex)
            literal = contents[i:tokenEndIndex]
            tokenType = tokenLiterals.get(literal)
            if tokenType is None:
                eprint(f"Error: Unrecognized token found '{literal}' at {filename}:{lineNumber}:{columnNumber}")
                debugPrint(f" internal index: {i}\n char: {char}\n tokenEndIndex: {tokenEndIndex}")
                exit(1)
            yield Token(tokenType, literal, lineNumber, columnNumber)
            columnNumber += len(literal)
            i += len(literal)
            continue

        i += 1



@dataclasses.dataclass
class Expression:
    expr: Token
    args: Token|None = None

    left: list[Expression] = dataclasses.field(default_factory=list)
    right: list[Expression] = dataclasses.field(default_factory=list)

    negated: bool = False

    def print(self, depth=0):
        spaces = "    " * depth
        print(f"{spaces}", end="")
        if self.negated:
            print(f"not ", end="")
        print(f"{self.expr.tokenLiteral}", end="")
        if self.args is not None:
            print(f"({self.args.tokenLiteral})", end="")
        if len(self.left) == 0:
            print()
        else:
            print(" {")
            for expr in self.left:
                expr.print(depth+1)
            if len(self.right) > 0:
                print(f"{spaces}}} else {{")
                for expr in self.right:
                    expr.print(depth+1)
            print(f"{spaces}}}")


def makeTree(tokens: TokenIterator, inputPath: str, *, depth: int=0) -> list[Expression]:
    exprs: list[Expression] = []

    currentExpr: Expression|None = None
    foundElse = False

    i = 0
    while (token := tokens.get()) is not None:
        if token.tokenType == TokenType.ARGS:
            if currentExpr is None or currentExpr.args is not None:
                eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: ARGS")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}\n current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)

            currentExpr.args = token

        elif token.tokenType.canBeStartingToken() or token.tokenType == TokenType.NOT:
            if currentExpr is not None and currentExpr.expr.tokenType.isBranch():
                if len(currentExpr.left) == 0:
                    eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: canBeStartingToken")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)

            negate = False
            if token.tokenType == TokenType.NOT:
                negate = True
                tokenAux = tokens.get()
                if tokenAux is None:
                    eprint(f"Error: `not` operator followed by nothing at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: NOT canBeStartingToken")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)
                token = tokenAux
                if not token.tokenType.canBeStartingToken():
                    eprint(f"Error: `not` operator followed invalid token at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: NOT canBeStartingToken")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)

            currentExpr = Expression(token)
            currentExpr.negated = negate
            foundElse = False
            exprs.append(currentExpr)
            if not token.tokenType.hasArguments():
                currentExpr = None

        elif token.tokenType == TokenType.ELSE:
            if currentExpr is None or currentExpr.args is None or foundElse:
                eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: ELSE")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}")
                debugPrint(f" current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)
            foundElse = True

            # Peek next token
            nextToken = tokens.get()
            if nextToken is None:
                eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                eprint(f"    missing expression after `else`")
                debugPrint(" makeTree: ELSE")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}")
                debugPrint(f" current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)

            tokens.unget()
            if nextToken.tokenType != TokenType.BRACE_OPEN:
                # Else with no braces, try to parse it
                if len(currentExpr.left) == 0 or len(currentExpr.right) != 0:
                    eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: BRACE_OPEN foundElse")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)
                subExprs = makeTree(tokens, inputPath, depth=depth+1)
                currentExpr.right = subExprs
                return exprs

        elif token.tokenType == TokenType.BRACE_OPEN:
            # The body of an `if` or an `else`

            if currentExpr is None or currentExpr.args is None:
                eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: BRACE_OPEN")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}\n current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)

            subExprs = makeTree(tokens, inputPath, depth=depth+1)
            if foundElse:
                if len(currentExpr.left) == 0 or len(currentExpr.right) != 0:
                    eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: BRACE_OPEN foundElse")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)
                currentExpr.right = subExprs
            else:
                if len(currentExpr.left) != 0 or len(currentExpr.right) != 0:
                    eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: BRACE_OPEN not foundElse")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)
                currentExpr.left = subExprs

        elif token.tokenType == TokenType.BRACE_CLOSE:
            if len(exprs) == 0:
                eprint(f"Warning: Braces with empty body at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                # eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                # debugPrint(" makeTree: BRACE_CLOSE")
                # debugPrint(f" i: {i}")
                # debugPrint(f" depth: {depth}")
                # debugPrint(f" token: {token}\n current expression: {currentExpr}")
                # debugPrint(f" foundElse: {foundElse}")
                # exit(1)

            return exprs

        else:
            eprint("This code should be unreachable")
            debugPrint(" makeTree: UNREACHABLE")
            debugPrint(f" i: {i}")
            debugPrint(f" depth: {depth}")
            debugPrint(f" token: {token}\n current expression: {currentExpr}")
            debugPrint(f" foundElse: {foundElse}")
            exit(1)

        i += 1

    return exprs


@dataclasses.dataclass
class CommandInfo:
    macro: str
    cmdLenght: int

cmdInfos: dict[TokenType, CommandInfo] = {
    TokenType.IF_WEEKEVENTREG_S:    CommandInfo('SCHEDULE_CMD_CHECK_FLAG_S',         0x04,),
    TokenType.IF_WEEKEVENTREG_L:    CommandInfo('SCHEDULE_CMD_CHECK_FLAG_L',         0x05,),
    TokenType.IF_TIMERANGE_S:       CommandInfo('SCHEDULE_CMD_CHECK_TIME_RANGE_S',   0x06,),
    TokenType.IF_TIMERANGE_L:       CommandInfo('SCHEDULE_CMD_CHECK_TIME_RANGE_L',   0x07,),
    TokenType.RETURN_S:             CommandInfo('SCHEDULE_CMD_RET_VAL_S',            0x02,),
    TokenType.RETURN_L:             CommandInfo('SCHEDULE_CMD_RET_VAL_L',            0x03,),
    TokenType.RETURN_NONE:          CommandInfo('SCHEDULE_CMD_RET_NONE',             0x01,),
    TokenType.RETURN_EMPTY:         CommandInfo('SCHEDULE_CMD_RET_EMPTY',            0x01,),
    TokenType.IF_MISC_S:            CommandInfo('SCHEDULE_CMD_CHECK_MISC_S',         0x03,),
    TokenType.IF_SCENE_S:           CommandInfo('SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S', 0x04,),
    TokenType.IF_SCENE_L:           CommandInfo('SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L', 0x05,),
    TokenType.IF_DAY_S:             CommandInfo('SCHEDULE_CMD_CHECK_NOT_IN_DAY_S',   0x04,),
    TokenType.IF_DAY_L:             CommandInfo('SCHEDULE_CMD_CHECK_NOT_IN_DAY_L',   0x05,),
    TokenType.NOP:                  CommandInfo('SCHEDULE_CMD_NOP',                  0x04,),
    TokenType.RETURN_TIME:          CommandInfo('SCHEDULE_CMD_RET_TIME',             0x06,),
    TokenType.IF_BEFORETIME_S:      CommandInfo('SCHEDULE_CMD_CHECK_BEFORE_TIME_S',  0x04,),
    TokenType.IF_BEFORETIME_L:      CommandInfo('SCHEDULE_CMD_CHECK_BEFORE_TIME_L',  0x05,),
    TokenType.IF_AFTERTIME_S:      CommandInfo('SCHEDULE_CMD_CHECK_BEFORE_TIME_S',  0x04,),
    TokenType.IF_AFTERTIME_L:      CommandInfo('SCHEDULE_CMD_CHECK_BEFORE_TIME_L',  0x05,),
    TokenType.BRANCH_S:             CommandInfo('SCHEDULE_CMD_BRANCH_S',             0x02,),
    TokenType.BRANCH_L:             CommandInfo('SCHEDULE_CMD_BRANCH_L',             0x03,),
}


def emitMacros(tree: list[Expression], byteCount = 0) -> tuple[str, int]:
    result = ""

    for expr in tree:
        info = cmdInfos[expr.expr.tokenType]
        currentMacro = f"    /* 0x{byteCount:02X} */ {info.macro}("

        byteCount += info.cmdLenght
        currentOffset = byteCount

        subResults = ""
        left = expr.left
        right = expr.right
        if expr.expr.tokenType.needsToInvert():
            left, right = right, left
        if expr.negated:
            left, right = right, left

        sub, byteCount = emitMacros(left, byteCount)
        targetOffset = byteCount

        subResults += sub
        sub, byteCount = emitMacros(right, byteCount)
        subResults += sub
        byteCount = byteCount

        if expr.args is not None:
            currentMacro += f"{expr.args.tokenLiteral}"
        if expr.expr.tokenType.isBranch():
            currentMacro += f", 0x{targetOffset:02X} - 0x{currentOffset:02X}"
        currentMacro += "),\n"

        result += currentMacro + subResults

    return result, byteCount


def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("input", help="Schedule script path", type=Path)
    parser.add_argument("-o", "--output", help="Output path. Will print to stdout if omitted", type=Path)

    debuggingParser = parser.add_argument_group("Debugging options")
    debuggingParser.add_argument("-p", "--print-tree", help="Prints the processed tree to stdout", action="store_true")

    args = parser.parse_args()

    inputPath: Path = args.input
    outputPath: Path|None = args.output

    printTree: bool = args.print_tree

    if not inputPath.exists():
        eprint(f"Error: Input file '{inputPath}' not found")
        exit(1)

    inputContents = inputPath.read_text("UTF-8")

    tokens = TokenIterator(tokenize(inputContents, str(inputPath)))
    tree = makeTree(tokens, str(inputPath))
    assert tokens.remainingTokens() == 0
    if printTree:
        for expr in tree:
            expr.print()
    output, byteCount = emitMacros(tree)

    if outputPath is None:
        print(output)
    else:
        outputPath.parent.mkdir(parents=True, exist_ok=True)
        outputPath.write_text(output)


if __name__ == "__main__":
    main()
