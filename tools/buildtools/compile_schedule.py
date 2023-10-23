#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT


from __future__ import annotations

import argparse
import dataclasses
import enum
from pathlib import Path
import re
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
    BRANCH = "branch"

    # Extra tokens
    ELSE = "else"
    BRACE_OPEN = "{"
    BRACE_CLOSE = "}"
    ARGS = "(args)"
    NOT = "not"
    LABEL = "label"

    def canBeStartingToken(self) -> bool:
        if self in { TokenType.ELSE, TokenType.BRACE_OPEN, TokenType.BRACE_CLOSE, TokenType.ARGS, TokenType.NOT, TokenType.LABEL }:
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

    def isUnconditionalBranch(self) -> bool:
        if self in {
            TokenType.BRANCH_S,
            TokenType.BRANCH_L,
            TokenType.BRANCH,
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
            TokenType.BRANCH_S,
            TokenType.BRANCH_L,
            TokenType.BRANCH,
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
    "branch": TokenType.BRANCH,

    "else": TokenType.ELSE,
    "{": TokenType.BRACE_OPEN,
    "}": TokenType.BRACE_CLOSE,
    "not": TokenType.NOT,
}

regex_label = re.compile(r"(?P<label>\w+)\s*:")
regex_identifier = re.compile(r"(?P<identifier>\w+)")
regex_individualTokens = re.compile(r"(?P<individual>[\{\}])")

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


# Strips comments
def preprocess(contents: str, filename: str) -> str:
    result = ""

    lineNumber = 1
    columnNumber = 1

    blockComment = False
    lineComment = False

    contentsLength = len(contents)
    i = 0
    while i < contentsLength:
        char = contents[i]

        if blockComment and lineComment:
            eprint(f"Error: internal error. {filename}:{lineNumber}:{columnNumber}")
            debugPrint(f" if blockComment and lineComment:")
            debugPrint(f" internal index: {i}")
            exit(1)

        if char == "\n":
            lineComment = False
            result += char
            lineNumber += 1
            columnNumber = 1
            i += 1
        elif blockComment or lineComment:
            if blockComment and contents[i:i+2] == "*/":
                # end of block comment
                blockComment = False
                result += " " * 2
                columnNumber += 2
                i += 2
                continue

            result += " "
            columnNumber += 1
            i += 1
        elif contents[i:i+2] == "/*":
            # block comment
            endIndex = contents.find("*/", i+2)
            if endIndex == -1:
                eprint(f"Error: Unterminated comment at {filename}:{lineNumber}:{columnNumber}")
                debugPrint(f" internal index: {i}")
                exit(1)
            blockComment = True
            result += " " * 2
            columnNumber += 2
            i += 2
        elif contents[i:i+2] == "//":
            # line comment
            lineComment = True
            result += " " * 2
            columnNumber += 2
            i += 2
        else:
            result += char
            columnNumber += 1
            i += 1

    return result


def tokenize(contents: str, filename: str) -> Iterator[Token]:
    lineNumber = 1
    columnNumber = 1

    contentsLength = len(contents)
    i = 0
    while i < contentsLength:
        char = contents[i]

        if char == "(":
            # Command arguments are handled in a special way
            lineNumberStart = lineNumber
            columnNumberStart = columnNumber

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
                    break
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

        if char == "\n":
            lineNumber += 1
            columnNumber = 1
        elif char.isspace():
            columnNumber += 1
        else:
            # Look for tokens
            if (reMatch := regex_label.match(contents, pos=i)) is not None:
                literal = reMatch["label"]
                tokenType = TokenType.LABEL
            elif (reMatch := regex_identifier.match(contents, pos=i)) is not None:
                literal = reMatch["identifier"]
                tokenType = tokenLiterals.get(literal)
            elif (reMatch := regex_individualTokens.match(contents, pos=i)) is not None:
                literal = reMatch["individual"]
                tokenType = tokenLiterals.get(literal)
            else:
                eprint(f"Error: Unrecognized token found at {filename}:{lineNumber}:{columnNumber}")
                debugPrint(f" internal index: {i}\n char: {char}")
                exit(1)

            if tokenType is None:
                eprint(f"Error: Unrecognized token found '{literal}' at {filename}:{lineNumber}:{columnNumber}")
                debugPrint(f" internal index: {i}\n char: {char}")
                exit(1)
            yield Token(tokenType, literal, lineNumber, columnNumber)

            spanStart, spanEnd = reMatch.span()
            matchLen = spanEnd - spanStart
            columnNumber += matchLen
            i += matchLen
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
        if self.expr.tokenType == TokenType.LABEL:
            print(f":", end="")
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
                if len(currentExpr.right) != 0:
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
                if len(currentExpr.right) != 0:
                    eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: BRACE_OPEN foundElse")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)
                currentExpr.right = subExprs
            else:
                if len(currentExpr.left) != 0:
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

        elif token.tokenType == TokenType.LABEL:
            nextToken = tokens.get()
            tokens.unget()
            if nextToken is None:
                eprint(f"Error: label followed by nothing at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: NOT canBeStartingToken")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}\n current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)
            if not nextToken.tokenType.canBeStartingToken():
                eprint(f"Error: label followed by not admitted token '{nextToken.tokenLiteral}' at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: NOT canBeStartingToken")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}\n current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)
            currentExpr = Expression(token)
            foundElse = False
            exprs.append(currentExpr)

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
    TokenType.IF_AFTERTIME_S:       CommandInfo('SCHEDULE_CMD_CHECK_BEFORE_TIME_S',  0x04,),
    TokenType.IF_AFTERTIME_L:       CommandInfo('SCHEDULE_CMD_CHECK_BEFORE_TIME_L',  0x05,),
    TokenType.BRANCH_S:             CommandInfo('SCHEDULE_CMD_BRANCH_S',             0x02,),
    TokenType.BRANCH_L:             CommandInfo('SCHEDULE_CMD_BRANCH_L',             0x03,),

    TokenType.BRANCH:               CommandInfo('SCHEDULE_CMD_BRANCH_S',             0x02,),
}



