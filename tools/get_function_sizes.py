#!/usr/bin/env python3

import argparse, math, os, re
from posixpath import relpath

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = script_dir + "/../"
# asm_dir = root_dir + "asm/non_matchings/overlays/"
# build_dir = root_dir + "build/src/overlays/actors"
asm_dir = root_dir + "asm/non_matchings/"
build_dir = root_dir + "build/src/"


def get_num_instructions(f_path):
    with open(f_path) as f:
        f_lines = f.readlines()
    sum = 0
    for line in f_lines:
        if line.startswith("/* "):
            sum += 1
    return sum


def count_non_matching():
    overlays = {}

    for root, dirs, _ in os.walk(asm_dir):
        for actor_dir in dirs:
            total_size = 0
            max_size = -1
            ovl_path = os.path.join(root, actor_dir)
            num_files = 0

            actor_funcs = {}

            for f_name in os.listdir(ovl_path):
                file_path = os.path.join(ovl_path, f_name)
                file_size = get_num_instructions(file_path)

                num_files += 1
                total_size += file_size
                if file_size > max_size:
                    max_size = file_size
                actor_funcs[f_name] = file_size

            overlays[actor_dir] = {
                "summary": (num_files, max_size, total_size, 
                    total_size / num_files),
                "funcs": actor_funcs
            }
    
    return overlays


pattern_function = re.compile("^[0-9a-fA-F]+ <(.+)>:")
pattern_switchcase = re.compile("L[0-9a-fA-F]{8}")

def count_built_funcs_and_instructions(f_path):
    f_lines = ""
    with open(f_path) as f:
        f_lines = f.readlines()
    
    current = ""
    funcs = {}
    for line in f_lines:
        if line.strip() == "":
            continue
        match_function = pattern_function.match(line)
        if match_function:
            func_name = match_function.group(1)
            if pattern_switchcase.match(func_name):
                # this is not a real function tag.
                # probably a case from a switch
                # for example: <L80979A80>
                continue
            current = func_name
            funcs[current] = 0
        elif current != "":
            funcs[current] += 1
    return funcs


def count_build():
    overlays = {}

    for root, dirs, files in os.walk(build_dir):
        # print(root,dirs,files)
        for actor_dir in dirs:
            # if len(files) == 0:
            #     continue
            total_size = 0
            max_size = -1
            ovl_path = os.path.join(root, actor_dir)
            num_funcs = 0    

            actor_funcs = {}

            for f_name in os.listdir(ovl_path):
                if len(dirs) == 0:
                    continue
                if not f_name.endswith(".s"):
                    continue
                if f_name.endswith("_reloc.s"):
                    continue

                file_path = os.path.join(ovl_path, f_name)
                funcs = count_built_funcs_and_instructions(file_path)
                
                if len(funcs) > 0:
                    # print(funcs)
                    num_funcs = len(funcs)
                    # round up the file size to a multiple of four.
                    total_size = math.ceil(sum(funcs.values())/4)*4
                    max_size = max(funcs.values())
                    # merges both dictionaries
                    actor_funcs = {**actor_funcs, **funcs}
                    
                if num_funcs == 0:
                    continue

                # Get directory relative to starting directory
                rel_dir = os.path.relpath(ovl_path, build_dir)

                overlays[os.path.join(rel_dir, os.path.splitext(f_name)[0])] = {
                    "summary": (num_funcs, max_size, total_size, 
                        total_size / num_funcs),
                    "funcs": actor_funcs
                }


    return overlays


def get_list_from_file(filename):
    actor_list = []
    if filename is not None:
        with open(filename) as f:
            actor_list = list(map(lambda x: x.strip().split(",")[0], f.readlines()))
    return actor_list


def print_csv(overlays, ignored, include_only):
    sorted_actors = [(k, v["summary"]) for k, v in overlays.items()]
    sorted_actors.sort()

    print("File,Num functions,Max size,Total size,Average size")

    for actor_data in sorted_actors:
        name = actor_data[0]
        other = actor_data[1]
        if name in ignored:
            continue
        if include_only and name not in include_only:
            continue
        print("{},{},{},{},{:0.2f}".format(name, *other))


def print_function_lines(overlays, ignored, include_only):
    sorted_actors = []
    for k, v in overlays.items():
        func_data = []
        for func_name, lines in v["funcs"].items():
            func_data.append((func_name, lines))
        #func_data.sort(key=lambda x: x[1], reverse=True)
        sorted_actors.append((k, func_data))
    sorted_actors.sort()

    print("File,Function_name,Lines")

    for actor_data in sorted_actors:
        name = actor_data[0]
        func_data = actor_data[1]
        if name in ignored:
            continue
        if include_only and name not in include_only:
            continue
        for func_name, lines in func_data:
            print("{},{},{}".format(name, func_name, lines))


def main():
    description = "Collects actor's functions sizes, and print them in csv format."

    epilog = """\
To make a .csv with the data, simply redirect the output. For example:
    ./tools/get_actor_sizes.py > results.csv

Flags can be mixed to produce a customized result:
    ./tools/get_actor_sizes.py --function-lines --non-matching > status.csv
    ./tools/get_actor_sizes.py --non-matching --ignore pull_request.csv > non_matching.csv
    ./tools/get_actor_sizes.py --non-matching --function-lines --include-only my_reserved.csv > my_status.csv
    """
    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("-d", help="Directory to examine.", default="src/overlays/actors")
    parser.add_argument("--non-matching", help="Collect data of the non-matching actors instead.", action="store_true")
    parser.add_argument("--function-lines", help="Prints the size of every function instead of a summary.", action="store_true")
    parser.add_argument("--ignore", help="Path to a file containing actor's names. The data of actors in this list will be ignored.")
    parser.add_argument("--include-only", help="Path to a file containing actor's names. Only data of actors in this list will be printed.")
    args = parser.parse_args()

    if args.non_matching:
        overlays = count_non_matching()
    else:
        overlays = count_build()

    ignored = get_list_from_file(args.ignore)
    include_only = get_list_from_file(args.include_only)

    if args.function_lines:
        print_function_lines(overlays, ignored, include_only)
    else:
        print_csv(overlays, ignored, include_only)

main()
