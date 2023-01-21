#!/usr/bin/env python3
import colorama
colorama.init()

import argparse
import os
import re
import collections

regex_fileDataEntry = re.compile(r"^\s+(?P<section>[^\s]+)\s+(?P<vram>0x[^\s]+)\s+(?P<size>0x[^\s]+)\s+(?P<name>[^\s]+)$")
regex_bssEntry = re.compile(r"^\s+(?P<vram>0x[^\s]+)\s+(?P<name>[^\s]+)$")
regex_label = re.compile(r"^(?P<name>L[0-9A-F]{8})$")

VarInfo = collections.namedtuple("VarInfo", ["file", "vram"])

def parseMapFile(mapPath: str):
    with open(mapPath) as f:
        mapData = f.read()
        startIndex = mapData.find("..makerom")
        mapData = mapData[startIndex:]
    # print(len(mapData))

    symbolsDict = collections.OrderedDict()

    inFile = False
    currentFile = ""

    mapLines = mapData.split("\n")
    for line in mapLines:
        if inFile:
            if line.startswith("                "):
                entryMatch = regex_bssEntry.search(line)

                # Find variable
                if entryMatch is not None:
                    varName = entryMatch["name"]
                    varVram = int(entryMatch["vram"], 16)

                    # Filter out jump table labels
                    labelMatch = regex_label.search(varName)
                    if labelMatch is None:
                        symbolsDict[varName] = VarInfo( currentFile, varVram )
                        # print( symbolsDict[varName] )

            else:
                inFile = False
        else:
            if line.startswith(" .bss "):
                inFile = False
                entryMatch = regex_fileDataEntry.search(line)

                # Find file
                if entryMatch is not None:
                    name = "/".join(entryMatch["name"].split("/")[1:])

                    # mapfile only contains .o files, so just strip the last character to replace it
                    # we assume all the .c files are in the src folder, and all others are .s (true for OoT/MM)
                    if name.split("/")[0] == "src":
                        name = name[:-1] + "c"
                    else:
                        name = name[:-1] + "s"

                    size = int(entryMatch["size"], 16)
                    vram = int(entryMatch["vram"], 16)

                    if size > 0:
                        inFile = True
                        currentFile = name

    return symbolsDict


Compared = collections.namedtuple("Compared", [ "buildAddress", "buildFile", "expectedAddress", "expectedFile", "diff"])

