#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

# TODO: Check for repeated labels

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
    IF_SINCETIME_S = "if_since_time_s"
    IF_SINCETIME_L = "if_since_time_l"
    BRANCH_S = "branch_s"
    BRANCH_L = "branch_l"

    # Generics
    IF_WEEKEVENTREG = "if_week_event_reg"
    IF_TIMERANGE = "if_time_range"
    IF_MISC = "if_misc"
    IF_SCENE = "if_scene"
    IF_DAY = "if_day"
    IF_BEFORETIME = "if_before_time"
    IF_SINCETIME = "if_since_time"
    BRANCH = "branch"

    # Extra tokens
    ELSE = "else"
    BRACE_OPEN = "{"
    BRACE_CLOSE = "}"
    ARGS = "(args)"
    NOT = "not"
    LABEL = "label"

@dataclasses.dataclass
class TokenProperties:
    macro: str|None = None
    cmdLength: int|None = None
    isExtraToken: bool = False
    isConditionalBranch: bool = False
    isUnconditionalBranch: bool = False
    hasArguments: bool = False
    isGeneric: bool = False
    needsToInvert: bool = False
    isShort: bool = False
    shortVersion: TokenType|None=None
    longVersion: TokenType|None=None

    @property
    def isAnyBranch(self) -> bool:
        return self.isConditionalBranch or self.isUnconditionalBranch

