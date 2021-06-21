#!/usr/bin/env python3

import os
import argparse

# "old": "new"
animdict ={
    "Actor_GetSwitchFlag": "Flags_GetSwitch",
    "atan_flip": "Math_Acot2F",
    "atans": "Math_Atan2S",
    "Matrix_Pop": "SysMatrix_StatePop",
    "Matrix_Push": "SysMatrix_StatePush",
    "Matrix_Init": "SysMatrix_StateAlloc",
    "Matrix_Put": "SysMatrix_SetCurrentState",
}

def replace_anim(file):
    with open(file,'r',encoding = 'utf-8') as infile:
        srcdata = infile.read()

    funcs = list(animdict.keys())
    fixes = 0
    for func in funcs:
        newfunc = animdict.get(func)
        if(newfunc is None):
            print("How did this happen?")
            return -1
        if(func in srcdata):
            fixes += 1
            print(func)
            srcdata = srcdata.replace(func, newfunc)

    if(fixes > 0):
        print('Changed', fixes,'entr' + ('y' if fixes == 1 else 'ies') + ' in',file)
        with open(file, 'w', encoding = 'utf-8', newline = '\n') as outfile:
            outfile.write(srcdata)
    return 1

def replace_anim_all(repo):
    for subdir, dirs, files in os.walk(repo + os.sep + 'src'):
        for filename in files:
            if(filename.endswith('.c')):
                file = subdir + os.sep + filename
                replace_anim(file)
    for subdir, dirs, files in os.walk(repo + os.sep + 'asm' + os.sep + 'non_matchings'):
        for filename in files:
            if(filename.endswith('.s')):
                file = subdir + os.sep + filename
                replace_anim(file)
    return 1

parser = argparse.ArgumentParser(description='Update to the new animation names')
parser.add_argument('file', help="source file to be processed. use . to process the whole repo", default = None)

if __name__ == "__main__":
    args = parser.parse_args()
    if(args.file == '.'):
        replace_anim_all(os.curdir)
    else:
        replace_anim(args.file)
