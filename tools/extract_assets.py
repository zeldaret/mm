#!/usr/bin/env python3

import argparse, json, os, signal, time, colorama, multiprocessing
from pathlib import Path

colorama.init()

dontGenerateCFilesList = [
    "map_grand_static",
    "map_i_static",
]

def SignalHandler(sig, frame):
    print(f'Signal {sig} received. Aborting...')
    mainAbort.set()
    # Don't exit immediately to update the extracted assets file.

def ExtractFile(xmlPath, outputPath, outputSourcePath):
    if globalAbort.is_set():
        # Don't extract if another file wasn't extracted properly.
        return

    generateSourceFile = "1"
    for name in dontGenerateCFilesList:
        if name in xmlPath:
            generateSourceFile = "0"
            break

    execStr = f"tools/ZAPD/ZAPD.out e -eh -i {xmlPath} -b {globalBaseromSegmentsDir} -o {outputPath} -osf {outputSourcePath} -gsf {generateSourceFile} -rconf tools/ZAPDConfigs/MM/Config.xml {ZAPDArgs}"

    if globalUnaccounted:
        execStr += " -Wunaccounted"

    print(execStr)
    exitValue = os.system(execStr)
    if exitValue != 0:
        globalAbort.set()
        print("\n")
        print("Error when extracting from file " + xmlPath, file=os.sys.stderr)
        print("Aborting...", file=os.sys.stderr)
        print("\n")

def ExtractFunc(fullPath):
    *pathList, xmlName = fullPath.split(os.sep)
    objectName = os.path.splitext(xmlName)[0]

    if "scenes" in pathList:
        outPath = os.path.join(globalOutputDir, *pathList[2:])
    else:
        outPath = os.path.join(globalOutputDir, *pathList[2:], objectName)
    outSourcePath = outPath

    if fullPath in globalExtractedAssetsTracker:
        timestamp = globalExtractedAssetsTracker[fullPath]["timestamp"]
        modificationTime = int(os.path.getmtime(fullPath))
        if modificationTime < timestamp:
            # XML has not been modified since last extraction.
            return

    currentTimeStamp = int(time.time())

    ExtractFile(fullPath, outPath, outSourcePath)

    if not globalAbort.is_set():
        # Only update timestamp on successful extractions
        if fullPath not in globalExtractedAssetsTracker:
            globalExtractedAssetsTracker[fullPath] = globalManager.dict()
        globalExtractedAssetsTracker[fullPath]["timestamp"] = currentTimeStamp

def initializeWorker(abort, unaccounted: bool, extractedAssetsTracker: dict, manager, baseromSegmentsDir: Path, outputDir: Path):
    global globalAbort
    global globalUnaccounted
    global globalExtractedAssetsTracker
    global globalManager
    global globalBaseromSegmentsDir
    global globalOutputDir
    globalAbort = abort
    globalUnaccounted = unaccounted
    globalExtractedAssetsTracker = extractedAssetsTracker
    globalManager = manager
    globalBaseromSegmentsDir = baseromSegmentsDir
    globalOutputDir = outputDir

def main():
    parser = argparse.ArgumentParser(description="baserom asset extractor")
    parser.add_argument(
        "baserom_segments_dir",
        type=Path,
        help="Directory of uncompressed ROM segments",
    )
    parser.add_argument(
        "output_dir",
        type=Path,
        help="Output directory to place files in",
    )
    parser.add_argument("-v", "--version", help="Which version should be processed", default="n64-us")
    parser.add_argument("-s", "--single", help="asset path relative to assets/, e.g. objects/gameplay_keep")
    parser.add_argument("-f", "--force", help="Force the extraction of every xml instead of checking the touched ones.", action="store_true")
    parser.add_argument("-j", "--jobs", help="Number of cpu cores to extract with.")
    parser.add_argument("-u", "--unaccounted", help="Enables ZAPD unaccounted detector warning system.", action="store_true")
    parser.add_argument("-Z", help="Pass the argument on to ZAPD, e.g. `-ZWunaccounted` to warn about unaccounted blocks in XMLs. Each argument should be passed separately, *without* the leading dash.", metavar="ZAPD_ARG", action="append")
    args = parser.parse_args()

    baseromSegmentsDir: Path = args.baserom_segments_dir
    outputDir: Path = args.output_dir

    args.output_dir.mkdir(parents=True, exist_ok=True)

    global ZAPDArgs
    ZAPDArgs = ""
    if args.Z is not None:
        badZAPDArg = False
        for i in range(len(args.Z)):
            z = args.Z[i]
            if z[0] == '-':
                print(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: argument \"{z}\" starts with \"-\", which is not supported.", file=os.sys.stderr)
                badZAPDArg = True
            else:
                args.Z[i] = "-" + z

        if badZAPDArg:
            exit(1)

        ZAPDArgs = " ".join(args.Z)
        print("Using extra ZAPD arguments: " + ZAPDArgs)

    global mainAbort
    mainAbort = multiprocessing.Event()
    manager = multiprocessing.Manager()
    signal.signal(signal.SIGINT, SignalHandler)

    extractedAssetsFile = Path("extracted") / args.version / ".extracted-assets.json"
    extractedAssetsTracker = manager.dict()
    if not args.force and extractedAssetsFile.exists():
        with extractedAssetsFile.open(encoding='utf-8') as f:
            extractedAssetsTracker.update(json.load(f, object_hook=manager.dict))

    asset_path = args.single
    if asset_path is not None:
        fullPath = os.path.join("assets", "xml", asset_path + ".xml")
        if not os.path.exists(fullPath):
            print(f"Error. File {fullPath} does not exist.", file=os.sys.stderr)
            exit(1)

        initializeWorker(mainAbort, args.unaccounted, extractedAssetsTracker, manager, baseromSegmentsDir, outputDir)
        # Always extract if -s is used.
        if fullPath in extractedAssetsTracker:
            del extractedAssetsTracker[fullPath]
        ExtractFunc(fullPath)
    else:
        xmlFiles = []
        for currentPath, _, files in os.walk(os.path.join("assets", "xml")):
            for file in files:
                fullPath = os.path.join(currentPath, file)
                # ZAPD can't handle audio, skip those XMLs.
                if file.endswith(".xml") and (fullPath.find("audio") == -1):
                    xmlFiles.append(fullPath)

        try:
            numCores = int(args.jobs or 0)
            if numCores <= 0:
                numCores = 1
            print("Extracting assets with " + str(numCores) + " CPU core" + ("s" if numCores > 1 else "") + ".")
            with multiprocessing.get_context("fork").Pool(numCores,  initializer=initializeWorker, initargs=(mainAbort, args.unaccounted, extractedAssetsTracker, manager, baseromSegmentsDir, outputDir)) as p:
                p.map(ExtractFunc, xmlFiles)
        except (multiprocessing.ProcessError, TypeError):
            print("Warning: Multiprocessing exception occurred.", file=os.sys.stderr)
            print("Disabling mutliprocessing.", file=os.sys.stderr)

            initializeWorker(mainAbort, args.unaccounted, extractedAssetsTracker, manager, baseromSegmentsDir, outputDir)
            for singlePath in xmlFiles:
                ExtractFunc(singlePath)

    with extractedAssetsFile.open('w', encoding='utf-8') as f:
        serializableDict = dict()
        for xml, data in extractedAssetsTracker.items():
            serializableDict[xml] = dict(data)
        json.dump(dict(serializableDict), f, ensure_ascii=False, indent=4)

    if mainAbort.is_set():
        exit(1)

if __name__ == "__main__":
    main()