tokenPropertiesDict: dict[TokenType, TokenProperties] = {
    # Schedule commands
    TokenType.IF_WEEKEVENTREG_S:    TokenProperties(macro="SCHEDULE_CMD_CHECK_FLAG_S",         cmdLength=0x04, isConditionalBranch=True, hasArguments=True, needsToInvert=True, isShort=True, shortVersion=TokenType.IF_WEEKEVENTREG_S, longVersion=TokenType.IF_WEEKEVENTREG_L),
    TokenType.IF_WEEKEVENTREG_L:    TokenProperties(macro="SCHEDULE_CMD_CHECK_FLAG_L",         cmdLength=0x05, isConditionalBranch=True, hasArguments=True, needsToInvert=True,               shortVersion=TokenType.IF_WEEKEVENTREG_S, longVersion=TokenType.IF_WEEKEVENTREG_L),
    TokenType.IF_TIMERANGE_S:       TokenProperties(macro="SCHEDULE_CMD_CHECK_TIME_RANGE_S",   cmdLength=0x06, isConditionalBranch=True, hasArguments=True, needsToInvert=True, isShort=True, shortVersion=TokenType.IF_TIMERANGE_S, longVersion=TokenType.IF_TIMERANGE_L),
    TokenType.IF_TIMERANGE_L:       TokenProperties(macro="SCHEDULE_CMD_CHECK_TIME_RANGE_L",   cmdLength=0x07, isConditionalBranch=True, hasArguments=True, needsToInvert=True,               shortVersion=TokenType.IF_TIMERANGE_S, longVersion=TokenType.IF_TIMERANGE_L),
    TokenType.RETURN_S:             TokenProperties(macro="SCHEDULE_CMD_RET_VAL_S",            cmdLength=0x02, hasArguments=True, isShort=True),
    TokenType.RETURN_L:             TokenProperties(macro="SCHEDULE_CMD_RET_VAL_L",            cmdLength=0x03, hasArguments=True),
    TokenType.RETURN_NONE:          TokenProperties(macro="SCHEDULE_CMD_RET_NONE",             cmdLength=0x01),
    TokenType.RETURN_EMPTY:         TokenProperties(macro="SCHEDULE_CMD_RET_EMPTY",            cmdLength=0x01),
    TokenType.IF_MISC_S:            TokenProperties(macro="SCHEDULE_CMD_CHECK_MISC_S",         cmdLength=0x03, isConditionalBranch=True, hasArguments=True, needsToInvert=True, isShort=True, shortVersion=TokenType.IF_MISC_S),
    TokenType.IF_SCENE_S:           TokenProperties(macro="SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S", cmdLength=0x04, isConditionalBranch=True, hasArguments=True, isShort=True, shortVersion=TokenType.IF_SCENE_S, longVersion=TokenType.IF_SCENE_L),
    TokenType.IF_SCENE_L:           TokenProperties(macro="SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L", cmdLength=0x05, isConditionalBranch=True, hasArguments=True,               shortVersion=TokenType.IF_SCENE_S, longVersion=TokenType.IF_SCENE_L),
    TokenType.IF_DAY_S:             TokenProperties(macro="SCHEDULE_CMD_CHECK_NOT_IN_DAY_S",   cmdLength=0x04, isConditionalBranch=True, hasArguments=True, isShort=True, shortVersion=TokenType.IF_DAY_S, longVersion=TokenType.IF_DAY_L),
    TokenType.IF_DAY_L:             TokenProperties(macro="SCHEDULE_CMD_CHECK_NOT_IN_DAY_L",   cmdLength=0x05, isConditionalBranch=True, hasArguments=True,               shortVersion=TokenType.IF_DAY_S, longVersion=TokenType.IF_DAY_L),
    TokenType.NOP:                  TokenProperties(macro="SCHEDULE_CMD_NOP",                  cmdLength=0x04, hasArguments=True),
    TokenType.RETURN_TIME:          TokenProperties(macro="SCHEDULE_CMD_RET_TIME",             cmdLength=0x06, hasArguments=True),
    TokenType.IF_BEFORETIME_S:      TokenProperties(macro="SCHEDULE_CMD_CHECK_BEFORE_TIME_S",  cmdLength=0x04, isConditionalBranch=True, hasArguments=True, needsToInvert=True, isShort=True, shortVersion=TokenType.IF_BEFORETIME_S, longVersion=TokenType.IF_BEFORETIME_L),
    TokenType.IF_BEFORETIME_L:      TokenProperties(macro="SCHEDULE_CMD_CHECK_BEFORE_TIME_L",  cmdLength=0x05, isConditionalBranch=True, hasArguments=True, needsToInvert=True,               shortVersion=TokenType.IF_BEFORETIME_S, longVersion=TokenType.IF_BEFORETIME_L),
    TokenType.IF_SINCETIME_S:       TokenProperties(macro="SCHEDULE_CMD_CHECK_BEFORE_TIME_S",  cmdLength=0x04, isConditionalBranch=True, hasArguments=True, isShort=True, shortVersion=TokenType.IF_SINCETIME_S, longVersion=TokenType.IF_SINCETIME_L),
    TokenType.IF_SINCETIME_L:       TokenProperties(macro="SCHEDULE_CMD_CHECK_BEFORE_TIME_L",  cmdLength=0x05, isConditionalBranch=True, hasArguments=True,               shortVersion=TokenType.IF_SINCETIME_S, longVersion=TokenType.IF_SINCETIME_L),
    TokenType.BRANCH_S:             TokenProperties(macro="SCHEDULE_CMD_BRANCH_S",             cmdLength=0x02, isUnconditionalBranch=True, hasArguments=True, isShort=True, shortVersion=TokenType.BRANCH_S, longVersion=TokenType.BRANCH_L),
    TokenType.BRANCH_L:             TokenProperties(macro="SCHEDULE_CMD_BRANCH_L",             cmdLength=0x03, isUnconditionalBranch=True, hasArguments=True,               shortVersion=TokenType.BRANCH_S, longVersion=TokenType.BRANCH_L),

    # Generics
    TokenType.IF_WEEKEVENTREG:      TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True, needsToInvert=True, shortVersion=TokenType.IF_WEEKEVENTREG_S, longVersion=TokenType.IF_WEEKEVENTREG_L),
    TokenType.IF_TIMERANGE:         TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True, needsToInvert=True, shortVersion=TokenType.IF_TIMERANGE_S, longVersion=TokenType.IF_TIMERANGE_L),
    TokenType.IF_MISC:              TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True, needsToInvert=True, shortVersion=TokenType.IF_MISC_S),
    TokenType.IF_SCENE:             TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True,                     shortVersion=TokenType.IF_SCENE_S, longVersion=TokenType.IF_SCENE_L),
    TokenType.IF_DAY:               TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True,                     shortVersion=TokenType.IF_DAY_S, longVersion=TokenType.IF_DAY_L),
    TokenType.IF_BEFORETIME:        TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True, needsToInvert=True, shortVersion=TokenType.IF_BEFORETIME_S, longVersion=TokenType.IF_BEFORETIME_L),
    TokenType.IF_SINCETIME:         TokenProperties(isConditionalBranch=True,   hasArguments=True, isGeneric=True,                     shortVersion=TokenType.IF_SINCETIME_S, longVersion=TokenType.IF_SINCETIME_L),
    TokenType.BRANCH:               TokenProperties(isUnconditionalBranch=True, hasArguments=True, isGeneric=True,                     shortVersion=TokenType.BRANCH_S, longVersion=TokenType.BRANCH_L),

    # Extra tokens
    TokenType.ELSE:                 TokenProperties(isExtraToken=True),
    TokenType.BRACE_OPEN:           TokenProperties(isExtraToken=True),
    TokenType.BRACE_CLOSE:          TokenProperties(isExtraToken=True),
    TokenType.ARGS:                 TokenProperties(isExtraToken=True),
    TokenType.NOT:                  TokenProperties(isExtraToken=True),
    TokenType.LABEL:                TokenProperties(isExtraToken=True),
}

