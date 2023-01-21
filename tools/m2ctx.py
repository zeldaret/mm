#!/usr/bin/env python3

import argparse, os, subprocess, sys
from pathlib import Path

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = script_dir + "/../"
src_dir = root_dir + "src/"

# Read through the processes context and replace whatever
def custom_replacements(output):
    output = output.splitlines()

    i = 0
    while i < len(output):
        line = output[i]

        ############### actorLists[2].first -> Player* ###############
        if "typedef struct ActorListEntry " in line:
            actorListText = ""
            i += 1
            while not output[i].startswith("}"):
                actorListText += output[i]
                i += 1
            actorCats = [
                "actorSwitch",
                "bg",
                "player",
                "explosive",
                "npc",
                "enemy",
                "prop",
                "itemAction",
                "misc",
                "boss",
                "door",
                "chest",
            ]
            actorList = []
            for x in range(12):
                actorList.append(actorListText.replace("first;", f"{actorCats[x]};") + "\n")
                if x == 2:
                    actorList[x] = actorList[x].replace("Actor*", "struct Player*")
        elif "ActorListEntry actorLists[ACTORCAT_MAX];" in line:
            output[i] = "struct {\n" + "".join(actorList) + "};"
        ########################################################

        i += 1
    return "\n".join(output)

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


def import_c_file(in_file):
    in_file = os.path.relpath(in_file, root_dir)
    cpp_command = ["gcc", "-E", "-P", "-Iinclude", "-Iassets", "-Isrc", "-undef", "-D__sgi", "-D_LANGUAGE_C",
                   "-DNON_MATCHING", "-D_Static_assert(x, y)=", "-D__attribute__(x)=", in_file]
    try:
        return subprocess.check_output(cpp_command, cwd=root_dir, encoding="utf-8")
    except subprocess.CalledProcessError:
        print(
            "Failed to preprocess input file, when running command:\n"
            + cpp_command,
            file=sys.stderr,
        )
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(usage="./m2ctx.py path/to/file.c or ./m2ctx.py (from an actor or gamestate's asm dir)",
                                     description="Creates a ctx.c file for mips2c. "
                                     "Output will be saved as oot/ctx.c")
    parser.add_argument('filepath', help="path of c file to be processed")
    parser.add_argument("--custom", "-c", dest="custom", action="store_true", default=False, 
                            help="Apply custom replacements to the output to help aid m2c output")
    args = parser.parse_args()

    if args.filepath:
        c_file_path = args.filepath
        print("Using file: {}".format(c_file_path))
    else:
        this_dir = Path.cwd()
        c_dir_path = get_c_dir(this_dir.name)
        if c_dir_path is None:
            sys.exit(
                "Cannot find appropriate c file dir. In argumentless mode, run this script from the c file's corresponding asm dir.")
        c_file = get_c_file(c_dir_path)
        c_file_path = os.path.join(c_dir_path, c_file)
        print("Using file: {}".format(c_file_path))

    output = import_c_file(c_file_path)

    if args.custom:
        output = custom_replacements(output)

    with open(os.path.join(root_dir, "ctx.c"), "w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()
