#!/usr/bin/env python3
import argparse, os

def split_asm_and_rodata():
    parser = argparse.ArgumentParser()

    parser.add_argument('input', help='input file')
    parser.add_argument('output', help='output file path')
    parser.add_argument('-c', '--c-base', help='create base c file that has GLOBAL_ASM for each function', metavar='file')
    args = parser.parse_args()

    os.makedirs(args.output, exist_ok=True)

    file_names = []
    rodata_entries = []
    disableRodataConvert = False

    basename = str(args.input)
    rodataFile = None

    if "ovl_" in basename:
        if "0x" in basename:
            basename = basename.split("0x")[0]
        else:
            basename = basename.split(".")[0]
    else: # files in code
        if "0x" in basename:
            basename = basename.split("code_")[-1]
        else:
            basename = basename.split("/")[-1]
        rodataFile = "asm/code/code_rodata_" + basename

    if rodataFile is None:
        rodataFile = basename + "late_rodata.asm"

    if not os.path.exists(rodataFile):
        rodataFile = basename + "rodata.asm"

    rodata_lines = []
    if os.path.exists(rodataFile) and not disableRodataConvert:
        with open(rodataFile, 'r') as f:
            rodata_lines = f.readlines()
            current_rodata = None
            for line in rodata_lines:
                if line.startswith('glabel') and not line.startswith('glabel L80'):
                    current_rodata = line.split()[1]
                    assert(current_rodata != '')
                if any([directive in line for directive in ['.byte', '.half', '.short', '.word', '.ascii', '.asciz', '.float', '.double']]):
                    rodata_entries.append([current_rodata, line, False])
            f.close()

    with open(args.input, 'r') as f:
        current_file = None
        relevant_rodata = []
        written_rodata = []
        writing = False

        lines = f.readlines()
        for line in lines:
            if line.startswith('glabel') and not line.startswith('glabel L80'):
                func_name = line.split()[1]
                assert(func_name != '')

                if current_file != None:
                    if len(relevant_rodata):
                        current_file.write("\n.section .late_rodata\n\n")
                        for entry in relevant_rodata:
                            writeLabel = True
                            for labelName in written_rodata:
                                if entry[0] == labelName:
                                    writeLabel = False
                                    break
                            if writeLabel:
                                current_file.write("glabel " + entry[0] + "\n")
                                written_rodata.append(entry[0])
                            current_file.write(entry[1])

                        if os.path.exists(rodataFile) and not disableRodataConvert:
                            with open(rodataFile, 'w+') as f:
                                f.truncate()
                                deleteLine = False
                                for xline in rodata_lines:
                                    if deleteLine:
                                        for entry in relevant_rodata:
                                                if xline.startswith('glabel') and not xline.startswith('glabel L80'):
                                                    deleteLine = False
                                                    break
                                    if xline.startswith('glabel') and not xline.startswith('glabel L80'):
                                        for labelName in written_rodata:
                                            if labelName in xline:
                                                deleteLine = True
                                                break
                                    if not deleteLine:
                                        f.writelines([xline])
                                f.close()

                    relevant_rodata = []
                    current_file.close()
                file_name = args.output + '/' + func_name + '.asm'
                current_file = open(file_name, 'w')
                writing = True
                file_names.append(file_name)

            if any([directive in line for directive in ['.byte', '.half', '.short', '.word', '.ascii', '.asciz', '.float', '.double']]):
                writing = False

            for entries in rodata_entries:
                entryLabel = entries[0]
                addRodata = True
                if not entryLabel:
                    print(args.input)
                    entryLabel = ""

                for existing_entry in relevant_rodata:
                    if existing_entry[0] == entryLabel:
                        addRodata = False
                        break

                if addRodata:
                    if entryLabel in line:
                        for xentries in rodata_entries:
                            if entryLabel == xentries[0]:
                                # Is Used
                                xentries[2] = True
                                relevant_rodata.append(xentries)
                        break
            if writing:
                current_file.write(line)

        if current_file != None:
            if len(relevant_rodata):
                current_file.write("\n.section .late_rodata\n\n")
                for entry in relevant_rodata:
                    writeLabel = True
                    for labelName in written_rodata:
                        if entry[0] == labelName:
                            writeLabel = False
                            break
                    if writeLabel:
                        current_file.write("glabel " + entry[0] + "\n")
                        written_rodata.append(entry[0])
                    current_file.write(entry[1])

                if os.path.exists(rodataFile):
                    with open(rodataFile, 'w+') as f:
                        f.truncate()
                        deleteLine = False
                        for xline in rodata_lines:
                            if deleteLine:
                                for entry in relevant_rodata:
                                        if xline.startswith('glabel') and not xline.startswith('glabel L80'):
                                            deleteLine = False
                                            break
                            if xline.startswith('glabel') and not xline.startswith('glabel L80'):
                                for labelName in written_rodata:
                                    if labelName in xline:
                                        deleteLine = True
                                        break
                            if not deleteLine:
                                f.writelines([xline])
                        f.close()

            relevant_rodata = []
            written_rodata = []
            current_file.close()

    if args.c_base != None:
        os.makedirs(os.path.dirname(args.c_base), exist_ok=True)
        with open(args.c_base, 'w') as f:
            f.write('#include <ultra64.h>\n#include <global.h>\n')

            for name in file_names:
                f.write('\n#pragma GLOBAL_ASM("{}")\n'.format(name))

