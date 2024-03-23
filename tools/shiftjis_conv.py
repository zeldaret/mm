#!/usr/bin/env python3

import argparse
import sys

def sjis_process(buf, outfile):
    skipTimer = 0

    for i in range(len(buf)):
        if skipTimer > 0:
            skipTimer -= 1
            continue

        if buf[i] == "'" and buf[i+2] == "'" and ord(buf[i + 1]) > 0xFF:
            echar = buf[i+1].encode("shift-jis")
            hchar = int(echar.hex(), 16)
            outfile.write(f"0x{hchar:04X}")
            skipTimer = 2
        else:
            outfile.write(buf[i])

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Takes a file and converts shift-jis character literals to their hex value')
    parser.add_argument('infile', type=str, help='input file to process')
    parser.add_argument('-o', '--outfile', help='output file to write to. None for stdout')
    args = parser.parse_args()

    with open(args.infile) as f:
        fb = f.read()

    if args.outfile is None:
        sjis_process(fb, sys.stdout)
    else:
        with open(args.outfile, "w+") as outf:
            sjis_process(fb, outf)
