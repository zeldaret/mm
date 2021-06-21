#!/usr/bin/env python3
import os, argparse, json, re, csv, git

parser = argparse.ArgumentParser()

parser = argparse.ArgumentParser(description="Computes current progress throughout the whole project.")
parser.add_argument("format", nargs="?", default="text", choices=["text", "csv", "shield-json"])
parser.add_argument("-m", "--matching", dest='matching', action='store_true',
                    help="Output matching progress instead of decompilation progress")
args = parser.parse_args()

NON_MATCHING_PATTERN = r"#ifdef\s+NON_MATCHING.*?#pragma\s+GLOBAL_ASM\s*\(\s*\"(.*?)\"\s*\).*?#endif"
NOT_ATTEMPTED_PATTERN = r"#pragma\s+GLOBAL_ASM\s*\(\s*\"(.*?)\"\s*\)"

def GetFunctionsByPattern(pattern, files):
    functions = []

    for file in files:
        with open(file) as f:
            functions += re.findall(pattern, f.read(), re.DOTALL)

    return functions

def ReadAllLines(fileName):
    line_list = list()
    with open(fileName) as f:
        line_list = f.readlines()

    return line_list

def GetFiles(path, ext):
    files = []

    for r, d, f in os.walk(path):
        for file in f:
            if file.endswith(ext):
                files.append(os.path.join(r, file))

    return files

def GetRemovableSize(functions_to_count, path):
    size = 0

    asm_files = GetFiles(path, ".asm")

    for asm_file_path in asm_files:
        file_size = 0
        if asm_file_path in functions_to_count:
            asm_lines = ReadAllLines(asm_file_path)

            for asm_line in asm_lines:
                if (asm_line[0:2] == "/*" and asm_line[30:32] == "*/"):
                    file_size += 4

        size += file_size

    return size

map_file = ReadAllLines('build/mm.map')

# Get list of Non-Matchings
all_files = GetFiles("src", ".c")
non_matching_functions = GetFunctionsByPattern(NON_MATCHING_PATTERN, all_files)

# Get list of functions not attempted.
not_attempted_functions = GetFunctionsByPattern(NOT_ATTEMPTED_PATTERN, all_files)
not_attempted_functions = list(set(not_attempted_functions).difference(non_matching_functions))

# If we are looking for a count that includes non-matchings, then we want to set non matching functions list to empty.
# We want to do this after not attempted functions list generation so we can remove all non matchings.
if not args.matching:
    non_matching_functions = []

# Get asset files
audio_files = GetFiles("baserom/assets/audio", "")
misc_files = GetFiles("baserom/assets/misc", "")
object_files = GetFiles("baserom/assets/objects", "")
scene_files = GetFiles("baserom/assets/scenes", "")
texture_files = GetFiles("baserom/assets/textures", "")

# Initialize all the code values
src = 0
src_code = 0
src_boot = 0
src_ovl = 0
src_libultra = 0
asm = 0
asm_code = 0
asm_boot = 0
asm_ovl = 0
asm_libultra = 0
audio = 0
misc = 0
object_ = 0
scene = 0
texture = 0

for line in map_file:
    line_split =  list(filter(None, line.split(" ")))

    if (len(line_split) == 4 and line_split[0].startswith(".")):
        section = line_split[0]
        file_size = int(line_split[2], 16)
        obj_file = line_split[3]

        if (section == ".text"):
            if (obj_file.startswith("build/src")):
                if (obj_file.startswith("build/src/code")):
                    src_code += file_size
                elif (obj_file.startswith("build/src/libultra")):
                    src_libultra += file_size
                elif (obj_file.startswith("build/src/boot")):
                    src_boot += file_size
                elif (obj_file.startswith("build/src/overlays")):
                    src_ovl += file_size
            elif (obj_file.startswith("build/asm")):
                if (obj_file.startswith("build/asm/code")):
                    asm_code += file_size
                elif (obj_file.startswith("build/asm/libultra")):
                    asm_libultra += file_size
                elif (obj_file.startswith("build/asm/boot")):
                    asm_boot += file_size
                elif (obj_file.startswith("build/asm/overlays")):
                    asm_ovl += file_size

        if (section == ".data"):
            if (obj_file.startswith("build/assets/audio")):
                audio += file_size
            elif (obj_file.startswith("build/assets/misc")):
                misc += file_size
            elif (obj_file.startswith("build/assets/objects")):
                object_ += file_size
            elif (obj_file.startswith("build/assets/scenes")):
                scene += file_size
            elif (obj_file.startswith("build/assets/textures")):
                texture += file_size

# Add libultra to boot.
src_boot += src_libultra
asm_boot += asm_libultra

# Calculate Non-Matching
non_matching_asm_ovl = GetRemovableSize(non_matching_functions, "./asm/non_matchings/overlays")
non_matching_asm_code = GetRemovableSize(non_matching_functions, "./asm/non_matchings/code")
non_matching_asm_boot = GetRemovableSize(non_matching_functions, "./asm/non_matchings/boot")

# Calculate Not Attempted
not_attempted_asm_ovl = GetRemovableSize(not_attempted_functions, "./asm/non_matchings/overlays")
not_attempted_asm_code = GetRemovableSize(not_attempted_functions, "./asm/non_matchings/code")
not_attempted_asm_boot = GetRemovableSize(not_attempted_functions, "./asm/non_matchings/boot")

# All the non matching asm is the sum of non-matching code
non_matching_asm = non_matching_asm_ovl + non_matching_asm_code + non_matching_asm_boot

# All the not attempted asm is the sum of not attemped code
not_attempted_asm = not_attempted_asm_ovl + not_attempted_asm_code + not_attempted_asm_boot

