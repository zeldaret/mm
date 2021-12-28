#!/usr/bin/env python3

import argparse
from pathlib import Path
import glob
import xml.etree.ElementTree as xml
import re

def get_new_name(object_name, symbol_type, symbol_lookup):
    match symbol_type:
        case "AnimationHeader":
            return (f"{object_name}_Anim_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")
        case "TexturePtr":
            return (f"{object_name}_Tex_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")
        case "Gfx":
            return (f"{object_name}_DL_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")
        case "SkeletonHeader" | "FlexSkeletonHeader":
            return (f"{object_name}_Skel_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")
        case "CollisionHeader":
            return (f"{object_name}_Colheader_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")
        case "Vtx":
            return (f"{object_name}_Vtx_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")
        case _:
            return (f"{object_name}_Blob_{symbol_lookup:06X}", f"0x{symbol_lookup:X}")

def make_element_string(symbol_type, name, offset):
    match symbol_type:
        case "AnimationHeader":
            return f"<Animation Name=\"{name}\" Offset=\"{offset}\" />"
        case "TexturePtr":
            return f"<Texture Name=\"{name}\" OutName=\"tex_{name.rsplit('_',1)[1]}\" Format=\"rgba16\" Width=\"0\" Height=\"0\" Offset=\"{offset}\" />"
        case "Gfx":
            return f"<DList Name=\"{name}\" Offset=\"{offset}\" />"
        case "SkeletonHeader":
            return f"<Skeleton Name=\"{name}\" Type=\"Normal\" LimbType=\"Standard\" Offset=\"{offset}\" />"
        case "FlexSkeletonHeader":
            return f"<Skeleton Name=\"{name}\" Type=\"Flex\" LimbType=\"Standard\" Offset=\"{offset}\" />"
        case "CollisionHeader":
            return f"<Collision Name=\"{name}\" Offset=\"{offset}\" />"
        case "Vtx":
            out = f"<Array Name=\"{name}\" Count=\"0\" Offset=\"{offset}\" />\n"
            out += f"        <Vtx/>\n"
            out += f"    </Array>"
            return out
        case _:
            return f"<Blob Name=\"{name}\" Size=\"0\" Offset=\"{offset}\" />"
    return f"<Blob Name=\"{name}\" Size=\"0\" Offset=\"{offset}\" />"

def get_object_file(object_name):
    if object_name == "":
        return None
    # objects can have weird capitalisation, so try to fix it
    object_xml_path = Path(__file__).parent.resolve() / "assets" / "xml" / "objects" / f"{object_name}.xml"
    if not object_xml_path.exists():
        for f in (Path(__file__).parent.resolve() / "assets" / "xml" / "objects").iterdir():
            if f.stem.lower() == object_name:
                object_name = f.stem
                object_xml_path = Path(__file__).parent.resolve() / "assets" / "xml" / "objects" / f"{f.stem}.xml"

    if not object_xml_path.exists():
        print(f"Failed to find XML file for {object_name}")
        print(f"Assumed path: {object_xml_path}")
        exit()

    tree = xml.parse(object_xml_path, parser=xml.XMLParser(target=xml.TreeBuilder(insert_comments=True)))
    root = tree.getroot()[0]
    xml_entries = list(root)
    return xml_entries


XML_DATA = {
    "gameplay_keep":get_object_file("gameplay_keep"),
    "gameplay_field_keep":get_object_file("gameplay_field_keep"),
    "gameplay_dangeon_keep":get_object_file("gameplay_dangeon_keep"),
}

def find_xml_entry(xml_entries, symbol_name, symbol_lookup, symbol_type, object_name, to_replace, to_replace_set):
    if symbol_name.startswith ("0"):
        symbol_name = f"D_{symbol_name}"

    for entry in xml_entries:
        if len(entry.attrib.keys()) == 0:
            # comments
            try:
                lookup = int(entry.text.split("Offset=\"",1)[1].split("\"")[0], 16)
            except Exception:
                continue
        else:
            lookup = int(entry.attrib["Offset"], 16)

        if lookup == symbol_lookup:
            #print(f"{hex(symbol_lookup)} matches entry {entry.attrib}")
            if "Name" not in entry.attrib:
                #Matches a comment offset
                if symbol_name not in to_replace_set:
                    if symbol_type.startswith("UNK_"):
                        print(f"\tUNK {symbol_name}")
                    else:
                        name, offset = get_new_name(object_name, symbol_type, symbol_lookup)
                        to_add.append(make_element_string(symbol_type, name, offset))
                        to_replace.append((symbol_name, name))
                    to_replace_set.add(symbol_name)
            else:
                if symbol_name not in to_replace_set:
                    to_replace.append((symbol_name, entry.attrib["Name"]))
                    to_replace_set.add(symbol_name)
            break
    else:
        return False, to_replace, to_replace_set

    return True, to_replace, to_replace_set