def compareMapFiles(mapFileBuild: str, mapFileExpected: str):
    badFiles = set()
    missingFiles = set()

    print("Build mapfile:    " + mapFileBuild, file=os.sys.stderr)
    print("Expected mapfile: " + mapFileExpected, file=os.sys.stderr)
    print("", file=os.sys.stderr)

    if not os.path.exists(mapFileBuild):
        print(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: mapfile not found at {mapFileBuild}. Did you enter the correct path?", file=os.sys.stderr)
        exit(1)

    if not os.path.exists(mapFileExpected):
        print(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: expected mapfile not found at {mapFileExpected}. Is 'expected' missing or in a different folder?", file=os.sys.stderr)
        exit(1)

    buildMap = parseMapFile(mapFileBuild)
    expectedMap = parseMapFile(mapFileExpected)

    comparedDict = collections.OrderedDict()

    for symbol in buildMap:
        if symbol in expectedMap:
            comparedDict[symbol] = Compared( buildMap[symbol].vram, buildMap[symbol].file, expectedMap[symbol].vram, expectedMap[symbol].file, buildMap[symbol].vram - expectedMap[symbol].vram )
            if comparedDict[symbol].diff != 0:
                badFiles.add(buildMap[symbol].file)
                
        else:
            missingFiles.add(buildMap[symbol].file)
            comparedDict[symbol] = Compared( buildMap[symbol].vram, buildMap[symbol].file, -1, "", "Unknown" )

    for symbol in expectedMap:
        if not symbol in buildMap:
            missingFiles.add(expectedMap[symbol].file)
            comparedDict[symbol] = Compared( -1, "", expectedMap[symbol].vram, expectedMap[symbol].file, "Unknown" )

    return badFiles, missingFiles, comparedDict


def printCsv(badFiles, missingFiles, comparedDict, printAll = True):
    print("Symbol Name,Build Address,Build File,Expected Address,Expected File,Difference,GOOD/BAD/MISSING")

    # If it's bad or missing, don't need to do anything special.
    # If it's good, check for if it's in a file with bad or missing stuff, and check if print all is on. If none of these, print it.
    
    for symbol in comparedDict:
        symbolInfo = comparedDict[symbol]
        symbolGood = colorama.Fore.RED + "BAD" + colorama.Fore.RESET
        if type(symbolInfo.diff) != int:
            symbolGood = colorama.Fore.YELLOW + "MISSING" + colorama.Fore.RESET
            print(f"{symbol},{symbolInfo.buildAddress:X},{symbolInfo.buildFile},{symbolInfo.expectedAddress:X},{symbolInfo.expectedFile},{symbolInfo.diff},{symbolGood}")
            continue

        if symbolInfo.diff == 0:
            symbolGood = colorama.Fore.GREEN + "GOOD" + colorama.Fore.RESET
            if (not symbolInfo.buildFile in badFiles and not symbolInfo.expectedFile in badFiles) and (not symbolInfo.buildFile in badFiles and not symbolInfo.expectedFile in badFiles) and not printAll:
                continue
        
        if symbolInfo.buildFile != symbolInfo.expectedFile:
            symbolGood += colorama.Fore.CYAN + " MOVED" + colorama.Fore.RESET
        print(f"{symbol},{symbolInfo.buildAddress:X},{symbolInfo.buildFile},{symbolInfo.expectedAddress:X},{symbolInfo.expectedFile},{symbolInfo.diff:X},{symbolGood}")


def main():
    description = "Check that globally visible bss has not been reordered."
    epilog = """\
    N.B. Since this script reads the map files, it can only see globally visible bss; in-function static bss must be examined with other tools.
    """

    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("mapFile", help="Path to a map file.")
    parser.add_argument("mapFileExpected", help="Path to the expected map file. Optional, default is 'expected/mapFile'.", nargs="?", default="")
    parser.add_argument("-a", "--print-all", help="Print all bss, not just non-matching.", action="store_true")
    parser.add_argument("-n", "--no-fun-allowed", help="Remove amusing messages.", action="store_true")
    args = parser.parse_args()

    if args.mapFileExpected == "":
        args.mapFileExpected = os.path.join("expected", args.mapFile)

    badFiles, missingFiles, comparedDict = compareMapFiles(args.mapFile, args.mapFileExpected)
    printCsv(badFiles, missingFiles, comparedDict, args.print_all)

    if len(badFiles) + len(missingFiles) != 0:
        print("", file=os.sys.stderr)

        if len(badFiles) != 0:
            print(colorama.Fore.RED + "  BAD" + colorama.Style.RESET_ALL)

            for file in badFiles:
                print(f"bss reordering in {file}", file=os.sys.stderr)
            print("", file=os.sys.stderr)
            
            if not args.no_fun_allowed:
                print(colorama.Fore.LIGHTWHITE_EX +
                "  BSS is REORDERED!!\n"
                "  Oh! MY GOD!!" 
                + colorama.Style.RESET_ALL, file=os.sys.stderr)
                print("", file=os.sys.stderr)

        if len(missingFiles) != 0:
            print(colorama.Fore.YELLOW + "  MISSING" + colorama.Style.RESET_ALL)

            for file in missingFiles:
                print(f"Symbols missing from {file}", file=os.sys.stderr)
            print("", file=os.sys.stderr)

            if not args.no_fun_allowed:
                print(colorama.Fore.LIGHTWHITE_EX + "  Error, should (not) be in here " + colorama.Style.RESET_ALL, file=os.sys.stderr)
                print("", file=os.sys.stderr)

            print("Some files appear to be missing symbols. Have they been renamed or declared as static? You may need to remake 'expected'", file=os.sys.stderr)

        return 1
    
    print("", file=os.sys.stderr)
    print(colorama.Fore.GREEN + "  GOOD" + colorama.Style.RESET_ALL, file=os.sys.stderr)

    if args.no_fun_allowed:
        return 0

    print("\n" + colorama.Fore.LIGHTWHITE_EX +
    colorama.Back.RED + "                                  " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "         CONGRATURATIONS!         " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "    All Global BSS is correct.    " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "             THANK YOU!           " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "      You are great decomper!     " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "                                  " + colorama.Style.RESET_ALL , file=os.sys.stderr)

    return 0

if __name__ == "__main__":
    ret = main()
    exit(ret)
