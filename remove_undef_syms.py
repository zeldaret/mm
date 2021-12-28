#!/usr/bin/env python3

import argparse
from pathlib import Path
import re
import glob

fd = Path("undefined_syms.txt").read_text().splitlines()
new_fd = []

i = 551
while i < 3080:
    if fd[i].startswith("//"):
        if (";" in fd[i+1] or ";" in fd[i+2]):
            new_fd.append(fd[i])
    else:
        new_fd.append(fd[i])
    i += 1

i = 0
fd = new_fd
new_fd = []
while i < len(fd)-1:
    if fd[i] == "" and fd[i+1] == "":
        i += 1
        continue
    new_fd.append(fd[i])
    i += 1


'''
files = {}
for file in glob.iglob("src/**/*.c", recursive=True):
    files[file] = Path(file).read_text()
for file in glob.iglob("asm/**/*.s", recursive=True):
    if "makerom" in file or "dmadata" in file:
        continue
    files[file] = Path(file).read_text()
for file in glob.iglob("data/**/*.s", recursive=True):
    if "makerom" in file or "dmadata" in file:
        continue
    files[file] = Path(file).read_text()

sym_regex = re.compile(r"(D_0[^8][0-9a-fA-F]{6})[^_]?")
curr_file_name = ""

for line in fd:
    if line.startswith("//"):
        curr_file_name = line.split("// ",1)[1]

    if line.startswith("D_04") or line.startswith("D_05") or line.startswith("D_06"):
        sym = line.split(" =",1)[0]

        #if sym != "D_06001E60":
        #    continue

        still_used = False
        if line.startswith("D_04") or line.startswith("D_05"):
            for file in files.values():
                if file.find(sym) >= 0:
                    still_used = True
                    break
        elif line.startswith("D_06"):
            for file in files.keys():
                if curr_file_name in file and file.endswith(".c"):
                    if file not in files:
                        continue
                    for l in files[file].splitlines():
                        if "#pragma GLOBAL_ASM" in l:
                            check_me = l.split("(",1)[1].split(")",1)[0][1:-1]
                            if files[check_me].find(sym) >= 0:
                                still_used = True
                                break

                    if files[file].find(sym) >= 0:
                        still_used = True
                        break

        #print(f"Used {still_used}")
        if still_used:
            new_fd.append(line)

        #exit()

    else:
        new_fd.append(line)
'''
print("\n".join(new_fd))