sym_regex = re.compile(r"D_(0[^8][0-9a-fA-F]{6})[^_]?")

dm_stk = {
        f"0601C21C" : "object_stk",
        f"0601D3D0" : "object_stk",
        f"06001030" : "object_stk",
        f"0601D008" : "object_stk",
        f"0601D008" : "object_stk",
        f"06015C14" : "object_stk",
        f"0600BB2C" : "object_stk",
        f"0600C964" : "object_stk",
        f"06002774" : "object_stk",
        f"06003068" : "object_stk",

        f"060070DC" : "object_stk2",
        f"0600D830" : "object_stk2",
        f"0600055C" : "object_stk2",
        f"0600130C" : "object_stk2",
        f"0600C270" : "object_stk2",
        f"0600CBB8" : "object_stk2",
        f"0601AA80" : "object_stk2",
        f"0601D07C" : "object_stk2",
        f"06016910" : "object_stk2",
        f"06018ED0" : "object_stk2",
        f"0601DDE0" : "object_stk2",
        f"0601EF50" : "object_stk2",
        f"0602DC64" : "object_stk2",
        f"0602E9A0" : "object_stk2",
        f"0602DC64" : "object_stk2",
        f"0602E9A0" : "object_stk2",
        f"060035C8" : "object_stk2",
        f"060049C8" : "object_stk2",
        f"060259F4" : "object_stk2",
        f"060266C8" : "object_stk2",
        f"06026CF4" : "object_stk2",
        f"0601C114" : "object_stk2",
        f"06004580" : "object_stk2",
        f"06020CAC" : "object_stk2",
        f"0602200C" : "object_stk2",
        f"0602336C" : "object_stk2",
        f"060101A4" : "object_stk2",
        f"06010B60" : "object_stk2",
        f"0602A2D8" : "object_stk2",
        f"0601F9E4" : "object_stk2",
        f"06029A04" : "object_stk2",
        f"0602AD54" : "object_stk2",
        f"060110B4" : "object_stk2",
        f"06011FB0" : "object_stk2",
        f"06012A58" : "object_stk2",
        f"060141E4" : "object_stk2",
        f"0600E6EC" : "object_stk2",
        f"0600EEC0" : "object_stk2",
        f"06027CF4" : "object_stk2",
        f"06028F28" : "object_stk2",
        f"0603323C" : "object_stk2",
        f"06031210" : "object_stk2",
        f"060322FC" : "object_stk2",
        f"06032AE0" : "object_stk2",
        f"0603021C" : "object_stk2",
        f"06036964" : "object_stk2",
        f"06016508" : "object_stk2",
        f"06015028" : "object_stk2",
        f"06014920" : "object_stk2",
        f"0602FA70" : "object_stk2",
        f"06037B94" : "object_stk2",
        f"0603967C" : "object_stk2",
        f"0603967C" : "object_stk2",
        f"0603A8F8" : "object_stk2",
        f"06034FD8" : "object_stk2",

        f"06005F44" : "object_stk3",
        f"06002CD8" : "object_stk3",
        f"060039F0" : "object_stk3",
        f"06004554" : "object_stk3",
        f"060051C0" : "object_stk3",
        f"06001374" : "object_stk3",
        f"06001EDC" : "object_stk3",
}

XML_DATA[f"object_stk"] = get_object_file(f"object_stk")
XML_DATA[f"object_stk2"] = get_object_file(f"object_stk2")
XML_DATA[f"object_stk3"] = get_object_file(f"object_stk3")

