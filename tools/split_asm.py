#!/usr/bin/env python3
import argparse, os

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('input', help='input file')
    parser.add_argument('output', help='output file path')
    parser.add_argument('-c', '--c-base', help='create base c file that has GLOBAL_ASM for each function', metavar='file')
    args = parser.parse_args()

    os.makedirs(args.output, exist_ok=True)

    file_names = []

    with open(args.input, 'r') as f:
        current_file = None
        writing = False
        lines = f.readlines()
        for line in lines:
            if line.startswith('glabel') and not line.startswith('glabel L80'):
                if current_file != None:
                    current_file.close()
                func_name = line.split()[1]

                assert(func_name != '')

                file_name = args.output + '/' + func_name + '.asm'
                current_file = open(file_name, 'w')
                writing = True
                file_names.append(file_name)

            if '.word' in line:
                writing = False

            if writing:
                current_file.write(line)

        if current_file != None:
            current_file.close()

    if args.c_base != None:
        os.makedirs(os.path.dirname(args.c_base), exist_ok=True)
        with open(args.c_base, 'w') as f:
            f.write('#include <ultra64.h>\n#include <global.h>\n')

            for name in file_names:
                f.write('\n#pragma GLOBAL_ASM("{}")\n'.format(name))

