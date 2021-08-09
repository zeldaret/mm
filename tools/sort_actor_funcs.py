#!/usr/bin/env python3

from pathlib import Path
import argparse

parser = argparse.ArgumentParser(description="Script to sort forward-declared functions and extern'd symbols in actors")
parser.add_argument("file", type=str, help="Path to c file to sort")
args = parser.parse_args()

file_path = Path(args.file).resolve()

if not file_path.suffix == ".c":
    print(f"Should only be run on a .c file!")
    exit()
if "/overlays/actors/" not in str(file_path):
    print(f"This should only be run on actors, are you sure you gave it the right file?")
    exit()

map_path = file_path.parent.parent.parent.parent.parent
map_lines = (map_path / "build" / "mm.map").read_text().splitlines()[10000:]

i = 0
while not f"{file_path.stem}.o(.text)" in map_lines[i]:
    i += 1
i += 2
assert map_lines[i-1].startswith(" .text")

orig_funcs = set()
while map_lines[i].startswith("  "):
    func = map_lines[i].split(" ")[-1]
    if not (func.endswith("_Init") or func.endswith("_Destroy") or func.endswith("_Update") or func.endswith("_Draw")):
        orig_funcs.add(func)
    i += 1

lines = file_path.read_text().splitlines()
start_func_line = 0
end_func_line = 0
func_list = set()
externs = []
extern_set = set()

i = 0
while (not (lines[i].startswith("const") or lines[i].startswith("static") or lines[i].startswith("typedef"))):
    line = lines[i]
    if line.startswith("extern"):
        extern_type = line.rsplit(" ",1)[0]
        extern_name = line.split(" ",2)[2][:-1]
        if extern_name not in extern_set:
            externs.append({"type":extern_type, "name":extern_name})
            extern_set.add(extern_name)
    i += 1

declares_needed = set()
funcs_seen = set()
funcs_types = []
for count, line in enumerate(lines):
    if not line.startswith(" ") and "(" in line and "{" in line and "static" not in line:
        func_ret = line.split(" ",1)[0]
        func_name = line.split(" ",1)[1].split("(",1)[0]
        func_args = line.split("(",1)[1].split(")",1)[0]
        funcs_seen.add(func_name)
        funcs_types.append({"ret":func_ret, "name":func_name, "args":func_args})
    else:
        for func in orig_funcs:
            if func in line and func not in funcs_seen:
                declares_needed.add(func)

externs.sort(key=lambda x: x["name"])

declares = []
for func in funcs_types:
    if func["name"] in declares_needed:
        declares.append(f"{func['ret']} {func['name']}({func['args']});")

print("\n".join(declares))
print()
print("\n".join([f"{x['type']} {x['name']};" for x in externs]))
