#!/usr/bin/env python3
#
#   Rename non_matching files whose name does not match the glabel function name
#

import os

to_rename = {}

for root, dirs, files in os.walk("asm/non_matchings/"):
    for f in [f for f in files if f.endswith(".s")]:
        full_path = os.path.join(root,f)
        contents = ""
        with open(full_path,"r") as infile:
            contents = infile.read()
        text_lines = []
        if ".text\n" in contents:
            text_lines = contents.split(".text\n")[1].split("\n")
        else:
            text_lines = contents.split("\n")
        for line in text_lines:
            if line.startswith("glabel "):
                if f.replace(".s","") != line.replace("glabel ",""):
                    to_rename.update({full_path : full_path.replace(f.replace(".s",""),line.replace("glabel ",""))})
                break

if any([list(to_rename.values()).count(x) > 1 for x in to_rename]):
    print("Rename collision, aborting!")
else:
    for old_path,new_path in to_rename.items():
        print(f"{old_path} --> {new_path}")
        os.rename(old_path, new_path)
