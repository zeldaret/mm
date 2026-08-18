# SPDX-FileCopyrightText: 2023-2024 Max Bebök (HailToDodongo), Fig, Thar0, Dragorn421
# SPDX-License-Identifier: CC0-1.0

# Derived from
# https://github.com/HailToDodongo/oot/blob/daea8bacb27425a7dd8923dea6e0467ba68d1047/gdb_script.py
# https://github.com/fig02/gdb-load-ovl ( https://github.com/fig02/gdb-load-ovl/tree/327147060af067c4e2ff4793b4d46249afeab161 )

# Once loaded, this script provides a command `ovl`,
# that allows loading into gdb a z64 overlay *that is already loaded in-game*.
# For loading the pause menu overlay: `ovl PAUSE` or `ovl KALEIDO` or `ovl KALEIDO_SCOPE`
# Examples: `ovl ACTOR_PLAYER`, `ovl ACTOR_EN_DAIKU`, `ovl GAMESTATE_MAP_SELECT`, `ovl EFFECT_SS_DUST`
# The z64 overlays can also be loaded automatically as they're loaded by the game with `ovl auto on`

import enum
from pathlib import Path
import re

import gdb


AUTOLOAD_ENABLED_BY_DEFAULT = False


TYPE_U32 = gdb.lookup_type("u32")
TYPE_VOIDP = gdb.lookup_type("void").pointer()


class SectionType(enum.Enum):
    TEXT = (".text", "Text")
    DATA = (".data", "Data")
    RODATA = (".rodata", "RoData")
    BSS = (".bss", "Bss")

    def __init__(self, section_name, linker_script_name):
        self.section_name = section_name
        self.linker_script_name = linker_script_name


def get_sym_addr_from_name(name: str):
    """Get a symbol's address from its name
    Raises ValueError if something goes wrong"""
    printf_out = gdb.execute(f'printf "%x", &{name}', False, True)
    try:
        return int(printf_out, 16)
    except ValueError as e:
        raise ValueError(
            f'Unexpected result for `printf "%x", &{name}`', printf_out
        ) from e


VALUE_SYM_FMT_PATTERN = re.compile(
    r"(0x[0-9a-f]+)(?: <([^+]+)(?:\+(\d+))?>)?", flags=re.IGNORECASE
)


def get_sym_name_from_addr(addr: int):
    """Get a symbol's name from its address
    Raises ValueError if there is no symbol at addr or if something goes wrong"""
    v = gdb.Value(addr).cast(TYPE_VOIDP)
    s = v.format_string(raw=True, symbols=True)
    # s is expected to be like one of:
    # 0xDEADBEEF                        (if symbol not found)
    # 0xDEADBEEF <func_DEADBEEF>        (if symbol found)
    # 0xDEADBEEF <func_DEADBEE0+15>     (if symbol not found but addr is inside a symbol)
    m = VALUE_SYM_FMT_PATTERN.fullmatch(s)
    if m is None:
        raise ValueError(f"Unexpected result for getting name of {addr:#x}", s)
    addr_str, sym_name, offset_str = m.groups()
    if addr_str.lower() != f"{addr:#x}":
        raise ValueError(
            f"Unexpected result (different addr) for getting name of {addr:#x}", s
        )
    if sym_name is None:
        raise ValueError(f"No symbol found for {addr:#x}")
    if offset_str is not None:
        assert int(offset_str) != 0, s
        raise ValueError(
            f"No symbol found for {addr:#x} (but the addr is {sym_name}+{offset_str})"
        )
    return sym_name


def get_sym_section(sym: str | int):
    """Get the name of a symbol's section
    sym can be a symbol name (str) or address (int)
    Raises ValueError if something goes wrong"""
    if isinstance(sym, int):
        sym = f"{sym:#x}"
    info_sym = gdb.execute(f"info symbol {sym}", False, True)
    # info_sym can be like
    # Play_Init in section ..code
    # Play_Init in section ..code of /home/dragorn421/Documents/oot/build/gcc/oot-gc-eu-mq-dbg.elf
    parts = info_sym.split("in section ")
    if len(parts) != 2:
        raise ValueError(f"Unexpected result for `info symbol {sym}`", info_sym)
    parts2 = parts[1].split(" of ")
    return parts2[0].strip()


