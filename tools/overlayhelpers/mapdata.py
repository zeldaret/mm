#!/usr/bin/env python3
# mzxrules 2022
# Extracts z_map_data.c data
import argparse, os, struct, math

map_i_static_Info_ROM = 0x1196B0
CODE_START_VRAM = 0x800A5AC0
MAP_DATA_DATA_START = 0x801BED40
MAP_DATA_DATA_END = 0x801BF550

typeInfo = {
    "Color_RGBA8" : [ 0x04, ">BBBB", "{{ {0}, {1}, {2}, {3} }}" ],
    "MapSpriteInfo2" : [ 0x0C, ">IBBBBBBh", "{{ D_{0:08X}, {1}, {2}, {3}, {4}, MAPDATA_DRAW_{5}, {6}, {7} }}"],
    "MapSpriteInfo" : [ 0x0A, ">BBhhBBh", "{{ {0}, {1}, {2}, {3}, MAPDATA_DRAW_{4}, {5}, {6} }}"],
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

def dumpMapGrandStatic(data, vram, typeKey, length):
    xmlStr = "\n"
    ty = typeInfo[typeKey]
    off = GetDataOff(vram)
    mapId = 0x100
    textureOff = 0

    for i in range(length):
        val = struct.unpack_from(ty[1], data, off)
        off += ty[0]
        textureWidth = val[0]
        textureHeight = val[1]

        xmlStr += f'    <Texture Name="map_grand_static_{mapId:X}" OutName="map_{mapId:X}" Format="i4" Width="{textureWidth}" Height="{textureHeight}" Offset="0x{textureOff:X}" />\n'
        # inc cursors

        textureOff += textureWidth * textureHeight // 2
        textureOff = ((textureOff + 0xF) // 0x10) * 0x10
        mapId += 1


    xmlStr += "};\n"
    return xmlStr

def dumpMapIStatic(data, vram, typeKey, length):
    xmlStr = "\n"
    ty = typeInfo[typeKey]
    off = GetDataOff(vram)
    mapId = 0x0
    textureOff = 0

    for i in range(length):
        val = struct.unpack_from(ty[1], data, off)
        off += ty[0]
        textureWidth = val[0]
        textureHeight = val[1]

        xmlStr += f'    <Texture Name="map_i_static_{mapId:02X}" OutName="map_{mapId:02X}" Format="i4" Width="{textureWidth}" Height="{textureHeight}" Offset="0x{textureOff:X}" />\n'
        # inc cursors

        textureOff += textureWidth * textureHeight // 2
        textureOff = ((textureOff + 0xF) // 0x10) * 0x10
        mapId += 1


    xmlStr += "};\n"
    return xmlStr


def dump():
    data = []
    cstr = ""
    with open(repo + "baserom/code","rb") as codefile:
        codefile.seek(GetCodeOff(MAP_DATA_DATA_START))
        data = codefile.read(MAP_DATA_DATA_END - MAP_DATA_DATA_START)

    cstr += dumpList(data, 0x801BED40, "static", "Color_RGBA8", "mapColorTable", 3)
    cstr += dumpList(data, 0x801BED4C, "static", "MapSpriteInfo2", "gameplay_dangeon_keep_Info", 5)
    cstr += dumpList(data, 0x801BED88, "static", "MapSpriteInfo", "map_grand_static_Info", 98)
    cstr += dumpList(data, 0x801BF15C, "static", "s32", "D_801BF15C", 5)
    cstr += dumpList(data, 0x801BF170, "static", "MapSpriteInfo", "map_i_static_Info", 58)
    cstr += dumpList(data, 0x801BF3B4, "static", "s32", "map_i_for_gameplay_dangeon_keep", 5)
    cstr += dumpList(data, 0x801BF3C8, "static", "s32", "map_i_for_map_grand", 98)

    cstr += dumpMapGrandStatic(data, 0x801BED88, "MapSpriteInfo", 98)
    cstr += dumpMapIStatic(data, 0x801BF170, "MapSpriteInfo", 58)

    print(cstr)

parser = argparse.ArgumentParser(description="Extracts z_map_data.data")
args = parser.parse_args()

dump()