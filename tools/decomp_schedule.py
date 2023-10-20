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

entryRegex = re.compile(r"/\* (?P<offset>0x..) \*/ (?P<macro>\w+)\((?P<args>.*)\),")

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


@dataclasses.dataclass
class CommandInfo:
    isBranch: bool = False
    needsToInvert: bool = False

cmdInfos: dict[str, CommandInfo] = {
    "SCHEDULE_CMD_CHECK_FLAG_S":            CommandInfo(isBranch=True, needsToInvert=True),
    "SCHEDULE_CMD_CHECK_FLAG_L":            CommandInfo(isBranch=True, needsToInvert=True),
    "SCHEDULE_CMD_CHECK_TIME_RANGE_S":      CommandInfo(isBranch=True, needsToInvert=True),
    "SCHEDULE_CMD_CHECK_TIME_RANGE_L":      CommandInfo(isBranch=True, needsToInvert=True),
    "SCHEDULE_CMD_RET_VAL_S":               CommandInfo(),
    "SCHEDULE_CMD_RET_VAL_L":               CommandInfo(),
    "SCHEDULE_CMD_RET_NONE":                CommandInfo(),
    "SCHEDULE_CMD_RET_EMPTY":               CommandInfo(),
    "SCHEDULE_CMD_CHECK_MISC_S":            CommandInfo(isBranch=True),
    "SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S":    CommandInfo(isBranch=True),
    "SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L":    CommandInfo(isBranch=True),
    "SCHEDULE_CMD_CHECK_NOT_IN_DAY_S":      CommandInfo(isBranch=True),
    "SCHEDULE_CMD_CHECK_NOT_IN_DAY_L":      CommandInfo(isBranch=True),
    "SCHEDULE_CMD_NOP":                     CommandInfo(),
    "SCHEDULE_CMD_RET_TIME":                CommandInfo(),
    "SCHEDULE_CMD_CHECK_BEFORE_TIME_S":     CommandInfo(isBranch=True),
    "SCHEDULE_CMD_CHECK_BEFORE_TIME_L":     CommandInfo(isBranch=True),
    "SCHEDULE_CMD_BRANCH_S":                CommandInfo(isBranch=True),
    "SCHEDULE_CMD_BRANCH_L":                CommandInfo(isBranch=True),
}


def toCommandList(inputContents: str) -> list[tuple[int, str, str]]:
    braceIndex = inputContents.find("{")
    if braceIndex != -1:
        inputContents = inputContents[braceIndex+2:]
    braceIndex = inputContents.find("}")
    if braceIndex != -1:
        inputContents = inputContents[:braceIndex-1]

    entries: list[tuple[int, str, str]] = []
    for entry in inputContents.split("\n"):
        entry = entry.strip()
        # print(entry)
        entryMatch = entryRegex.search(entry)
        if entryMatch is None:
            eprint("wat: ", entry)
            exit(1)
        offset = int(entryMatch["offset"], 0)
        macro = str(entryMatch["macro"])
        entryArgs = str(entryMatch["args"])
        # print(f"{offset:02X}", macro, entryArgs)
        subEntry = (offset, macro, entryArgs)
        entries.append(subEntry)
    return entries


@dataclasses.dataclass
class Expression:
    expr: str
    args: str|None = None

    left: list[Expression] = dataclasses.field(default_factory=list)
    right: list[Expression] = dataclasses.field(default_factory=list)

    def print(self, depth=0):
        spaces = "    " * depth
        print(f"{spaces}{self.expr}", end="")
        if self.args is not None:
            print(f" ({self.args})", end="")
        if len(self.left) == 0:
            print()
        else:
            print(" {")
            for expr in self.left:
                expr.print(depth+1)
            print(f"{spaces}}} else {{")
            for expr in self.right:
                expr.print(depth+1)
            print(f"{spaces}}}")


tokenMap: dict = {
    'SCHEDULE_CMD_CHECK_FLAG_S'         : "if_week_event_reg_s",
    'SCHEDULE_CMD_CHECK_FLAG_L'         : "if_week_event_reg_l",
    'SCHEDULE_CMD_CHECK_TIME_RANGE_S'   : "if_time_range_s",
    'SCHEDULE_CMD_CHECK_TIME_RANGE_L'   : "if_time_range_l",
    'SCHEDULE_CMD_RET_VAL_S'            : "return_s",
    'SCHEDULE_CMD_RET_VAL_L'            : "return_l",
    'SCHEDULE_CMD_RET_NONE'             : "return_none",
    'SCHEDULE_CMD_RET_EMPTY'            : "return_empty",
    'SCHEDULE_CMD_CHECK_MISC_S'         : "if_misc_s",
    'SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S' : "if_scene_s",
    'SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L' : "if_scene_l",
    'SCHEDULE_CMD_CHECK_NOT_IN_DAY_S'   : "if_day_s",
    'SCHEDULE_CMD_CHECK_NOT_IN_DAY_L'   : "if_day_l",
    'SCHEDULE_CMD_NOP'                  : "nop",
    'SCHEDULE_CMD_RET_TIME'             : "return_time",
    'SCHEDULE_CMD_CHECK_BEFORE_TIME_S'  : "if_before_time_s",
    'SCHEDULE_CMD_CHECK_BEFORE_TIME_L'  : "if_before_time_l",
    'SCHEDULE_CMD_BRANCH_S'             : "branch_s",
    'SCHEDULE_CMD_BRANCH_L'             : "branch_l",
}


def processCommands(cmdList: list[tuple[int, str, str]]) -> list[Expression]:
    expressions: list[Expression] = []

    for i, (offset, macro, entryArgs) in enumerate(cmdList):
        cmd = cmdInfos[macro]

        if cmd.isBranch:
            *argsList, branchInfo = entryArgs.split(", ")
            entryArgs = ", ".join([x.strip() for x in argsList])

            args = None
            if entryArgs != "":
                args = entryArgs
            expr = Expression(tokenMap[macro], args)
            expressions.append(expr)

            # print(branchInfo)
            branchTarget = int(branchInfo.split(" - ")[0], 0)

            # Look up for branch target offset index
            j = -1
            for j, (suboffset, _, _) in enumerate(cmdList):
                if suboffset == branchTarget:
                    break

            if j == -1:
                eprint(f"Not able to find branch target for command {macro}({entryArgs}) at offset {offset:02X}")
                exit(1)

            # Get both braces of this check
            left = cmdList[i+1:j]
            right = cmdList[j:]
            if cmd.needsToInvert:
                right, left = left, right

            expr.left = processCommands(left)
            expr.right = processCommands(right)

            return expressions
        else:
            args = None
            if entryArgs != "":
                args = ", ".join([x.strip() for x in entryArgs.split(", ")])
            expr = Expression(tokenMap[macro], args)
            expressions.append(expr)

    return expressions


def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("input", help="Path to file to an array generated by scheduledis.py", type=Path)

    args = parser.parse_args()

    inputPath: Path = args.input

    if not inputPath.exists():
        eprint(f"Error: Input file '{inputPath}' not found")
        exit(1)

    inputContents = inputPath.read_text("UTF-8")

    cmds = toCommandList(inputContents)
    tree = processCommands(cmds)
    # print(tree)
    for expr in tree:
        expr.print()


if __name__ == "__main__":
    main()