INFO_FILE_LINE_PATTERN = re.compile(
    "(0x[0-9a-f]+) - (0x[0-9a-f]+) is (.*)", re.IGNORECASE
)


def get_section_by_addr(addr: int):
    """get the name of the section at an address
    Raises ValueError if no section is found"""
    info_file = gdb.execute("info file", False, True)
    lines = info_file.splitlines()
    # Most lines look like:
    # \t0x00000000 - 0x00001060 is ..makerom
    # \t0x00001060 - 0x00001060 is ..makerom.bss
    # \t0xffffffff80000460 - 0xffffffff80010aa0 is ..boot
    # \t0xffffffff80010aa0 - 0xffffffff800155b0 is ..boot.bss
    # Other lines can be ignored
    for line in lines:
        m = INFO_FILE_LINE_PATTERN.fullmatch(line)
        if m is None:
            continue
        start_str, end_str, section = m.groups()
        start = int(start_str, 16)
        end = int(end_str, 16)
        start &= 0xFFFF_FFFF
        end &= 0xFFFF_FFFF
        if start <= addr < end:
            return section
    raise ValueError(f"No section found for address {addr:#x}")


# address to object-path map, used to unload entire .o files by an address
loaded_z64overlay_objects: dict[int, Path] = {}


def get_section_address(ovl_name, section_name):
    section_start_name = "_" + ovl_name + "Segment" + section_name + "Start"
    try:
        return get_sym_addr_from_name(section_start_name)
    except Exception as e:
        e.add_note(f"{section_start_name=}")
        raise


def load_z64overlay_object(alloc_address: int, vram_address: int):
    if alloc_address in loaded_z64overlay_objects:
        raise Exception("Already loaded")

    try:
        ovl_sec_name = get_sym_section(vram_address)
    except ValueError:
        print("get_sym_section() failed, trying get_section_by_addr()")
        ovl_sec_name = get_section_by_addr(vram_address)

    ovl_sec_name = ovl_sec_name.removeprefix("..")

    ovl_addresses = {
        sec: get_section_address(ovl_sec_name, sec.linker_script_name)
        for sec in SectionType
    }

    ovl_offsets = {
        sec: alloc_address + (ovl_addresses[sec] - vram_address) for sec in SectionType
    }

    # get full object-file path that contains the first symbol
    target_filename_c = gdb.lookup_symbol(get_sym_name_from_addr(vram_address))[
        0
    ].symtab.filename
    rom_elf_filename = gdb.current_progspace().filename
    target_filename_o_p = (
        Path(rom_elf_filename).parent / target_filename_c
    ).with_suffix(".o")

    loaded_z64overlay_objects[alloc_address] = target_filename_o_p
    print("Reading " + target_filename_o_p.stem + "...")

    gdb.execute(
        "add-symbol-file -readnow "
        + str(target_filename_o_p)
        + " -o 0xFF000000"
        + "".join(
            f" -s {sec.section_name} {ovl_offsets[sec]:#x}" for sec in SectionType
        ),
        False,
        True,
    )

    print("Complete.")


def unload_z64overlay_object(alloc_address: int):
    if alloc_address in loaded_z64overlay_objects:
        obj_p = loaded_z64overlay_objects[alloc_address]
        del loaded_z64overlay_objects[alloc_address]
        print(
            f"Unloading overlay: {obj_p.stem}",
            f"({len(loaded_z64overlay_objects)} left)",
        )
        gdb.execute(f"remove-symbol-file {obj_p}", False, False)


