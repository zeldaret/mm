#!/usr/bin/env python3
import os, struct, sys, ast, argparse

def read_all_lines(file_name):
    lines = list()
    try:
        with open(file_name) as f:
            lines = f.readlines()
    except IOError:
        print('failed to read file ' + file_name)
        sys.exit(1)

    return lines

if __name__ == "__main__":
    map_lines = read_all_lines('build/mm.map')

    current_section = ''
    in_section_list = False
    asm_amounts = dict()
    src_amounts = dict()
    src_files = dict()
    for line in map_lines:
        if in_section_list:
            if line.startswith('OUTPUT(build/code.elf elf32-tradbigmips)'):
                break

            line_split =  list(filter(None, line.split()))

            if (len(line_split) > 0 and not line.startswith(' ')):
                current_section = line_split[0]
                src_amounts[current_section] = 0
                asm_amounts[current_section] = 0
                src_files[current_section] = []

            if (len(line_split) == 4 and line_split[0].startswith(".")):
                section = line_split[0]
                size = int(line_split[2], 16)
                obj_file = line_split[3]

                if (section == ".text" and not current_section + '_data' in obj_file and not current_section + '_rodata' in obj_file):
                    if (obj_file.startswith("build/src")):
                        src_amounts[current_section] += size
                        formatted_name = obj_file[len('build/'):] # remove build/ prefix
                        formatted_name = formatted_name[:-1] + 'c' # replace .o preface with .c
                        src_files[current_section].append(formatted_name)
                    elif (obj_file.startswith("build/asm")):
                        asm_amounts[current_section] += size
        else:
           in_section_list = line.startswith('Linker script and memory map')

    for section in src_files:
        for file in src_files[section]:
            file_lines = read_all_lines(file)
            for line in file_lines:
                if line.startswith('GLOBAL_ASM'):
                    line_split =  list(filter(None, line.split('\"')))
                    asm_lines = read_all_lines(line_split[1])
                    for asm_line in asm_lines:
                        if asm_line.startswith('/*'):
                            asm_amounts[section] += 4
                            src_amounts[section] -= 4

    src = 0
    asm = 0
    for section in src_amounts:
        src += src_amounts[section]
    for section in asm_amounts:
        asm += asm_amounts[section]

    total = src + asm
    src_percent = 100 * src / total
    asm_percent = 100 * asm / total

    print('{} total bytes of decompilable code\n'.format(total))
    print('{} bytes of code in src {}%'.format(src, src_percent))
    print('{} bytes of code in asm {}%\n'.format(asm, asm_percent))
    print("------------------------------------\n")

    num_masks = 24
    max_rupees = 500
    bytes_per_mask = total / num_masks
    bytes_per_rupee = bytes_per_mask / max_rupees
    masks = int(src / bytes_per_mask)
    rupees = int((src % bytes_per_mask) / bytes_per_rupee)

    if (rupees > 0):
        print('You have {}/{} masks and {}/{} rupee(s).\n'.format(masks, num_masks, rupees, max_rupees));
    else:
        print('You have {}/{} masks .\n'.format(masks, num_masks));

