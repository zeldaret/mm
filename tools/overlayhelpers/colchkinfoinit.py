#!/usr/bin/env python3

import struct
import argparse
from actor_symbols import resolve_symbol

def HexParse(s):
    return int(s, 16)


def NameMass(info):
    if info[-1] == 0xFE:
        info[-1] = "MASS_HEAVY"
    else:
        if info[-1] == 0xFF:
            info[-1] = "MASS_IMMOVABLE"

def main():
    parser = argparse.ArgumentParser(description='Decompiles a ColChkInfoInit')
    parser.add_argument('address', help='VRAM or VROM address of a ColChkInfoInit', type=HexParse)
    parser.add_argument('type', help="Type: ColChkInfoInit or ColChkInfoInit2", choices=['ColChkInfoInit', 'ColChkInfoInit2'])
    args = parser.parse_args()

    file_path, file_offset = resolve_symbol(args.address)

    with open(file_path, 'rb') as f:
        filedata = f.read()

    if args.type == "ColChkInfoInit":
        info = list(struct.unpack(">Bx2hB", filedata[file_offset:file_offset+7]))
        NameMass(info)
        output="// sColChkInfoInit\nstatic CollisionCheckInfoInit D_{0:08X} = {{ ".format(args.address) + ", ".join(map(str,info)) + "};"
    else:
        info = list(struct.unpack(">Bx3hB", filedata[file_offset:file_offset+9]))
        NameMass(info)
        output="// sColChkInfoInit\nstatic CollisionCheckInfoInit2 D_{0:08X} = {{ ".format(args.address) + ", ".join(map(str,info)) + "};"

    print(output)

if __name__ == "__main__":
    main()
