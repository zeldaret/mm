#!/usr/bin/env python3

import os
import argparse

# all occurrences of keys will be replaced by associated value
simpleReplace = {
    # "Math_Rand_":"Rand_",
    # "ACTORTYPE":"ACTORCAT",
    # "DistToLink":"DistToPlayer",
    # "HitItem":"HitInfo",
}

# all occurrences of keys will be replaced by associated value,
# if the occurence is the whole word
# for example, if there is a space before and an open parenthesis after,
# like for a function call: ` func_8002E4B4(`
# 
# Custom behaviour can be enabled by using a tuple as the value (see 
# explanation in replace_single below)
wordReplace = {
    # "Actor_MarkForDeath": "Actor_Kill",
    "gSaveContext.weekEventReg": "gSaveContext.save.weekEventReg",
    "gSaveContext.playerForm": "gSaveContext.save.playerForm",
    "gSaveContext.day": "gSaveContext.save.day",
    "gSaveContext.isNight": "gSaveContext.save.isNight",
    "gSaveContext.naviTimer": "gSaveContext.save.playerData.tatlTimer",
    "gSaveContext.tatlTimer": "gSaveContext.save.playerData.tatlTimer",
    "gSaveContext.rupees": "gSaveContext.save.playerData.rupees",
    "gSaveContext.magicAcquired": "gSaveContext.save.playerData.magicAcquired",
    "gSaveContext.doubleMagic": "gSaveContext.save.playerData.doubleMagic",
    "gSaveContext.doubleDefense": "gSaveContext.save.playerData.doubleDefense",
    "gSaveContext.playerName": "gSaveContext.save.playerData.playerName",
    "gSaveContext.inventory": "gSaveContext.save.inventory",
    "gSaveContext.equippedMask": "gSaveContext.save.equippedMask",
    "gSaveContext.entranceIndex": "gSaveContext.save.entranceIndex",
    "gSaveContext.time": "gSaveContext.save.time",
    "gSaveContext.unk_14": "gSaveContext.save.daySpeed",
    "gSaveContext.unk_FE6": "gSaveContext.save.bombersCaughtNum",
    "gSaveContext.unk_FE7": "gSaveContext.save.bombersCaughtOrder",
    "gSaveContext.linkAge": "gSaveContext.save.linkAge",
    "gSaveContext.dekuPlaygroundHighScores": "gSaveContext.save.dekuPlaygroundHighScores",
    "gSaveContext.lotteryCodeGuess": "gSaveContext.save.lotteryCodeGuess",
    "gSaveContext.permanentSceneFlags": "gSaveContext.save.permanentSceneFlags",
    "gSaveContext.bomberCode": "gSaveContext.save.bomberCode",
    "gSaveContext.skullTokenCount": "gSaveContext.save.skullTokenCount",
    "gSaveContext.cutscene": "gSaveContext.save.cutscene",
    "gSaveContext.health": "gSaveContext.save.playerData.health",

    # Example of custom behaviour:
    # "PLAYER": ("GET_PLAYER(globalCtx)", {"ignore": (-1, '"PLAYER"')}), # ignore "PLAYER" in sSoundBankNames
}

# [a-zA-Z0-9_]
def is_word_char(c):
    return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or (c >= '0' and c <= '9') or c == '_'

def replace_single(file):
    with open(file, 'r', encoding = 'utf-8') as infile:
        srcdata = infile.read()

    changesCount = 0

    for old, new in simpleReplace.items():
        # replace `old` with `new`
        if old in srcdata:
            changesCount += 1
            print(old, "->", new)
            srcdata = srcdata.replace(old, new)

    for old, new in wordReplace.items():
        # `new` can be a tuple where the first element is what to replace `old` with,
        # and the second element is a dict containing "custom behavior" properties.
        if isinstance(new, tuple):
            custom_behavior = True
            new, custom_behavior_data = new
            # The "ignore" data is a tuple where the first element is an offset relative to
            # where `old` was found, and the string from that index must differ from the
            # tuple's second element for the replacement to be done.
            custom_behavior_ignore_data = custom_behavior_data.get("ignore")
            custom_behavior_ignore = custom_behavior_ignore_data is not None
            if custom_behavior_ignore:
                custom_behavior_ignore_offset, custom_behavior_ignore_match = custom_behavior_ignore_data
        else:
            custom_behavior = False
        # replace `old` with `new` if the occurence of `old` is the whole word
        oldStartIdx = srcdata.find(old)
        if oldStartIdx >= 0:
            old_start_as_word = is_word_char(old[0])
            old_end_as_word = is_word_char(old[-1])
            replaceCount = 0
            while oldStartIdx >= 0:
                replace = True
                if old_start_as_word:
                    if oldStartIdx == 0:
                        pass
                    elif is_word_char(srcdata[oldStartIdx-1]):
                        replace = False
                if old_end_as_word:
                    oldEndIdx = oldStartIdx + len(old)
                    if oldEndIdx >= len(srcdata):
                        pass
                    elif is_word_char(srcdata[oldEndIdx]):
                        replace = False
                if replace and custom_behavior and custom_behavior_ignore:
                    if srcdata[oldStartIdx + custom_behavior_ignore_offset:].startswith(custom_behavior_ignore_match):
                        replace = False
                if replace:
                    srcdata = srcdata[:oldStartIdx] + new + srcdata[oldEndIdx:]
                    replaceCount += 1
                oldStartIdx = srcdata.find(old, oldStartIdx + len(new))
            if replaceCount > 0:
                changesCount += 1
                print(old, "->", new)

    if changesCount > 0:
        print('Changed', changesCount, 'entry' if changesCount == 1 else 'entries', 'in', file)
        with open(file, 'w', encoding = 'utf-8', newline = '\n') as outfile:
            outfile.write(srcdata)

def replace_all(repo):
    for subdir, dirs, files in os.walk(repo + os.sep + 'src'):
        for filename in files:
            if filename.endswith('.c') or filename.endswith('.h'):
                file = subdir + os.sep + filename
                replace_single(file)
    for subdir, dirs, files in os.walk(repo + os.sep + 'include'):
        for filename in files:
            if filename.endswith('.c') or filename.endswith('.h'):
                file = subdir + os.sep + filename
                replace_single(file)

    functions_txt = os.path.join(repo, "tools", "disasm", "functions.txt")
    variables_txt = os.path.join(repo, "tools", "disasm", "variables.txt")
    for file in [functions_txt,variables_txt]:
        replace_single(file)

    for subdir, dirs, files in os.walk(repo + os.sep + 'asm'):
        for filename in files:
            if filename.endswith('.s'):
                file = subdir + os.sep + filename
                replace_single(file)

parser = argparse.ArgumentParser(description='Apply function renames to a file')
parser.add_argument('file', help="source file to be processed. use . to process the whole repo")

if __name__ == "__main__":
    args = parser.parse_args()
    if args.file == '.':
        replace_all(os.curdir)
    else:
        replace_single(args.file)