for file in glob.iglob("src/overlays/actors/**/*.c", recursive=True):
    if "/effects/" in file:
        continue
    if "dm_stk." not in file:
        continue
    #print(file)

    with open(file, "r") as f:
        fd_ = f.read()
        fd = fd_.splitlines()

    if fd_.count("#pragma GLOBAL_ASM") > 3:
        # bad heuristic for skipping un-decomped files
        continue

    object_name = ""
    for i,line in enumerate(fd):
        if line.endswith("_InitVars = {"):
            _, type, name, *_ = fd[i].split(" ")
            if "Effect" in type:
                object_name = fd[i+1].strip()[:-1].lower()
            elif "Actor" in type:
                object_name = fd[i+4].strip()[:-1].lower()
            break

    skip_object_syms = False
    #if fd_.find("Object_GetIndex") >= 0 or fd_.find("Object_IsLoaded") >= 0:
    #    print(file, object_name)
    #    print(f"HANDLE OBJECTS HERE MANUALLY!")
    #    print()
    #    skip_object_syms = True
    #    continue

    if object_name:
        print(file, object_name)
    else:
        print(f"No object found: {file}")

    XML_DATA[object_name] = get_object_file(f"object_stk") + get_object_file(f"object_stk2") + get_object_file(f"object_stk3")

    to_replace = []
    to_replace_set = set()
    to_add = []
    new_fd = []
    includes_needed = set()

    for i,line in enumerate(fd):
        add_line = True;

        syms = re.findall(sym_regex, line)

        for sym in syms:
            symbol_type = "UNK_PTR"
            if line.startswith("extern ") and ";" in line:
                _, symbol_type, symbol_name = line.split(";",1)[0].split(" ")
                symbol_name = re.findall(sym_regex, symbol_name)[0]

                #new_lookup = -1
                #if " // " in line and line.split(" // ",1)[1].find(" ") == -1:
                #    new_lookup = int(symbol_name, 16)
                #    symbol_name = line.split(" // ")[1]
                add_line = False
            else:
                symbol_name = sym

            #print(symbol_name, symbol_type)
            #if new_lookup >= 0:
            #    symbol_lookup = new_lookup
            #else:
            #    symbol_lookup = int(symbol_name, 16)
            symbol_lookup = int(symbol_name, 16)

            is_type_5 = False
            if symbol_lookup >= 0x04000000 and symbol_lookup < 0x05000000:
                # gameplay_keep
                xml_entries = XML_DATA["gameplay_keep"]
                symbol_lookup -= 0x04000000
                includes_needed.add("gameplay_keep")
            elif symbol_lookup >= 0x05000000 and symbol_lookup < 0x06000000:
                # gameplay_field_keep or gamepaly_dangeon_keep
                xml_entries = XML_DATA["gameplay_field_keep"]
                symbol_lookup -= 0x05000000
                is_type_5 = True
            elif symbol_lookup >= 0x06000000 and symbol_lookup < 0x07000000:
                if object_name == "":
                    print(f"Object name is empty, skipping {symbol_name}")
                    continue
                elif skip_object_syms:
                    continue
                if sym in dm_stk:
                    xml_entries = XML_DATA[dm_stk[sym]]
                else:
                    xml_entries = XML_DATA[object_name]
                symbol_lookup -= 0x06000000
                includes_needed.add(object_name)
            else:
                print(f"Skipping {symbol_name}")
                continue

            found, to_replace, to_replace_set = find_xml_entry(xml_entries, symbol_name, symbol_lookup, symbol_type, object_name, to_replace, to_replace_set)
            if found and is_type_5:
                includes_needed.add("gameplay_field_keep")

            if not found and is_type_5:
                xml_entries = XML_DATA["gameplay_dangeon_keep"]
                found, to_replace, to_replace_set = find_xml_entry(xml_entries, symbol_name, symbol_lookup, symbol_type, object_name, to_replace, to_replace_set)
                
                if found and is_type_5:
                    includes_needed.add("gameplay_dangeon_keep")

            if not found:
                symbol_name = f"D_{symbol_name}"
                if symbol_name not in to_replace_set:
                    if symbol_type.startswith("UNK_"):
                        print(f"\tUNK {symbol_name}")
                    else:
                        name, offset = get_new_name(object_name, symbol_type, symbol_lookup)
                        to_add.append(make_element_string(symbol_type, name, offset))
                        to_replace.append((symbol_name, name))
                    to_replace_set.add(symbol_name)

        if add_line:
            new_fd.append(line)

    del XML_DATA[object_name]

    if len(to_replace) > 0:
        need_include = True
        include_set = False
        last_include = -1

        for i,line in enumerate(fd):
            if line.startswith("#include"):
                last_include = i
                new_inc = includes_needed
                for include in includes_needed:
                    if f"objects/{include}" in line:
                        new_inc.remove(include)
                includes_needed = new_inc

        for include in includes_needed:
            new_fd.insert(last_include + 1, f"#include \"objects/{include}/{include}.h\"")

    new_fd = "\n".join(new_fd)
    for replace in to_replace:
        new_fd = new_fd.replace(replace[0], replace[1])

    with open(file, "w") as f:
        f.write(new_fd)

    if len(to_add) > 0:
        to_add.sort(key=lambda x: int(x.split("Offset=\"", 1)[1].split("\"")[0], 16))
        print(f"New entries to the XML:")
        [print(f"\t{entry}") for entry in to_add]
    print()

    #print(new_fd)
