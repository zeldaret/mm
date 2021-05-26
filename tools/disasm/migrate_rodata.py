#!/usr/bin/env python3

import os, re

ASM_OUT = "asm/"
DATA_OUT = "data/"

func_regex = re.compile(r'\n\nglabel \S+\n')

rodata_symbols_regex = re.compile(r'(?<=\n)glabel (.+)(?=\n)')
asm_symbols_regex = re.compile(r'%(?:lo|hi)\((.+?)\)')

def align(x, n):
    while (x % n != 0):
        x += 1
    return x

def rodata_block_size(block):
    accumulator = 0
    for part in block.split('    .'):
        part = part.strip()
        if part.startswith('# '):
            continue
        elif part.startswith('asciz '):
            part = part[len('asciz '):]
            string = part[1:-1].encode('utf-8', 'ignore').decode('unicode_escape')
            accumulator += len(string.encode('euc-jp') + b'\x00')
        elif part.startswith('balign '):
            part = part[len('balign '):]
            accumulator = align(accumulator, int(part, 16 if part.startswith('0x') else 10))
        elif part.startswith('double '):
            part = part[len('double '):]
            accumulator = align(accumulator, 8)
            accumulator += 8 * (part.count(',') + 1)
        elif part.startswith('float '):
            part = part[len('float '):]
            accumulator = align(accumulator, 4)
            accumulator += 4 * (part.count(',') + 1)
        elif part.startswith('word '):
            part = part[len('word '):]
            accumulator = align(accumulator, 4)
            accumulator += 4 * (part.count(',') + 1)
        elif part.startswith('half '):
            part = part[len('half '):]
            accumulator = align(accumulator, 2)
            accumulator += 2 * (part.count(',') + 1)
        elif part.startswith('byte '):
            part = part[len('byte '):]
            accumulator += 1 * (part.count(',') + 1)
    return accumulator

def late_rodata_size(blocks):
    return sum([rodata_block_size(block) for block in blocks])

def text_block_size(asm):
    return 4*len([line for line in asm.split("\n") if line.startswith("/*")])

def is_late_rodata(block):
    return ".float" or ".double" or ".word L" in block

def asm_syms(asm):
    return re.findall(asm_symbols_regex, asm)

def rodata_syms(rodata):
    return re.findall(rodata_symbols_regex, rodata)

def rodata_blocks(rodata):
    return ["glabel" + b for b in rodata.split("glabel")[1:]]

def compare_items(a, b, items):
    """
    Return True if a is sooner in the list than b
    """
    if a not in items:
        return True
    if b not in items:
        return False
    for item in items:
        if item == a:
            return True
        if item == b:
            return False

for root,dirs,files in os.walk(ASM_OUT):
    for f in files:
        if "non_matchings" in root:
            continue
        asm_path = os.path.join(root,f)
        rodata_path = asm_path.replace(ASM_OUT + "overlays/", DATA_OUT).replace(ASM_OUT, DATA_OUT).replace(".text.s", ".rodata.s")

        # print(asm_path)

        asm = ""
        with open(asm_path,"r") as infile:
            asm = infile.read()

        rodata = ""
        if os.path.exists(rodata_path):
            # print(rodata_path)
            with open(rodata_path, "r") as rodata_file:
                rodata = rodata_file.read()

            rdata_syms = rodata_syms(rodata)
            rdata_blocks = rodata_blocks(rodata)
            rdata_info = list(zip(rdata_syms, rdata_blocks))

        # print([(sym,block.split("\n")[1:]) for sym,block in zip(rdata_syms,rdata_blocks)])

        function_labels = [s.replace("glabel","").strip() for s in func_regex.findall(asm)]
        function_bodies = func_regex.split(asm)[1:] # remove header

        all_referenced = set()

        function_info = list(zip(function_labels, function_bodies))

        rdata_map = {}

        # pass 1 to resolve rodata splits
        if rodata != "":
            # enumerate rodata references by function
            referenced_rodata = {}
            for label,body in function_info:
                referenced_rodata.update({label : [sym for sym in asm_syms(body) if sym in rdata_syms]})

            for label,body in function_info:
                for sym,block in rdata_info:
                    if sym in referenced_rodata[label]:
                        # referenced
                        pass
                    elif sym in [sym for lbl,sym in referenced_rodata.items() if lbl != label]:
                        # referenced in another function
                        break
                    else:
                        # unreferenced
                        pass



                    # intersection = referenced_rodata & all_referenced
                    # if len(intersection) != 0:
                    #     print("Multiply referenced")
                    #     print(intersection)

                    # if in rodata, put multiply referenced rodata into its own GLOBAL_ASM
                    # if in late_rodata, put multiply referenced in the lowest func address that it can possibly be in after accounting for continuity

                    # all_referenced.update(referenced_rodata)


        # pass 2 to output splits
        for label,body in zip(function_labels, function_bodies):
            text_out = "glabel " + label.strip() + "\n" + body.strip() + "\n"

            if rodata != "":
                rdata_out = ""
                late_rodata_out = ""

                rodata_out = ".rdata\n" + rdata_out + ".late_rodata\n" + late_rodata_out + ".text\n"
                pass

            all_out = rodata_out + text_out
            pass
        
        # unreferenced = set(rdata_syms) - all_referenced
        # if len(unreferenced) != 0:
        #     print("Unreferenced")
        #     print(unreferenced)
