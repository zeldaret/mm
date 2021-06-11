#!/usr/bin/env python3

import argparse
import os
import struct
import sys
from pathlib import Path

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = script_dir + "/../"
src_dir = root_dir + "src/"


def get_c_dir(dirname):
    for root, dirs, files in os.walk(src_dir):
        for directory in dirs:
            if directory == dirname:
                return os.path.join(root, directory)


def get_c_file(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c") and "data" not in file:
                return file


def parse_data(file):
    entries = dict()

    with open(file, 'r') as f:
        glabels = f.read().split('glabel ')
        for glabel in glabels[2:]:
            split = glabel.split('\n')
            label = split[0]

            
            rest_of_label = split[1:]
            values = list()

            for f in rest_of_label:
                f = f.split('\t')
                values.append(f[-1])

            entries[split[0]] = values[:-1]

    return entries


def construct_arrays(data):
    output = ""

    for label, values in data.items():
        output += "s32 " + label + "[] = {"
        for value in values:
            output += "\n\t" + value + ","

            #labels floats as floats
            try:
                binary_data = bytes.fromhex(value[2:])
                number = struct.unpack('!f', binary_data)[0]
                if abs(number) > 0.0001 and abs(number) < 100000.0: 
                    output += " // f32: " + str(number)
            except Exception as e:
                pass
            

        output += "\n};\n\n"

    return output


def construct_extern(data):
    output = ""

    for label, values in data.items():
        output += "extern UNK_TYPE " + label + ";\n"

    return output


def main():
    parser = argparse.ArgumentParser(usage="./data_parser.py --file path/to/file.c or ./data_parser.py (from an actor or gamestate's asm dir)",
                                     description="Creates a data.c file. "
                                     "Output will be saved as data.c")
    parser.add_argument('--file', help="path of c file to be processed", required=False)
    parser.add_argument('--method', help="Method of output - options are 'extern' and 'arrays'.", required=False)
    args = parser.parse_args()

    if args.method not in ['extern', 'arrays']:
        print("Acceptable methods are {extern} and {arrays}.")
        print("Example usage: ./data_parser.py --method arrays --file ../../asm/overlays/ovl_En_Wallmas_data.asm")
        return

    if args.file:
        c_file_path = args.file
        print("Using file: {}".format(c_file_path))
    else:
        this_dir = Path.cwd()
        c_dir_path = get_c_dir(this_dir.name)
        if c_dir_path is None:
            sys.exit(
                "Cannot find appropriate c file dir. In argumentless mode, run this script from the c file's corresponding asm dir.")
        print("Example usage: ./data_parser.py --method arrays --file ../../asm/overlays/ovl_En_Wallmas_data.asm")
        c_file = get_c_file(c_dir_path)
        c_file_path = os.path.join(c_dir_path, c_file)
        print("Using file: {}".format(c_file_path))

    data = parse_data(c_file_path)
    output = None

    if args.method == 'extern':
        output = construct_extern(data)
    elif args.method == 'arrays':
        output = construct_arrays(data)

    with open(os.path.join(root_dir, "data.c"), "w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()
    