rodata_excluded = ["ovl_Bg_Dkjail_Ivy", "ovl_Bg_Ikana_Mirror", "ovl_Boss_02", "ovl_Boss_07", "ovl_Boss_Hakugin", "ovl_Elf_Msg", "ovl_Elf_Msg2", "ovl_Elf_Msg3", "ovl_Elf_Msg4", "ovl_Elf_Msg5", "ovl_En_Az", "ovl_En_Bigokuta", "ovl_En_Bigpamet", "ovl_En_Bigpo", "ovl_En_Bigslime", "ovl_En_Box", "ovl_En_Butte", "ovl_En_Col_Man", "ovl_En_Crow", "ovl_En_Death", "ovl_En_Elf", "ovl_En_Elforg", "ovl_En_Encount3", "ovl_En_Encount4", "ovl_En_Fish", "ovl_En_Fish2", "ovl_En_Fsn", "ovl_En_Honotrap", "ovl_En_Horse", "ovl_En_Horse_Game", "ovl_En_Invadepoh", "ovl_En_Ishi", "ovl_En_Kame", "ovl_En_Kanban", "ovl_En_Kusa2", "ovl_En_M_Thunder", "ovl_En_Maruta", "ovl_En_Mushi2", "ovl_En_Okuta", "ovl_En_Ossan", "ovl_En_Peehat", "ovl_En_Rg", "ovl_En_Ruppecrow", "ovl_En_Slime", "ovl_En_Sob1", "ovl_En_Syateki_Man", "ovl_En_Test7", "ovl_En_Trt", "ovl_En_Wiz_Fire", "ovl_Mir_Ray", "ovl_Obj_Bombiwa", "ovl_Obj_Driftice", "ovl_Obj_Hariko", "ovl_Obj_Iceblock", "ovl_Obj_Mure", "ovl_Obj_Snowball2", "ovl_Obj_Toudai", "ovl_select"]
rodata_included = ["z_en_item00"]

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('input', help='input file')
    parser.add_argument('output', help='output file path')
    parser.add_argument('-c', '--c-base', help='create base c file that has GLOBAL_ASM for each function', metavar='file')
    args = parser.parse_args()

    os.makedirs(args.output, exist_ok=True)

    file_names = []

    if ("ovl_" in str(args.input) and not any(file in str(args.input) for file in rodata_excluded)) or any(file in str(args.input) for file in rodata_included):
        split_asm_and_rodata()
        exit(0)

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