def load_z64overlay_object_from_table(overlay_table, index):
    alloc_address = int(overlay_table[index]["loadedRamAddr"].cast(TYPE_U32))

    if alloc_address == 0:
        print("ERROR: Requested overlay is not currently loaded")
        return

    vram_address = int(overlay_table[index]["vramStart"].cast(TYPE_U32))

    load_z64overlay_object(alloc_address, vram_address)


class LoadZ64OvlCmd(gdb.Command):
    def __init__(self):
        super().__init__("ovl", gdb.COMMAND_DATA, gdb.COMPLETE_EXPRESSION)

    def invoke(self, arg, from_tty):
        arg = arg.upper()

        if arg == "AUTO ON":
            bp_load.enabled = True
            print("z64 overlays will be automatically loaded")
            return
        if arg == "AUTO OFF":
            bp_load.enabled = False
            print("z64 overlays will NOT be automatically loaded")
            return

        if arg in {"PAUSE", "KALEIDO", "KALEIDO_SCOPE"}:
            # Pause menu does not have an enum, special case it. Index is 0 in `gKaleidoMgrOverlayTable`
            table = gdb.lookup_global_symbol("gKaleidoMgrOverlayTable").value()
            load_z64overlay_object_from_table(table, 0)
        elif arg == "ACTOR_PLAYER":
            # Player's index does not correspond to his actor ID, Special case it. Index is 1 in `gKaleidoMgrOverlayTable`
            table = gdb.lookup_global_symbol("gKaleidoMgrOverlayTable").value()
            load_z64overlay_object_from_table(table, 1)
        else:
            pattern = r"^([^_]+)"
            matches = re.findall(pattern, arg)
            ovl_type = matches[0]

            if ovl_type == "GAMESTATE":
                table = gdb.lookup_global_symbol("gGameStateOverlayTable").value()
            elif ovl_type == "ACTOR":
                table = gdb.lookup_global_symbol("gActorOverlayTable").value()
            elif ovl_type == "EFFECT":
                table = gdb.lookup_global_symbol("gEffectSsOverlayTable").value()
            else:
                print("ERROR: Type of enum provided is not supported")
                return

            # try to get the index from the elf via gdb
            try:
                index = gdb.lookup_symbol(arg)[0].value().cast(TYPE_U32)
            except:
                print("ERROR: Provided enum value could not be found in the elf")
                return

            load_z64overlay_object_from_table(table, index)


LoadZ64OvlCmd()


class BreakpointOverlayLoad(gdb.Breakpoint):
    def stop(self):
        frame = gdb.selected_frame()

        alloc_address = int(frame.read_var("allocatedRamAddr").cast(TYPE_U32))
        vram_address = int(frame.read_var("vramStart").cast(TYPE_U32))

        load_z64overlay_object(alloc_address, vram_address)

        return False


class BreakpointFree(gdb.Breakpoint):
    def stop(self):
        frame = gdb.selected_frame()
        # The following error
        # ValueError: Variable 'ptr' not found.
        # means the Free function was not compiled with debug flags (e.g. -Og -g)
        ptr = int(frame.read_var("ptr").cast(TYPE_U32))
        unload_z64overlay_object(ptr)
        return False


class BreakpointKaleidoFree(gdb.Breakpoint):
    def stop(self):
        frame = gdb.selected_frame()
        ptr = int(frame.read_var("ovl")["loadedRamAddr"].cast(TYPE_U32))
        unload_z64overlay_object(ptr)
        return False


bp_load = BreakpointOverlayLoad("Overlay_Load")
bp_load.silent = True
bp_load.enabled = AUTOLOAD_ENABLED_BY_DEFAULT

bp_free = BreakpointFree("ZeldaArena_Free")
bp_free.silent = True

bp_system_free = BreakpointFree("free")
bp_system_free.silent = True

bp_kaleido = BreakpointKaleidoFree("KaleidoManager_ClearOvl")
bp_kaleido.silent = True
