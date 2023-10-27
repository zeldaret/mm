#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

# TODO: Check for repeated labels
# TODO: think on a catchy name for the schedule language and the compiler

from __future__ import annotations

import argparse
import dataclasses
import enum
from pathlib import Path
import re
from typing import NoReturn
import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

DEBUG = False

def debugPrint(*args, **kwargs):
    if not DEBUG:
        return
    eprint(*args, **kwargs)

def fatalError(message: str, filename: str, lineNumber: int, columnNumber: int, **kwargs) -> NoReturn:
    # Print the filename/linenumber in a format that some IDEs can follow by ctrl-click on them
    eprint(f"Error: {message}. At {filename}:{lineNumber}:{columnNumber}")

    if DEBUG:
        # Get the info from the caller
        frame = sys._getframe().f_back
        if frame is not None:
            funcName = frame.f_code.co_name
            debugPrint(f" Halted from: {funcName} at {frame.f_code.co_filename}:{frame.f_lineno}")

        for key, value in kwargs.items():
            debugPrint(f"  {key}: {value}")

    # TODO: Add fun error messages

    exit(1)

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

    # The literal read from the input. Some token types don't have a fixed literal, like LABEL or ARGS
    tokenLiteral: str

    # Track the token position on the original file, for better error messages
    filename: str
    lineNumber: int
    columnNumber: int

    def getProperties(self) -> TokenProperties:
        return tokenPropertiesDict[self.tokenType]

    def newFromTokenType(self, newType: TokenType) -> Token:
        return Token(newType, newType.value, self.filename, self.lineNumber, self.columnNumber)

    def newFromTokenTypePreserveLiteral(self, newType: TokenType) -> Token:
        return Token(newType, self.tokenLiteral, self.filename, self.lineNumber, self.columnNumber)

    def __str__(self) -> str:
        ret = f"{self.filename}:{self.lineNumber}:{self.columnNumber}\n"
        ret += f"  {self.tokenType.name}"
        if self.tokenLiteral != self.tokenType.value:
            ret += f" '{self.tokenLiteral}'"
        return ret


# Allows to know which token will be the next one, even with recursive functions
class TokenIterator:
    def __init__(self, tokens: list[Token]):
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

    def reset(self) -> None:
        self.index = 0


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

# Takes a preprocessed input and converts them into a list of tokens
def tokenize(contents: str, filename: str) -> TokenIterator:
    tokens: list[Token] = []
    lineNumber = 1
    columnNumber = 1

    contentsLength = len(contents)
    i = 0
    while i < contentsLength:
        char = contents[i]

        if char == "(":
            # Command arguments are handled in a special way,
            # all the arguments are grouped together as a single token
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
                fatalError("Unterminated parenthesis", filename, lineNumber, columnNumber, i=i, char=char)
            parenContents = contents[i+1:subIndex]
            tokens.append(Token(TokenType.ARGS, parenContents, filename, lineNumberStart, columnNumberStart))

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
                fatalError(f"Unrecognized token found", filename, lineNumber, columnNumber, i=i, char=char)

            if tokenType is None:
                fatalError(f"Unrecognized token '{literal}' found", filename, lineNumber, columnNumber, i=i, char=char)
            tokens.append(Token(tokenType, literal, filename, lineNumber, columnNumber))

            # Calculate how long the found token is
            spanStart, spanEnd = reMatch.span()
            matchLen = spanEnd - spanStart
            columnNumber += matchLen
            i += matchLen
            continue

        i += 1
    return TokenIterator(tokens)

# Tree
@dataclasses.dataclass
class Expression:
    token: Token
    args: Token|None = None

    # The body of an `if` check
    left: list[Expression] = dataclasses.field(default_factory=list)
    # The body of an `else`
    right: list[Expression] = dataclasses.field(default_factory=list)

    # This expression follows a `not` operator
    negated: bool = False

    def toStr(self, depth=0) -> str:
        spaces = "    " * depth
        ret = f"{spaces}"
        if self.negated:
            ret += f"not "
        ret += f"{self.token.tokenLiteral}"
        if self.token.tokenType == TokenType.LABEL:
            ret += f":"
        if self.args is not None:
            ret += f" ({self.args.tokenLiteral})"
        if len(self.left) == 0:
            ret += f"\n"
        else:
            ret += f" {{\n"
            for expr in self.left:
                ret += expr.toStr(depth+1)
            if len(self.right) > 0:
                ret += f"{spaces}}} else {{\n"
                for expr in self.right:
                    ret += expr.toStr(depth+1)
            ret += f"{spaces}}}\n"
        return ret

    def __str__(self) -> str:
        return self.toStr()