@dataclasses.dataclass
class LinearExpression:
    offset: int

    expr: Token
    args: Token|None

    labelName: str|None

    # The branch target can be either an int (offset), str (label) or None (no branch target)
    branchTarget: int|str|None = None

    def getTargetOffset(self, linearizedExprs: list[LinearExpression]) -> int:
        if self.branchTarget is None:
            eprint(f"Internal error: no target offset for expression? at :{self.expr.lineNumber}:{self.expr.columnNumber}")
            debugPrint(f" getTargetOffset")
            exit(1)
        if isinstance(self.branchTarget, int):
            return self.branchTarget
        for linExpr in linearizedExprs:
            if linExpr.labelName == self.branchTarget:
                return linExpr.offset

        eprint(f"Error: label name {self.branchTarget} not found, used at :{self.expr.lineNumber}:{self.expr.columnNumber}")
        debugPrint(f" getTargetOffset")
        exit(1)

def linearizeTree(tree: list[Expression], byteCount = 0) -> tuple[list[LinearExpression], int]:
    result: list[LinearExpression] = []
    # To track labels
    labelName: str|None = None

    for expr in tree:
        if expr.expr.tokenType == TokenType.LABEL:
            labelName = expr.expr.tokenLiteral
            continue
        info = cmdInfos[expr.expr.tokenType]
        currentOffset = byteCount

        byteCount += info.cmdLenght

        subResults = []
        left = expr.left
        right = expr.right
        if expr.expr.tokenType.needsToInvert():
            left, right = right, left
        if expr.negated:
            left, right = right, left

        sub, byteCount = linearizeTree(left, byteCount)
        targetOffset = byteCount

        subResults += sub

        if len(right) == 1 and right[0].expr.tokenType.isUnconditionalBranch():
            # If an `if_` only has 1 expression and it is a branch then incorporate it as part of the `if_`,
            # avoiding redundant branches
            sub = []
            branchExpr = right[0]
            if branchExpr.args is None:
                eprint(f"Error: branch command without arguments? at :{branchExpr.expr.lineNumber}:{branchExpr.expr.columnNumber}")
                debugPrint(f" linearizeTree")
                exit(1)
            targetOffset = branchExpr.args.tokenLiteral
        else:
            sub, byteCount = linearizeTree(right, byteCount)
            subResults += sub

        linearExpr = LinearExpression(currentOffset, expr.expr, expr.args, labelName)
        labelName = None

        if expr.expr.tokenType.isBranch() or expr.expr.tokenType.isUnconditionalBranch():
            linearExpr.branchTarget = targetOffset

        result += [linearExpr] + subResults

    return result, byteCount

def emitLinearizedMacros(linearizedExprs: list[LinearExpression], byteCount: int) -> str:
    result = ""

    offsetWidth = len(f"{byteCount:X}")

    for linExpr in linearizedExprs:
        info = cmdInfos[linExpr.expr.tokenType]
        currentMacro = f"    /* 0x{linExpr.offset:0{offsetWidth}X} */ {info.macro}("

        nextOffset = linExpr.offset + info.cmdLenght

        if linExpr.expr.tokenType.isUnconditionalBranch():
            currentMacro += f"0x{linExpr.getTargetOffset(linearizedExprs):0{offsetWidth}X} - 0x{nextOffset:0{offsetWidth}X}"
        else:
            if linExpr.args is not None:
                currentMacro += f"{linExpr.args.tokenLiteral}"
            if linExpr.expr.tokenType.isBranch():
                currentMacro += f", 0x{linExpr.getTargetOffset(linearizedExprs):0{offsetWidth}X} - 0x{nextOffset:0{offsetWidth}X}"
        currentMacro += "),\n"

        result += currentMacro

    return result


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

    preprocessed = preprocess(inputContents, str(inputPath))

    tokens = TokenIterator(tokenize(preprocessed, str(inputPath)))
    tree = makeTree(tokens, str(inputPath))
    assert tokens.remainingTokens() == 0
    if printTree:
        for expr in tree:
            expr.print()

    linearizedExprs, byteCount = linearizeTree(tree)
    output = emitLinearizedMacros(linearizedExprs, byteCount)

    if outputPath is None:
        print(output)
    else:
        outputPath.parent.mkdir(parents=True, exist_ok=True)
        outputPath.write_text(output)


if __name__ == "__main__":
    main()