tokenLiterals: dict[str, TokenType] = {x.value: x for x in TokenType}


regex_label = re.compile(r"(?P<label>\w+)\s*:")
regex_identifier = re.compile(r"(?P<identifier>\w+)")
regex_individualTokens = re.compile(r"(?P<individual>[\{\}])")

@dataclasses.dataclass
class Token:
    tokenType: TokenType
    tokenLiteral: str
    filename: str
    lineNumber: int
    columnNumber: int

    def getProperties(self) -> TokenProperties:
        return tokenPropertiesDict[self.tokenType]


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
            yield Token(TokenType.ARGS, parenContents, filename, lineNumberStart, columnNumberStart)

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
            yield Token(tokenType, literal, filename, lineNumber, columnNumber)

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
            print(f" ({self.args.tokenLiteral})", end="")
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
        tokenProperties = token.getProperties()

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

        elif not tokenProperties.isExtraToken or token.tokenType == TokenType.NOT:
            if currentExpr is not None and currentExpr.expr.getProperties().isConditionalBranch:
                if len(currentExpr.left) == 0:
                    eprint(f"Error: Invalid syntax at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: isExtraToken")
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
                    debugPrint(" makeTree: NOT: tokenAux is None")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)
                token = tokenAux
                tokenProperties = token.getProperties()
                if tokenProperties.isExtraToken:
                    eprint(f"Error: `not` operator followed invalid token at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                    debugPrint(" makeTree: NOT: isExtraToken")
                    debugPrint(f" i: {i}")
                    debugPrint(f" depth: {depth}")
                    debugPrint(f" token: {token}\n current expression: {currentExpr}")
                    debugPrint(f" foundElse: {foundElse}")
                    exit(1)

            currentExpr = Expression(token)
            currentExpr.negated = negate
            foundElse = False
            exprs.append(currentExpr)
            if not tokenProperties.hasArguments:
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
                debugPrint(" makeTree: LABEL, nextToken is None")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}\n current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)
            if nextToken.tokenType == TokenType.LABEL:
                eprint(f"Error: label followed by another label '{nextToken.tokenLiteral}' at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: LABEL, nextToken == LABEL")
                debugPrint(f" i: {i}")
                debugPrint(f" depth: {depth}")
                debugPrint(f" token: {token}\n current expression: {currentExpr}")
                debugPrint(f" foundElse: {foundElse}")
                exit(1)
            if nextToken.getProperties().isExtraToken:
                eprint(f"Error: label followed by not admitted token '{nextToken.tokenLiteral}' at {inputPath}:{token.lineNumber}:{token.columnNumber}")
                debugPrint(" makeTree: NOT isExtraToken")
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