# Calculate total decompiled for each bucket by taking out the non-matching and not attempted in ovl/code/boot buckets.
code = src_code - (non_matching_asm_code + not_attempted_asm_code)
boot = src_boot - (non_matching_asm_boot + not_attempted_asm_boot)
ovl = src_ovl - (non_matching_asm_ovl + not_attempted_asm_ovl)

# Total code bucket sizes
code_size = src_code + asm_code
boot_size = src_boot + asm_boot
ovl_size = src_ovl + asm_ovl
handwritten = 0 # Currently unsure of any handwritten asm in MM

# Calculate size of all assets
audio_size = 0
misc_size = 0
object_size = 0
scene_size = 0
texture_size = 0
for f in audio_files:
    audio_size += os.stat(f).st_size
for f in misc_files:
    misc_size += os.stat(f).st_size
for f in object_files:
    object_size += os.stat(f).st_size
for f in scene_files:
    scene_size += os.stat(f).st_size
for f in texture_files:
    texture_size += os.stat(f).st_size

# Calculate asm and src totals
src = src_code + src_boot + src_ovl
asm = asm_code + asm_boot + asm_ovl

# Take out the non-matchings and not attempted in grand totals
src -= non_matching_asm + not_attempted_asm
asm += non_matching_asm + not_attempted_asm

# Calculate the total amount of decompilable code
total = src + asm

# Convert vaules to percentages
src_percent = 100 * src / total
asm_percent = 100 * asm / total
code_percent = 100 * code / code_size
boot_percent = 100 * boot / boot_size
ovl_percent = 100 * ovl / ovl_size
audio_percent = 100 * audio / audio_size
misc_percent = 100 * misc / misc_size
object_percent = 100 * object_ / object_size
scene_percent = 100 * scene / scene_size
texture_percent = 100 * texture / texture_size

# convert bytes to masks and rupees
num_masks = 24
max_rupees = 500
bytes_per_mask = total / num_masks
bytes_per_rupee = bytes_per_mask / max_rupees
masks = int(src / bytes_per_mask)
rupees = int((src % bytes_per_mask) / bytes_per_rupee)

# Debug print statements for the values
#print("Total: ", total)
#print("src: ", src)
#print("asm: ", asm)
#print("")
#print("src_code: ", src_code)
#print("src_boot: ", src_boot)
#print("src_ovl: ", src_ovl)
#print("")
#print("asm_code: ", asm_code)
#print("asm_boot: ", asm_boot)
#print("asm_ovl: ", asm_ovl)
#print("")
#print("Nonmatching code: ", non_matching_asm_code)
#print("Nonmatching boot: ", non_matching_asm_boot)
#print("Nonmatching ovl: ", non_matching_asm_ovl)
#print("")
#print("Not attempted code: ", not_attempted_asm_code)
#print("Not attempted boot: ", not_attempted_asm_boot)
#print("Not attempted ovl: ", not_attempted_asm_ovl)
#print("")
#print("code_size: ", code_size)
#print("boot_size: ", boot_size)
#print("ovl_size: ", ovl_size)
#print("")
#print("code: ", code)
#print("boot: ", boot)
#print("ovl: ", ovl)
#print("")

if args.format == 'csv':
    version = 1
    git_object = git.Repo().head.object
    timestamp = str(git_object.committed_date)
    git_hash = git_object.hexsha
    csv_list = [str(version), timestamp, git_hash, str(code), str(code_size), str(boot), str(boot_size),
                str(ovl), str(ovl_size), str(src), str(asm), str(len(non_matching_functions)),
                str(audio), str(audio_size), str(misc), str(misc_size), str(object_), str(object_size),
                str(scene), str(scene_size), str(texture), str(texture_size)]

    print(",".join(csv_list))
elif args.format == 'shield-json':
    # https://shields.io/endpoint
    print(json.dumps({
        "schemaVersion": 1,
        "label": "progress",
        "message": f"{src_percent:.3g}%",
        "color": 'yellow',
    }))
elif args.format == 'text':
    adjective = "decompiled" if not args.matching else "matched"

    print(str(total) + " total bytes of decompilable code\n")
    print(str(src) + " bytes " + adjective + " in src " + str(src_percent) + "%\n")
    print(str(boot) + "/" + str(boot_size) + " bytes " + adjective + " in boot " + str(boot_percent) + "%\n")
    print(str(code) + "/" + str(code_size) + " bytes " + adjective + " in code " + str(code_percent) + "%\n")
    print(str(ovl) + "/" + str(ovl_size) + " bytes " + adjective + " in overlays " + str(ovl_percent) + "%\n")
    print(str(audio) + "/" + str(audio_size) + " bytes reconstructed in audio " + str(audio_percent) + "%\n")
    print(str(misc) + "/" + str(misc_size) + " bytes reconstructed in misc " + str(misc_percent) + "%\n")
    print(str(object_) + "/" + str(object_size) + " bytes reconstructed in objects " + str(object_percent) + "%\n")
    print(str(scene) + "/" + str(scene_size) + " bytes reconstructed in scenes " + str(scene_percent) + "%\n")
    print(str(texture) + "/" + str(texture_size) + " bytes reconstructed in textures " + str(texture_percent) + "%\n")
    print("------------------------------------\n")

    if (rupees > 0):
        print('You have {}/{} masks and {}/{} rupee(s).\n'.format(masks, num_masks, rupees, max_rupees))
    else:
        print('You have {}/{} masks.\n'.format(masks, num_masks))
else:
    print("Unknown format argument: " + args.format)