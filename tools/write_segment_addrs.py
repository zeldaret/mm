#!/usr/bin/env python3

import os, re

g_segments = [
    set(),
    set(),
    set(),
    set(),
    set(),
    set(),
    dict(), # segment 6 special
    set(),
    set(),
    set(),
    set(),
    set(),
    set(),
    set(),
    set(),
    set(),
]

code_segment_addrs = set()

def segment_number(x):
    return (x >> 0x18) & 0xF

g_segments[6].update({"code" : set()})
for root,dirs,files in os.walk("asm/code/"):
    for f in files:
        asm_contents = ""
        with open(os.path.join(root,f),"r") as asm_file:
            asm_contents = asm_file.read()

        all_segments = [int(x.replace("D_",""),16) for x in re.findall(r'D_0[\da-fA-F]{7}', asm_contents)]

        for segment in [segment for segment in all_segments if segment_number(segment) != 0x06]:
            g_segments[segment_number(segment)].add(segment)
        for segment in [segment for segment in all_segments if segment_number(segment) == 0x06]:
            g_segments[6]["code"].add(segment)

for root,dirs,files in os.walk("asm/overlays/"):
    for f in files:
        ovl_name = f.replace(".text.s","")
        g_segments[6].update({ovl_name : set()})
        
        asm_contents = ""
        with open(os.path.join(root,f),"r") as asm_file:
            asm_contents = asm_file.read()

        all_segments = [int(x.replace("D_",""),16) for x in re.findall(r'D_0[\da-fA-F]{7}', asm_contents)]

        for segment in [segment for segment in all_segments if segment_number(segment) != 0x06]:
            g_segments[segment_number(segment)].add(segment)
        for segment in [segment for segment in all_segments if segment_number(segment) == 0x06]:
            g_segments[6][ovl_name].add(segment)

out = ""
for i,segments in enumerate(g_segments,0):
    out += f"// segment 0x{i:02X}\n\n"

    if i == 6:
        for name in g_segments[6].keys():
            if len(g_segments[6][name]) == 0:
                continue

            out += f"// {name}\n\n"
            for segment in sorted(g_segments[6][name]):
                out += f"D_{segment:08X} = 0x{segment:08X};\n"
            out += "\n"
    else:
        for segment in sorted(g_segments[i]):
            out += f"D_{segment:08X} = 0x{segment:08X};\n"
    out += "\n"

print(out)
