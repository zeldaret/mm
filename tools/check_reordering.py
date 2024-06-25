#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 ZeldaRET
# SPDX-License-Identifier: MIT

import colorama
colorama.init()

import argparse
import sys
import mapfile_parser
from pathlib import Path

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def mapPathToSource(origName: Path) -> Path:
    # Try to map built path to the source path
    parts = origName.parts
    if parts[0] == "build":
        parts = parts[2:]

    path = Path(*parts)
    # Assume every file in the asm folder has .s extension, while everything else has .c extension
    if path.parts[0] == "asm":
        path = path.with_suffix(".s")
    else:
        path = path.with_suffix(".c")
    return path

def compareMapFiles(mapFileBuild: Path, mapFileExpected: Path, section: str=".bss", reverseCheck: bool=True) -> mapfile_parser.MapsComparisonInfo:
    eprint(f"Build mapfile:    {mapFileBuild}")
    eprint(f"Expected mapfile: {mapFileExpected}")
    eprint("")

    if not mapFileBuild.exists():
        eprint(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: mapfile not found at {mapFileBuild}. Did you forget to build the rom?")
        exit(1)

    if not mapFileExpected.exists():
        eprint(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: expected mapfile not found at {mapFileExpected}. A mapfile under the 'expected' folder is required")
        exit(1)

    buildMap = mapfile_parser.MapFile()
    buildMap.readMapFile(mapFileBuild)
    if section != "all":
        buildMap = buildMap.filterBySectionType(section)

    expectedMap = mapfile_parser.MapFile()
    expectedMap.readMapFile(mapFileExpected)
    if section != "all":
        expectedMap = expectedMap.filterBySectionType(section)

    return buildMap.compareFilesAndSymbols(expectedMap, checkOtherOnSelf=reverseCheck)


def printSymbolComparison(comparisonInfo: mapfile_parser.MapsComparisonInfo, printAll = True):
    print("Symbol Name,Build Address,Build File,Expected Address,Expected File,Difference,GOOD/BAD/MISSING")

    # If it's bad or missing, don't need to do anything special.
    # If it's good, check for if it's in a file with bad or missing stuff, and check if print all is on. If none of these, print it.

    for symbolInfo in comparisonInfo.comparedList:
        buildFile = symbolInfo.buildFile.filepath if symbolInfo.buildFile is not None else None
        expectedFile = symbolInfo.expectedFile.filepath if symbolInfo.expectedFile is not None else None

        buildFileName = ""
        if buildFile is not None:
            buildFileName = mapPathToSource(buildFile)

        expectedFileName = ""
        if expectedFile is not None:
            expectedFileName = mapPathToSource(expectedFile)

        symbolGood = colorama.Fore.RED + "BAD" + colorama.Fore.RESET
        if symbolInfo.diff is None:
            symbolGood = colorama.Fore.YELLOW + "MISSING" + colorama.Fore.RESET
            print(f"{symbolInfo.symbol.name},{symbolInfo.buildAddress:X},{buildFileName},{symbolInfo.expectedAddress:X},{expectedFileName},{symbolInfo.diff},{symbolGood}")
            continue

        if symbolInfo.diff == 0:
            symbolGood = colorama.Fore.GREEN + "GOOD" + colorama.Fore.RESET
            if not buildFile in comparisonInfo.badFiles and not expectedFile in comparisonInfo.badFiles:
                if not buildFile in comparisonInfo.badFiles and not expectedFile in comparisonInfo.badFiles:
                    if not printAll:
                        continue

        if buildFile != expectedFile:
            symbolGood += colorama.Fore.CYAN + " MOVED" + colorama.Fore.RESET
        print(f"{symbolInfo.symbol.name},{symbolInfo.buildAddress:X},{buildFileName},{symbolInfo.expectedAddress:X},{expectedFileName},{symbolInfo.diff:X},{symbolGood}")


def printFileComparison(comparisonInfo: mapfile_parser.MapsComparisonInfo, fun_allowed: bool = True):
    eprint("")

    if len(comparisonInfo.badFiles) != 0:
        print(colorama.Fore.RED + "  BAD" + colorama.Style.RESET_ALL)

        for file in comparisonInfo.badFiles:
            eprint(f"Symbol reordering in {mapPathToSource(file.filepath)}")
        eprint("")

        if fun_allowed:
            eprint(colorama.Fore.LIGHTWHITE_EX +
            "  Symbols are REORDERED!!\n"
            "  Oh! MY GOD!!" 
            + colorama.Style.RESET_ALL)
            eprint("")

    if len(comparisonInfo.missingFiles) != 0:
        print(colorama.Fore.YELLOW + "  MISSING" + colorama.Style.RESET_ALL)

        for file in comparisonInfo.missingFiles:
            eprint(f"Symbols missing from {mapPathToSource(file.filepath)}")
        eprint("")

        if fun_allowed:
            eprint(colorama.Fore.LIGHTWHITE_EX + "  Error, should (not) be in here " + colorama.Style.RESET_ALL)
            eprint("")

        eprint("Some files appear to be missing symbols. Have they been renamed or declared as static? You may need to remake 'expected'")


def main():
    description = "Check that globally visible symbols has not been reordered."
    epilog = """\
    N.B. Since this script reads the map files, it can only see globally visible symbols; in-function static symbols must be examined with other tools.
    """

    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("-v", "--version", help="MM version to check. Defaults to n64-us", default="n64-us")
    parser.add_argument("-a", "--print-all", help="Print all symbols of the section, not just non-matching.", action="store_true")
    parser.add_argument("-n", "--no-fun-allowed", help="Remove amusing messages.", action="store_true")
    parser.add_argument("-r", "--no-reverse-check", help="Disable looking for symbols on the expected map that are missing on the built map file.", action="store_true")
    parser.add_argument("-s", "--section", help="Specify which section should be checked for reordered symbols. Use `all` to check all sections. Defaults to .bss", default=".bss", choices=[".text", ".data", ".rodata", ".bss", "all"])
    args = parser.parse_args()

    mapfilePath = Path(f"build/{args.version}/mm-{args.version}.map")
    mapfileExpectedPath = "expected" / mapfilePath
    reverseCheck: bool = not args.no_reverse_check
    section: str = args.section

    comparisonInfo = compareMapFiles(mapfilePath, mapfileExpectedPath, section, reverseCheck)
    printSymbolComparison(comparisonInfo, args.print_all)

    if len(comparisonInfo.badFiles) + len(comparisonInfo.missingFiles) != 0:
        printFileComparison(comparisonInfo, not args.no_fun_allowed)
        return 1

    eprint("")
    eprint(colorama.Fore.GREEN + "  GOOD" + colorama.Style.RESET_ALL)

    if args.no_fun_allowed:
        return 0

    eprint("\n" + colorama.Fore.LIGHTWHITE_EX +
    colorama.Back.RED + f"                                  " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + f"         CONGRATURATIONS!         " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "{:^34}".format(f"All Global {section if section != 'all' else 'Symbols'} is correct.") + colorama.Back.RESET + "\n" +
    colorama.Back.RED + f"             THANK YOU!           " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + f"      You are great decomper!     " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + f"                                  " + colorama.Style.RESET_ALL )

    return 0

if __name__ == "__main__":
    ret = main()
    exit(ret)