def normalizeTreeImpl(tree: list[Expression], postLabel: Expression, depth: int, autoLabelName: str) -> tuple[list[Expression], bool]:
    newTree: list[Expression] = []
    usedLabel = False

    currentPostLabel: Expression = postLabel

    i = 0
    while i < len(tree):
        expr = tree[i]

        newTree.append(expr)

        usedCurrentPostLabel = False
        shouldAddPostLabel = True
        if i + 1 < len(tree):
            if tree[i + 1].expr.tokenType == TokenType.LABEL:
                # Re-use label if there's already one
                currentPostLabel = tree[i + 1]
                shouldAddPostLabel = False
            else:
                # dot (.) is used to ensure no name crashes with user-declared labels
                currentPostLabel = Expression(Token(TokenType.LABEL, f"{autoLabelName}.{depth}_{i}", "", 0, 0))

        auxUsed = False
        if expr.expr.getProperties().isConditionalBranch:
            if len(expr.left) == 0:
                branchExpr = Expression(Token(TokenType.BRANCH, f"branch", "", 0, 0), currentPostLabel.expr)
                expr.left.append(branchExpr)
                if currentPostLabel == postLabel:
                    usedLabel = True
                else:
                    usedCurrentPostLabel = True
            else:
                expr.left, auxUsed = normalizeTreeImpl(expr.left, currentPostLabel, depth+1, f"{autoLabelName}_left")
                if currentPostLabel == postLabel:
                    usedLabel = usedLabel or auxUsed

            if len(expr.right) == 0:
                branchExpr = Expression(Token(TokenType.BRANCH, f"branch", "", 0, 0), currentPostLabel.expr)
                expr.right.append(branchExpr)
                if currentPostLabel == postLabel:
                    usedLabel = True
                else:
                    usedCurrentPostLabel = True
            else:
                expr.right, auxUsed = normalizeTreeImpl(expr.right, currentPostLabel, depth+1, f"{autoLabelName}_right")
                if currentPostLabel == postLabel:
                    usedLabel = usedLabel or auxUsed

        if currentPostLabel != postLabel and (usedCurrentPostLabel or auxUsed) and shouldAddPostLabel:
            newTree.append(currentPostLabel)

        currentPostLabel = postLabel

        i += 1

    return newTree, usedLabel

def normalizeTree(tree: list[Expression]) -> list[Expression]:
    postLabel = Expression(Token(TokenType.LABEL, ".autolabel.placeholder", "", -1, -1))

    newTree, usedLabel = normalizeTreeImpl(tree, postLabel, 0, "_autolabel")

    if usedLabel:
        eprint("Warning: branching outside the script")
        newTree.append(postLabel)
    return newTree


@dataclasses.dataclass
class LabeledExpression:
    index: int

    token: Token
    args: Token|None

    labelName: str

    canChange: bool

    # The branch target can be either a str (label) or None (no branch target)
    branchTarget: str|None = None

    def __str__(self) -> str:
        ret = f"/* {self.index:03} */ {self.labelName:<24}: {self.token.tokenLiteral}"
        if self.canChange:
            ret += "*"
        if self.args is not None:
            ret += f" ({self.args.tokenLiteral})"
        if self.branchTarget is not None:
            ret += f" -> {self.branchTarget}"
        return ret

