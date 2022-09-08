#!/usr/bin/env python3
# mzxrules 2022
# Extracts z_map_data.c data
import argparse, os, struct, math

D_801BF170_ROM = 0x1196B0
CODE_START_VRAM = 0x800A5AC0
MAP_DATA_DATA_START = 0x801BED40
MAP_DATA_DATA_END = 0x801BF550

typeInfo = {
    "Color_RGBA8" : [ 0x04, ">BBBB", "{{ {0}, {1}, {2}, {3} }}" ],
    "T_801BED4C" : [ 0x0C, ">IBBBBBBh", "{{ D_{0:08X}, {1}, {2}, {3}, {4}, 0x{5:02X}, 0x{6:02X}, {7} }}"],
    "T_801BF170" : [ 0x0A, ">BBhhBBh", "{{ {0}, {1}, {2}, {3}, 0x{4:02X}, 0x{5:02X}, {6} }}"],
    "s32" : [ 0x04, ">I", "0x{0:02X}"]
}

script_dir = os.path.dirname(os.path.realpath(__file__))
repo = script_dir + os.sep +  ".." + os.sep + ".." + os.sep

def GetCodeOff(vram):
    return vram-CODE_START_VRAM

def GetDataOff(vram):
    return vram-MAP_DATA_DATA_START

def dumpList(data, vram, keyword, typeKey, varName, length):
    if keyword is None:
        keyword = ""
    else: 
        keyword = f"{keyword} "
    cstr = f"{keyword}{typeKey} {varName}[{length}] = {{\n"
    
    ty = typeInfo[typeKey]
    off = GetDataOff(vram)
    for i in range(length):
        val = struct.unpack_from(ty[1], data, off)
        off += ty[0]
        cstr += f"    {ty[2].format(*val)},\n"
    cstr += "};\n"

    return cstr


def dump():
    data = []
    cstr = ""
    with open(repo + "baserom/code","rb") as codefile:
        codefile.seek(GetCodeOff(MAP_DATA_DATA_START))
        data = codefile.read(MAP_DATA_DATA_END - MAP_DATA_DATA_START)

    cstr += dumpList(data, 0x801BED40, "static", "Color_RGBA8", "D_801BED40", 3)
    cstr += dumpList(data, 0x801BED4C, "static", "T_801BED4C", "D_801BED4C", 5)
    cstr += dumpList(data, 0x801BED88, "static", "T_801BF170", "D_801BED88", 0x62)
    cstr += dumpList(data, 0x801BF15C, "static", "s32", "D_801BF15C", 5)
    cstr += dumpList(data, 0x801BF170, "static", "T_801BF170", "D_801BF170", 0x3A)
    cstr += dumpList(data, 0x801BF3B4, "static", "s32", "D_801BF3B4", 5)
    cstr += dumpList(data, 0x801BF3C8, "static", "s32", "D_801BF3C8", 0x62)

    print(cstr)

parser = argparse.ArgumentParser(description="Extracts z_map_data.data")
args = parser.parse_args()

dump()