#!/usr/bin/env python3
import argparse, os

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('input', help='input .c file')
    parser.add_argument('output', help='output .d file')
    args = parser.parse_args()

    asm_file = None
    with open(args.input, 'r') as f:
        lines = f.readlines()
        # Search for the first GLOBAL_ASM and use that as a dependency
        # We won't list all split assembly files as it is tricky to properly set up make recipes with multiple outputs
        for line in lines:
            if '#pragma GLOBAL_ASM(' in line:
                base_path = os.path.normpath(line.split('"')[1])
                path = os.path.split(base_path)[0]
                asm_file = path.replace('non_matchings/', '') + '.asm ' # base .asm file
                asm_file += path # split function .asm file
                break

    with open(args.output, 'w') as f:
        f.write('build/' + args.input.replace('.c', '.o' + ': '))
        if asm_file is not None:
            f.write(asm_file + ' ')

        f.write('\n')