def convertTreeIntoLabeledList(tree: list[Expression], index: int = 0) -> tuple[list[LabeledExpression], int]:
    result: list[LabeledExpression] = []
    # To track labels
    labelName: str|None = None

    for expr in tree:
        token = expr.expr
        if token.tokenType == TokenType.LABEL:
            # Keep the labelname but ignore the label itself
            labelName = token.tokenLiteral
            continue

        tokenProperties = token.getProperties()

        subResults = []
        left = expr.left
        right = expr.right
        if tokenProperties.needsToInvert:
            left, right = right, left
        if expr.negated:
            left, right = right, left

        currentIndex = index
        index += 1

        sub, index = convertTreeIntoLabeledList(left, index)

        subResults += sub

        targetLabel = None

        if len(right) == 1 and right[0].expr.getProperties().isUnconditionalBranch:
            # If an `if_` only has 1 expression and it is a branch then incorporate it as part of the `if_`,
            # avoiding redundant branches
            sub = []
            branchExpr = right[0]
            if branchExpr.args is None:
                eprint(f"Error: branch command without arguments? at {branchExpr.expr.filename}:{branchExpr.expr.lineNumber}:{branchExpr.expr.columnNumber}")
                debugPrint(f" convertTreeIntoLabeledList")
                exit(1)
            targetLabel = branchExpr.args.tokenLiteral.strip()
        else:
            sub, index = convertTreeIntoLabeledList(right, index)
            subResults += sub
            if len(sub) != 0:
                targetLabel = sub[0].labelName

        if labelName is None:
            labelName = f".index.{currentIndex}"

        canChange = False
        if tokenProperties.isGeneric:
            canChange = True
            newTokenType = tokenProperties.shortVersion
            assert newTokenType is not None, token
            token = Token(newTokenType, newTokenType.value, token.filename, token.lineNumber, token.columnNumber)
            tokenProperties = token.getProperties()

        if tokenProperties.isUnconditionalBranch:
            assert expr.args is not None, expr
            targetLabel = expr.args.tokenLiteral

        linearExpr = LabeledExpression(currentIndex, token, expr.args, labelName, canChange)
        labelName = None

        if tokenProperties.isAnyBranch:
            linearExpr.branchTarget = targetLabel

        result += [linearExpr] + subResults

    return result, index


def removeGenerics(labeledList: list[LabeledExpression]) -> tuple[list[LabeledExpression], bool]:
    modifiedAnything = False

    offset = 0
    for labeledExpr in labeledList:
        tokenProperties = labeledExpr.token.getProperties()

        assert tokenProperties.cmdLength is not None, labeledExpr
        nextOffset = offset + tokenProperties.cmdLength

        if labeledExpr.canChange:
            if tokenProperties.isAnyBranch:
                if tokenProperties.isShort:
                    # There's no point on trying to change a long branch

                    # find the target expression
                    targetIndex = -1
                    targetExpression = None
                    subOffset = 0
                    for j, auxExpr in enumerate(labeledList):
                        if labeledExpr.branchTarget == auxExpr.labelName:
                            targetIndex = j
                            targetExpression = auxExpr
                            break
                        targetProperties = auxExpr.token.getProperties()
                        assert targetProperties.cmdLength is not None, auxExpr
                        subOffset += targetProperties.cmdLength

                    if targetIndex < 0 or targetExpression is None:
                        eprint(f"Error: Not able to find target '{labeledExpr.branchTarget}' for expression '{labeledExpr.token.tokenLiteral}' at {labeledExpr.token.filename}:{labeledExpr.token.lineNumber}:{labeledExpr.token.columnNumber}")
                        debugPrint(f" removeGenerics")
                        exit(1)

                    diff = subOffset - nextOffset
                    if diff >= 0x7F or diff <= -0x80:
                        longTokenType = tokenProperties.longVersion
                        if longTokenType is None:
                            eprint(f"Error: Command '{labeledExpr.token.tokenLiteral}' will require a branch way too big for a short branch, but there's no long equivalent. At {labeledExpr.token.filename}:{labeledExpr.token.lineNumber}:{labeledExpr.token.columnNumber}")
                            debugPrint(f" removeGenerics")
                            exit(1)
                        labeledExpr.token = Token(longTokenType, longTokenType.value, labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)
                        tokenProperties = labeledExpr.token.getProperties()
                        modifiedAnything = True

        assert tokenProperties.cmdLength is not None, labeledExpr
        offset += tokenProperties.cmdLength

    return labeledList, modifiedAnything


def getTargetOffset(labeledExpr: LabeledExpression, labeledList: list[LabeledExpression], offsetList: list[int]) -> int:
    if labeledExpr.branchTarget is None:
        eprint(f"Internal Error: Command '{labeledExpr.token.tokenLiteral}' requested a target offset but it doesn't have a label. At {labeledExpr.token.filename}:{labeledExpr.token.lineNumber}:{labeledExpr.token.columnNumber}")
        debugPrint(f" getTargetOffset")
        exit(1)

    for i, targetExpr in enumerate(labeledList):
        if labeledExpr.branchTarget == targetExpr.labelName:
            return offsetList[i]

    eprint(f"Internal Error: Command '{labeledExpr.token.tokenLiteral}' requested label '{labeledExpr.branchTarget}', but it was not found. At {labeledExpr.token.filename}:{labeledExpr.token.lineNumber}:{labeledExpr.token.columnNumber}")
    debugPrint(f" getTargetOffset")
    exit(1)

