#!/usr/bin/env python3

import os

for root, dirs, files in os.walk("asm/non_matchings/"):
    for f in files:
        asm = ""
        with open(os.path.join(root, f), "r") as asm_file:
            asm = asm_file.read()
        
        hi_count = asm.count("%hi(")
        lo_count = asm.count("%lo(")

        if hi_count != lo_count:
            print(f"{os.path.join(root, f)}, ({hi_count}, {lo_count})")
