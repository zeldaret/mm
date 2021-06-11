#!/usr/bin/env python3

import os, re

ASM_OUT = "asm/"
DATA_OUT = "data/"

func_regex = re.compile(r'\n\nglabel \S+\n')
rodata_symbols_regex = re.compile(r'(?<=\n)glabel (.+)(?=\n)')

def rodata_block_size(block):
    def align(x, n):
        while (x % n != 0):
            x += 1
        return x

    accumulator = 0
    for part in block.split(' */ .'):
        part = part.strip()
        if part.startswith('# '):
            continue
        elif part.startswith('asciz '):
            part = part[len('asciz '):]
            string = part[1:-1].encode('utf-8', 'ignore').decode('unicode_escape')
            accumulator += len(string.encode('euc-jp') + b'\x00')
        elif part.startswith('ascii'):
            part = part[len('ascii '):]
            string = part[1:-1].encode('utf-8', 'ignore').decode('unicode_escape')
            accumulator += len(string.encode('euc-jp'))
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

def rodata_syms(rodata):
    return re.findall(rodata_symbols_regex, rodata)

def rodata_blocks(rodata):
    return ["glabel" + b for b in rodata.split("glabel")[1:]]

def find_late_rodata_start(rodata):
    """
    Returns the symbol that is the first late_rodata symbol, or None if there is no late_rodata

    Note this is approximate as const qualified floats/doubles end up in rdata and not late_rodata,
        so there may be some overlap. This should not pose much of a problem however.
    Also note that this method assumes the input rodata consists only of at most one block rodata and one block late_rodata,
        that is that the file splits are correct.
    """
    first = None

    for sym,body in rodata:
        if sym.startswith("jtbl_") and ".word L" in body:
            # jump tables are always late_rodata, so we can return early
            # floats and doubles are very rarely not late_rodata, this is mostly seen in libultra, so we cannot return early for those
            if first is not None:
                return first
            else:
                return sym
        elif (".float " in body or ".double " in body) and first is None:
            # may be late_rodata, but we aren't sure yet
            # it is confirmed either by reaching the end or by finding a jumptable, and it is proven wrong if something that is not late_rodata occurs after it
            first = sym
        elif (".asciz" in body or (".word " in body and ".float" not in body) or ".half " in body or ".byte " in body) and first is not None:
            # reset first if something that is definitely not late_rodata is found
            # word and not float is due to some floats needing to be output as words either due to being a specific NaN value, or GAS can't convert it properly
            first = None
    # May still be None at this point, that just means there is no late_rodata
    return first

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

            rodata_info = list(zip(rodata_syms(rodata), rodata_blocks(rodata)))

            # populate rdata and late_rodata lists
            first_late_rodata = find_late_rodata_start(rodata_info)
            rdata_info = []
            late_rodata_info = []
            target = rdata_info # first populate rdata
            for sym,block in rodata_info:
                if sym == first_late_rodata: # now populate late_rodata, if there is any
                    target = late_rodata_info
                target.append((sym,block))

        # print([(sym,block.split("\n")[1:]) for sym,block in zip(rdata_syms,rdata_blocks)])

        function_info = list(zip([s.replace("glabel","").strip() for s in func_regex.findall(asm)], func_regex.split(asm)[1:]))

        rdata_map = {}
        late_rodata_map = {}

        # pass 1 to resolve rodata splits
        if rodata != "":
            last_fn = None

            referenced_in = {} # key=rodata label , value=function label

            for sym,_ in rodata_info:
                all_refs = [label for label,body in function_info if "%lo(" + sym + ")" in body]
                # ignore multiple refs, take only the first
                referenced_in.update({ sym : all_refs[0] if len(all_refs) != 0 else None })

            def do_splits(out_dict, info):
                first = True
                last_ref = None
                cr = None
                for sym,block in info:
                    ref = referenced_in[sym]
                    if first:
                        cr = ref or sym

                    if ref is not None and not first:
                        if ref != last_ref:
                            # existing function
                            cr = ref
                    elif last_ref is not None:
                        # new GLOBAL_ASM
                        cr = sym
                    
                    # add to output
                    if cr not in out_dict.keys():
                        out_dict.update({cr : []})
                    out_dict[cr].append((sym,block))

                    # setup next iter
                    last_ref = ref
                    first = False

            do_splits(rdata_map, rdata_info)
            do_splits(late_rodata_map, late_rodata_info)

        # all output files, order is irrelevant at this point
        all_output = set([label for label,_ in function_info]).union(set(rdata_map.keys()),set(late_rodata_map.keys()))

        # pass 2 to output splits
        for label in all_output:
            fn_body = dict(function_info).get(label, None)

            text_out = ""
            rodata_out = ""
            
            if fn_body is not None:
                text_out = "glabel " + label.strip() + "\n" + fn_body.strip() + "\n"

            if rodata != "":
                rdata = rdata_map.get(label, None)
                late_rodata = late_rodata_map.get(label, None)

                # check for late_rodata_alignment
                late_rodata_alignment = ""
                if fn_body is not None and late_rodata is not None:
                    ratio = late_rodata_size([block for _,block in late_rodata]) / text_block_size(fn_body)
                    if ratio > 1./3:
                        # print(f"{label} : {ratio}")
                        # TODO hack: getting the address from a comment
                        first_block_split = late_rodata[0][1].split(" */ .")
                        vaddr = None
                        if first_block_split[1].startswith("float") or first_block_split[1].startswith("double"):
                            vaddr = first_block_split[0].split(" ")[-2]
                        else:
                            vaddr = first_block_split[0].split(" ")[-1]
                        assert vaddr is not None
                        vaddr = int(vaddr,16)
                        late_rodata_alignment = f".late_rodata_alignment {'8' if vaddr % 8 == 0 else '4'}\n"

                rdata_out = ""
                if rdata is not None:
                    rdata_out = ".rdata\n" + "".join([block for _,block in rdata])

                late_rodata_out = ""
                if late_rodata is not None:
                    late_rodata_out = ".late_rodata\n" + late_rodata_alignment + "".join([block for _,block in late_rodata])

                rodata_out = rdata_out + late_rodata_out + (".text\n" if ((rdata is not None or late_rodata is not None) and fn_body is not None) else "")

            all_out = rodata_out + text_out

            # write it out
            out_path = root.replace(ASM_OUT, f"{ASM_OUT}/non_matchings/") + "/" +  ((f.replace(".text.s","") + "/") if "overlays" not in root else "")
            os.makedirs(out_path, exist_ok=True)
            with open(out_path + label + ".s", "w") as outfile:
                outfile.write(all_out)