# Parses the tokens into a basic AST
def makeTree(tokens: TokenIterator, inputPath: str, *, depth: int=0) -> list[Expression]:
    exprs: list[Expression] = []

    currentExpr: Expression|None = None
    foundElse = False

    i = 0
    while (token := tokens.get()) is not None:
        tokenProperties = token.getProperties()

        if token.tokenType == TokenType.ARGS:
            if currentExpr is None or currentExpr.args is not None:
                fatalError(f"Invalid syntax, args following invalid token", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
            currentExpr.args = token

        elif not tokenProperties.isExtraToken or token.tokenType == TokenType.NOT:
            if currentExpr is not None and currentExpr.token.getProperties().isAnyBranch:
                if len(currentExpr.left) == 0:
                    fatalError(f"invalid syntax", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)

            negate = False
            if token.tokenType == TokenType.NOT:
                negate = True

                # Get the token that is being negated
                tokenAux = tokens.get()
                if tokenAux is None:
                    fatalError(f"`not` operator followed by nothing", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
                token = tokenAux
                tokenProperties = token.getProperties()
                if tokenProperties.isExtraToken:
                    fatalError(f"`not` operator followed by invalid `{token.tokenLiteral}` token", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)

            currentExpr = Expression(token)
            currentExpr.negated = negate
            foundElse = False
            exprs.append(currentExpr)
            if not tokenProperties.hasArguments:
                currentExpr = None

        elif token.tokenType == TokenType.ELSE:
            if currentExpr is None or currentExpr.args is None or foundElse:
                fatalError(f"Invalid syntax", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
            foundElse = True

            # Peek next token
            nextToken = tokens.get()
            if nextToken is None:
                fatalError(f"Invalid syntax: missing expression after `{token.tokenLiteral}`", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)

            tokens.unget()
            if nextToken.tokenType != TokenType.BRACE_OPEN:
                # `else` with no braces, try to parse it
                if len(currentExpr.right) != 0:
                    fatalError(f"Invalid syntax", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
                # Instead of storing the `else` as its own token, just store it as part of the corresponding `if` check
                currentExpr.right = makeTree(tokens, inputPath, depth=depth+1)
                return exprs

        elif token.tokenType == TokenType.BRACE_OPEN:
            # The body of an `if` or an `else`

            if currentExpr is None or currentExpr.args is None:
                fatalError(f"Invalid syntax: Opening braces doesn't follow a valid expression", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)

            if foundElse:
                if len(currentExpr.right) != 0:
                    fatalError(f"Invalid syntax: Double body for an `else`", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
                # Instead of storing the `else` as its own token, just store it as part of the corresponding `if` check
                currentExpr.right = makeTree(tokens, inputPath, depth=depth+1)
            else:
                if len(currentExpr.left) != 0:
                    fatalError(f"Invalid syntax: Double body for an `if_`", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
                currentExpr.left = makeTree(tokens, inputPath, depth=depth+1)

        elif token.tokenType == TokenType.BRACE_CLOSE:
            if len(exprs) == 0:
                eprint(f"Warning: Braces with empty body at {inputPath}:{token.lineNumber}:{token.columnNumber}")
            return exprs

        elif token.tokenType == TokenType.LABEL:
            # We need to check the token following a label is valid
            nextToken = tokens.get()
            tokens.unget()
            if nextToken is None:
                fatalError(f"Labels should be followed by another valid expression", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
            if nextToken.tokenType == TokenType.LABEL:
                fatalError(f"Labels can't be followed by another label", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
            if nextToken.getProperties().isExtraToken:
                fatalError(f"Found label followed by not admitted token `{nextToken.tokenLiteral}`", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
            currentExpr = Expression(token)
            foundElse = False
            exprs.append(currentExpr)

        else:
            fatalError(f"This code should be unreachable.\n Tell me dear user, is this a vanilla bug on the compiler?\n Or are you trying to implement new features and you forgot to add a check somewhere?\n Remember to enable the debug prints, they may help you either way.\n ", inputPath, token.lineNumber, token.columnNumber, i=i, depth=depth, token=token, currentExpr=currentExpr, foundElse=foundElse)
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
            if tree[i + 1].token.tokenType == TokenType.LABEL:
                # Re-use label if there's already one
                currentPostLabel = tree[i + 1]
                shouldAddPostLabel = False
            else:
                # dot (.) is used to ensure no name crashes with user-declared labels
                labelToken = expr.token.newFromTokenType(TokenType.LABEL)
                labelToken.tokenLiteral = f".{autoLabelName}.{depth}_{i}"
                currentPostLabel = Expression(labelToken)

        auxUsed = False
        if expr.token.getProperties().isConditionalBranch:
            if len(expr.left) == 0:
                branchExpr = Expression(expr.token.newFromTokenType(TokenType.BRANCH), currentPostLabel.token)
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
                branchExpr = Expression(expr.token.newFromTokenType(TokenType.BRANCH), currentPostLabel.token)
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

# Searches for `if_` and `else`s with empty bodies and inserts in them an unconditional branch to avoid compiler-induced fallthroughs
def normalizeTree(tree: list[Expression]) -> list[Expression]:
    postLabel = Expression(Token(TokenType.LABEL, ".autolabel.placeholder", "", -1, -1))

    newTree, usedLabel = normalizeTreeImpl(tree, postLabel, 0, "_autolabel")

    if usedLabel:
        eprint("Warning: branching outside the script")
        newTree.append(postLabel)
    return newTree


# For linearizing a tree
@dataclasses.dataclass
class LabeledExpression:
    # Index relative to the parent list
    index: int

    token: Token
    args: Token|None

    # Label to jump into this command
    labelName: str

    # True if this expression is allowed to change between `_s` and `_l` versions of the same command, like if the original script used a suffix-less version of the command
    # False if the original script used a command with a `_s`/`_l` suffix
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

# Takes a tree and linearizes it, preserving the control flow by using labels (user-defined or autogenerated)
def convertTreeIntoLabeledList(tree: list[Expression], index: int = 0) -> tuple[list[LabeledExpression], int]:
    result: list[LabeledExpression] = []
    # To track the current label
    labelName: str|None = None

    for expr in tree:
        token = expr.token
        if token.tokenType == TokenType.LABEL:
            # Keep the labelname but ignore the label itself
            labelName = token.tokenLiteral
            continue

        tokenProperties = token.getProperties()

        left = expr.left
        right = expr.right

        # Some commands need to invert theirs `if_`/`else` bodies to match the corresponding command
        if tokenProperties.needsToInvert:
            left, right = right, left

        # Invert the bodies if the expression was negated
        if expr.negated:
            left, right = right, left

        currentIndex = index
        index += 1

        # Linealize the left body
        subResults, index = convertTreeIntoLabeledList(left, index)

        # Expressions always jump into the right body if their check evaluates to True
        targetLabel = None
        if len(right) == 1 and right[0].token.getProperties().isUnconditionalBranch:
            # If an `if_` only has 1 expression and it is a branch then incorporate it as part of the `if_`,
            # avoiding redundant branches
            branchExpr = right[0]
            if branchExpr.args is None:
                fatalError(f"Branch command without arguments?", branchExpr.token.filename, branchExpr.token.lineNumber, branchExpr.token.columnNumber)
            targetLabel = branchExpr.args.tokenLiteral.strip()
        else:
            sub, index = convertTreeIntoLabeledList(right, index)
            subResults += sub
            if len(sub) != 0:
                # Get the label name of the first expression
                targetLabel = sub[0].labelName

        # If there's no user-defined label, then autogenerate one. Use dots to avoid name crashes with user-defined ones
        if labelName is None:
            labelName = f".index.{currentIndex}"

        # Process generics into non-generic short version for now.
        # A different pass will check if the short commands produced from generics will require a long version instead
        canChange = False
        if tokenProperties.isGeneric:
            canChange = True
            newTokenType = tokenProperties.shortVersion
            assert newTokenType is not None, token
            token = token.newFromTokenTypePreserveLiteral(newTokenType)
            tokenProperties = token.getProperties()

        # Take the target label of a `branch` command
        if tokenProperties.isUnconditionalBranch:
            if expr.args is None:
                fatalError(f"Branch command `{expr.token.tokenLiteral}` without arguments?", expr.token.filename, expr.token.lineNumber, expr.token.columnNumber)
            targetLabel = expr.args.tokenLiteral

        linearExpr = LabeledExpression(currentIndex, token, expr.args, labelName, canChange)

        # Reset the label, so we don't accidentally reuse it
        labelName = None

        if tokenProperties.isAnyBranch:
            linearExpr.branchTarget = targetLabel

        result += [linearExpr] + subResults

    return result, index


# Checks for every short command that was produced from a generic and calculate if the branch offset will
# fit on the short command, if it doesn't then change the command into a long version.
#
# The algorithm is basic and linear, so if an already-processed expression's branch offset will no longer fit
# because of latter processed expressions changed to long commands (which uses more bytes), then those won't
# be re-updated.
# To work-around this, this function returns a boolean on the second element of the returned tuple indicating
# if this pass modified any expression, so this function needs to be called again until that boolean is False
#
# Returns a 2-tuple with a list of the expressions and a boolean indicating if any expression was modified.
# Please note this function also modifies the parameter
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
                        fatalError(f"Not able to find target '{labeledExpr.branchTarget}' for expression '{labeledExpr.token.tokenLiteral}'", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)

                    diff = subOffset - nextOffset
                    if diff >= 0x7F or diff <= -0x80:
                        longTokenType = tokenProperties.longVersion
                        if longTokenType is None:
                            fatalError(f"Command '{labeledExpr.token.tokenLiteral}' will require a branch way too big for a short branch, but there's no long equivalent", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)
                        labeledExpr.token = labeledExpr.token.newFromTokenTypePreserveLiteral(longTokenType)
                        tokenProperties = labeledExpr.token.getProperties()
                        modifiedAnything = True

        assert tokenProperties.cmdLength is not None, labeledExpr
        offset += tokenProperties.cmdLength

    return labeledList, modifiedAnything


def getTargetOffset(labeledExpr: LabeledExpression, labeledList: list[LabeledExpression], offsetList: list[int]) -> int:
    if labeledExpr.branchTarget is None:
        fatalError(f"Command '{labeledExpr.token.tokenLiteral}' requested a target offset but it doesn't have a label", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)

    for i, targetExpr in enumerate(labeledList):
        if labeledExpr.branchTarget == targetExpr.labelName:
            return offsetList[i]

    fatalError(f"Command '{labeledExpr.token.tokenLiteral}' requested label '{labeledExpr.branchTarget}', but it was not found", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)

# Generate a string containing all the macros based on the labeled expression
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

    # Use the same amount of pads for every entry
    offsetWidth = len(f"{offsetList[-2]:X}")

    for i, labeledExpr in enumerate(labeledList):
        currentOffset = offsetList[i]
        nextOffset = offsetList[i+1]

        tokenProperties = labeledExpr.token.getProperties()

        assert tokenProperties.macro is not None, labeledExpr
        currentMacro = f"    /* 0x{currentOffset:0{offsetWidth}X} */ {tokenProperties.macro}("

        if tokenProperties.isUnconditionalBranch:
            targetOffset = getTargetOffset(labeledExpr, labeledList, offsetList)
            diff = targetOffset - nextOffset
            if tokenProperties.isShort:
                if diff not in range(-0x80, 0x7F):
                    fatalError(f"Trying to use a short command, but the branch offset is too big to fit on a single byte ({diff})", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)
            else:
                if diff not in range(-0x8000, 0x7FFF):
                    fatalError(f"Trying to use a long command, but the branch offset is too big to fit on a single byte ({diff})", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)
            currentMacro += f"0x{targetOffset:0{offsetWidth}X} - 0x{nextOffset:0{offsetWidth}X}"
        else:
            if labeledExpr.args is not None:
                currentMacro += f"{labeledExpr.args.tokenLiteral}"
            if tokenProperties.isConditionalBranch:
                targetOffset = getTargetOffset(labeledExpr, labeledList, offsetList)
                diff = targetOffset - nextOffset
                if tokenProperties.isShort:
                    if diff not in range(-0x80, 0x7F):
                        fatalError(f"Trying to use a short command, but the branch offset is too big to fit on a single byte ({diff})", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)
                else:
                    if diff not in range(-0x8000, 0x7FFF):
                        fatalError(f"Trying to use a long command, but the branch offset is too big to fit on a single byte ({diff})", labeledExpr.token.filename, labeledExpr.token.lineNumber, labeledExpr.token.columnNumber)
                currentMacro += f", 0x{targetOffset:0{offsetWidth}X} - 0x{nextOffset:0{offsetWidth}X}"
        currentMacro += "),"

        if debuggingLevel >= 1:
            currentMacro += f" /* {labeledExpr.token.filename}:{labeledExpr.token.lineNumber}:{labeledExpr.token.columnNumber} */"

        currentMacro += "\n"

        result += currentMacro

    return result


def main():
    parser = argparse.ArgumentParser(description="Compiler for the high level schedule language")
    parser.add_argument("input", help="Schedule script path", type=Path)
    parser.add_argument("-o", "--output", help="Output path. Will print to stdout if omitted", type=Path)
    parser.add_argument("-g", type=int, nargs="?", const=1, default=0, dest="debuggingLevel", metavar="level", help="Emit debugging information on the generated macros. Level 0 means no debugging information. Passing no level at all implies level 1. Defaults to level 0")

    debuggingParser = parser.add_argument_group("Compiler debugging options")
    debuggingParser.add_argument("-d", "--debug-prints", help="Enables debug prints for fatal errors", action="store_true")
    debuggingParser.add_argument("--print-tokens", help="Prints the processed tokens to stdout", action="store_true")
    debuggingParser.add_argument("--print-raw-tree", help="Prints the raw tree to stdout", action="store_true")
    debuggingParser.add_argument("--print-tree", help="Prints the processed and normalized tree to stdout", action="store_true")
    debuggingParser.add_argument("--print-labeleds", help="Prints the linearized labeled expressions to stdout", action="store_true")
    debuggingParser.add_argument("--print-labeleds-post", help="Prints the linearized labeled expressions after processing the generics to stdout", action="store_true")

    args = parser.parse_args()

    inputPath: Path = args.input
    outputPath: Path|None = args.output

    debuggingLevel: int = args.debuggingLevel

    global DEBUG
    DEBUG = args.debug_prints

    printTokens: bool = args.print_tokens
    printRawTree: bool = args.print_raw_tree
    printTree: bool = args.print_tree
    printLabeleds: bool = args.print_labeleds
    printLabeledsPost: bool = args.print_labeleds_post

    if not inputPath.exists():
        eprint(f"Error: Input file '{inputPath}' not found")
        exit(1)

    inputContents = inputPath.read_text("UTF-8")

    preprocessed = preprocess(inputContents, str(inputPath))

    tokens = tokenize(preprocessed, str(inputPath))
    if printTokens:
        for token in tokens.tokens:
            print(token)

    tree = makeTree(tokens, str(inputPath))
    if printRawTree:
        for expr in tree:
            print(expr)

    assert tokens.remainingTokens() == 0, tokens.remainingTokens()

    tree = normalizeTree(tree)
    if printTree:
        for expr in tree:
            print(expr)

    labeledList, _ = convertTreeIntoLabeledList(tree)
    if printLabeleds:
        for labeled in labeledList:
            print(labeled)
        print()

    keepGoing = True
    while keepGoing:
        labeledList, keepGoing = removeGenerics(labeledList)
    if printLabeledsPost:
        for labeled in labeledList:
            print(labeled)
        print()

    output = emitLabeledListMacros(labeledList, debuggingLevel)

    if outputPath is None:
        print(output)
    else:
        outputPath.parent.mkdir(parents=True, exist_ok=True)
        outputPath.write_text(output)

if __name__ == "__main__":
    main()