def emitLabeledListMacros(labeledList: list[LabeledExpression], debuggingLevel: int) -> str:
    result = ""

    # Precompute the offsets of each expression
    offsetList: list[int] = []
    offset = 0
    for labeledExpr in labeledList:
        offsetList.append(offset)
        cmdLength = labeledExpr.token.getProperties().cmdLength
        assert cmdLength is not None, labeledExpr
        offset += cmdLength
    # To avoid reading outside of the list
    offsetList.append(offset)

    # Use the same amount of 0 pads for every entry
    offsetWidth = len(f"{offsetList[-2]:X}")

    for i, labeledExpr in enumerate(labeledList):
        currentOffset = offsetList[i]
        nextOffset = offsetList[i+1]

        tokenProperties = labeledExpr.token.getProperties()

        assert tokenProperties.macro is not None, labeledExpr
        currentMacro = f"    /* 0x{currentOffset:0{offsetWidth}X} */ {tokenProperties.macro}("

        if tokenProperties.isUnconditionalBranch:
            targetOffset = getTargetOffset(labeledExpr, labeledList, offsetList)
            currentMacro += f"0x{targetOffset:0{offsetWidth}X} - 0x{nextOffset:0{offsetWidth}X}"
        else:
            if labeledExpr.args is not None:
                currentMacro += f"{labeledExpr.args.tokenLiteral}"
            if tokenProperties.isConditionalBranch:
                targetOffset = getTargetOffset(labeledExpr, labeledList, offsetList)
                currentMacro += f", 0x{targetOffset:0{offsetWidth}X} - 0x{nextOffset:0{offsetWidth}X}"
        currentMacro += "),"

        if debuggingLevel >= 1:
            currentMacro += f" /* {labeledExpr.token.filename}:{labeledExpr.token.lineNumber}:{labeledExpr.token.columnNumber} */"

        currentMacro += "\n"

        result += currentMacro

    return result


def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("input", help="Schedule script path", type=Path)
    parser.add_argument("-o", "--output", help="Output path. Will print to stdout if omitted", type=Path)
    parser.add_argument("-g", type=int, nargs="?", const=1, default=0, dest="debuggingLevel", metavar="level", help="Emit debugging information on the generated macros. Level 0 means no debugging information. Passing no level at all implies level 1. Defaults to level 0")

    debuggingParser = parser.add_argument_group("Compiler debugging options")
    debuggingParser.add_argument("-p", "--print-tree", help="Prints the processed tree to stdout", action="store_true")

    args = parser.parse_args()

    inputPath: Path = args.input
    outputPath: Path|None = args.output

    debuggingLevel: int = args.debuggingLevel

    printTree: bool = args.print_tree

    if not inputPath.exists():
        eprint(f"Error: Input file '{inputPath}' not found")
        exit(1)

    inputContents = inputPath.read_text("UTF-8")

    preprocessed = preprocess(inputContents, str(inputPath))

    tokens = TokenIterator(tokenize(preprocessed, str(inputPath)))
    tree = makeTree(tokens, str(inputPath))
    assert tokens.remainingTokens() == 0
    tree = normalizeTree(tree)
    if printTree:
        for expr in tree:
            expr.print()

    labeledList, _ = convertTreeIntoLabeledList(tree)
    # for labeled in labeledList:
    #     print(labeled)
    # print()

    genericsIterationCount = 0
    keepGoing = True
    while keepGoing:
        labeledList, keepGoing = removeGenerics(labeledList)
        genericsIterationCount += 1
    # for labeled in labeledList:
    #     print(labeled)
    # print()
    # print(f"{genericsIterationCount=}")
    # print()

    output = emitLabeledListMacros(labeledList, debuggingLevel)

    if outputPath is None:
        print(output)
    else:
        outputPath.parent.mkdir(parents=True, exist_ok=True)
        outputPath.write_text(output)

if __name__ == "__main__":
    main()
