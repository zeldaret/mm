#!/usr/bin/env python3

import argparse, ast, math, os, re, struct
from mips_isa import *
from multiprocessing import Pool, Manager
from pathlib import Path
import copy

parser = argparse.ArgumentParser()
parser.add_argument(
    "-j", dest="jobs", type=int, default=1, help="number of processes to run at once"
)
parser.add_argument(
    "--full",
    "-f",
    dest="full",
    action="store_true",
    default=False,
    help="Decompile all files regardless of whether they are used or not",
)

args = parser.parse_args()
jobs = args.jobs

ASM_OUT = "asm/"
DATA_OUT = "data/"


def discard_decomped_files(files_spec):
    root_path = Path(__file__).parent.parent.parent

    with open(root_path / "spec", "r") as f:
        spec = f.read()
    # No need to check anything beyond here
    spec = spec[: spec.find('name "gameplay_keep"')].splitlines()[:-2]

    new_spec = []
    for f in files_spec:
        name, _, type, _, file_list = f

        # Find the beginseg for this file
        i = 0
        while i < len(spec):
            if spec[i].startswith("beginseg") and f'"{name}"' in spec[i + 1]:
                break
            i += 1

        # For every fil;e within this segment, look through the seg for lines with this file's name
        # if found, check whether it's still in build/asm/ or build/data/, in which case it's not decomped
        # if all references to it are in build/src/ then it should be ok to skip, some code/boot files are a bit different

        seg_start = i
        new_files = {}
        included = False
        saved_off = 0
        for offset, file in file_list.items():
            if file == "[PADDING]":
                continue

            # why are these not named?
            if file == "":
                file = f"{type}_{offset:08X}"
                include = True
            # flg_set_table is not in the spec, and buffers has its own section, just add them
            elif file == "flg_set_table" or "buffers" in file:
                include = True
            else:
                include = False
                i = seg_start
                last_line = ""
                while not spec[i].startswith("endseg"):
                    if f"/{file}." in spec[i]:
                        if spec[i].count(".") == 1:
                            last_line = spec[i]
                        if "build/asm/" in spec[i] or "build/data/" in spec[i]:
                            include = True
                            break
                    i += 1
                else:
                    # Many code/boot files only have a single section (i.e .text)
                    # In that case it will be inside build/src/ and pragma in the asm
                    # For these files, open the source and look for the pragmas to be sure
                    # Overlays always have at least a data section we can check in the spec, so it's not needed for them
                    if type != "overlay":
                        assert last_line.count(".") == 1
                        last_line = (
                            last_line.strip()
                            .split("build/", 1)[1]
                            .replace(".o", ".c")[:-1]
                        )
                        with open(root_path / last_line, "r") as f2:
                            if "GLOBAL_ASM" in f2.read():
                                include = True

            if include:
                new_files[offset] = file
                included = True

        if type == "overlay" and not included:
            continue
        if included:
            f[4] = new_files

        new_spec.append(f)

    return new_spec


MIPS_BRANCH_LIKELY_INSNS = [
    MIPS_INS_BEQL,
    MIPS_INS_BGEZALL,
    MIPS_INS_BGEZL,
    MIPS_INS_BGTZL,
    MIPS_INS_BLEZL,
    MIPS_INS_BLTZALL,
    MIPS_INS_BLTZL,
    MIPS_INS_BNEL,
    MIPS_INS_BC1TL,
    MIPS_INS_BC1FL,
]

MIPS_BRANCH_INSNS = [
    *MIPS_BRANCH_LIKELY_INSNS,
    MIPS_INS_BEQ,
    MIPS_INS_BGEZ,
    MIPS_INS_BGEZAL,
    MIPS_INS_BGTZ,
    MIPS_INS_BNE,
    MIPS_INS_BLTZ,
    MIPS_INS_BLTZAL,
    MIPS_INS_BLEZ,
    MIPS_INS_BC1T,
    MIPS_INS_BC1F,
    MIPS_INS_BEQZ,
    MIPS_INS_BNEZ,
    MIPS_INS_B,
]

MIPS_JUMP_INSNS = [MIPS_INS_JAL, MIPS_INS_JALR, MIPS_INS_J, MIPS_INS_JR]

MIPS_FP_LOAD_INSNS = [MIPS_INS_LWC1, MIPS_INS_LDC1]

MIPS_FP_STORE_INSNS = [MIPS_INS_SWC1, MIPS_INS_SDC1]

MIPS_FP_LOAD_STORE_INSNS = [*MIPS_FP_LOAD_INSNS, *MIPS_FP_STORE_INSNS]

MIPS_STORE_INSNS = [
    MIPS_INS_SB,
    MIPS_INS_SH,
    MIPS_INS_SW,
    MIPS_INS_SWL,
    MIPS_INS_SWR,
    MIPS_INS_SD,
    MIPS_INS_SDL,
    MIPS_INS_SDR,
    MIPS_INS_SC,
    MIPS_INS_SCD,
    *MIPS_FP_STORE_INSNS,
]

MIPS_LOAD_STORE_INSNS = [
    MIPS_INS_LB,
    MIPS_INS_LBU,
    MIPS_INS_LH,
    MIPS_INS_LHU,
    MIPS_INS_LW,
    MIPS_INS_LWL,
    MIPS_INS_LWR,
    MIPS_INS_LWU,
    MIPS_INS_LD,
    MIPS_INS_LDL,
    MIPS_INS_LDR,
    MIPS_INS_LL,
    MIPS_INS_LLD,
    *MIPS_STORE_INSNS,
    *MIPS_FP_LOAD_STORE_INSNS,
]

functions = set()  # vram of functions
# vram of data labels, TODO this + functions can merge into something more general eventually
data_labels = set()
branch_labels = set()  # vram of branch labels via branch/jump instructions
jtbls = set()  # vram of jump tables
# vram of branch labels via jtbls, higher output priority than regular branch labels
jtbl_labels = set()
floats = set()  # vram of floats
doubles = set()  # vram of doubles
prospective_strings = set()  # vram of possible strings
strings = set()  # vram of confirmed strings
# lui/addiu pairs : {addr of %hi : full symbol} AND {addr of %lo : full symbol} ,
# twice the space complexity but much less time complexity
symbols = {}
# lui/ori pairs : {addr of %hi : full constant} AND {addr of %lo : full constant} ,
# twice the space complexity but much less time complexity
constants = {}
dwords = set()  # doublewords
# rodata with more than 1 reference outside of the same function cannot be migrated
multiply_referenced_rodata = set()
files = set()  # vram start of file

vrom_variables = list()  # (name,addr)

functions_ast = None
variables_ast = None

vars_cache = {}  # (address: variable + addend)

files_text = {}


def proper_name(symbol, in_data=False, is_symbol=True):
    # hacks
    # ovl_En_Encount4 fake symbol at the very end of the data section
    if symbol == 0x809C46F0:
        return variables_ast[0x809C46DC][0] + " + 0x14"
    elif symbol == 0x801EF66D:  # z_message_nes constant-folding stray fairy array
        return variables_ast[0x801EF670][0] + f" - 0x{0x801EF670 - 0x801EF66D:X}"
    elif symbol == 0x80A09740:  # boss_07 symbol with large addend folded into %lo
        return variables_ast[0x80A09A60][0] + f" - 0x{0x80A09A60 - 0x80A09740:X}"
    # bg_ikana_mirror symbol with large addend folded into %lo
    elif symbol == 0x80B80248:
        return variables_ast[0x80B801A8][0] + f" + 0x{0x80B80248 - 0x80B801A8:X}"
    # player symbol with very large addend folded into %lo, since we don't know the real symbol just use the first data symbol for now
    elif symbol == 0x8084D2FC:
        return variables_ast[0x8085B9F0][0] + f" - 0x{0x8085B9F0 - 0x8084D2FC:X}"
    # OS_K0_TO_PHYSICAL on rspS2DEX text and data symbols
    elif symbol == 0x001ABAB0 or symbol == 0x001E3BB0:
        return variables_ast[symbol + 0x80000000][0] + " - 0x80000000"
    # do_action_static + 0x480, this is the only rom segment that has a constant offset folded into it so just hack it
    elif symbol == 0x00AC0480:
        return "_do_action_staticSegmentRomStart + 0x480"

    # real names
    if symbol in functions_ast.keys():
        return functions_ast[symbol][0]
    elif symbol in variables_ast.keys():
        return variables_ast[symbol][0]
    elif symbol in [addr for _, addr in vrom_variables]:
        # prefer "start" vrom symbols
        filteredVromSymbols = {
            addr: name
            for name, addr in vrom_variables
            if "SegmentRomStart" in name and addr == symbol
        }
        if symbol in filteredVromSymbols:
            return filteredVromSymbols[symbol]
        else:
            return [name for name, addr in vrom_variables if addr == symbol][0]

    # addends
    if is_symbol and symbol in vars_cache.keys():
        return vars_cache[symbol]

    # generated names
    if symbol in functions and not in_data:
        return f"func_{symbol:08X}"
    elif symbol in jtbl_labels:
        return f"L{symbol:08X}"
    elif symbol in jtbls:
        return f"jtbl_{symbol:08X}"
    else:
        if is_symbol:
            return f"D_{symbol:08X}"
        else:
            return f"0x{symbol:08X}"


def lookup_name(symbol, word):
    # hacks for vrom variables in data
    if word in [addr for _, addr in vrom_variables]:
        if word == 0:  # no makerom segment start
            return "0x00000000"
        if symbol in [
            0x801AE4A0,  # effect table
            0x801C2740,  # object table
            0x801C2650,  # elf_message table
            0x801C3CA0,  # scene table
            0x801AEFD0,  # actor table
            0x801D0B70,  # kaleido table
            0x801D0BB0,  # fbdemo table
            0x801BE4D4,  # kankyo skybox table
            0x801BD910,  # gamestate table
            0x801C2660,  # scene textures table
        ]:  # data labels that are allowed to have vrom variables
            return proper_name(word, is_symbol=False)
        else:
            return f"0x{word:08X}"
    # hacks for variables with references to variables with addends (i.e. gSaveContext + 0x...)
    if symbol in [0x800980C4, 0x801AE8F0]:  # __osViNext and flg_set table
        return proper_name(word, is_symbol=True)
    return proper_name(word, is_symbol=False)


def as_double(b):
    return struct.unpack(">d", b)[0]


def as_float(b):
    return struct.unpack(">f", b)[0]


def as_dword(b):
    return struct.unpack(">Q", b)[0]


def as_word(b):
    return struct.unpack(">I", b)[0]


def as_hword(b):
    return struct.unpack(">H", b)[0]


def as_double_list(b):
    return [i[0] for i in struct.iter_unpack(">d", b)]


def as_float_list(b):
    return [i[0] for i in struct.iter_unpack(">f", b)]


def as_dword_list(b):
    return [i[0] for i in struct.iter_unpack(">Q", b)]


def as_word_list(b):
    return [i[0] for i in struct.iter_unpack(">I", b)]


def as_hword_list(b):
    return [h[0] for h in struct.iter_unpack(">H", b)]


STR_INDENT = "                      "


def try_decode_string(data_bytes, output_ends=True, force_ascii=False):
    """
    Swiss Cheese
    """
    hex_digits = "0123456789abcdefABCDEF"
    result = ""
    directive = "ascii" if force_ascii else "asciz"

    if 0x8C in data_bytes or 0x8D in data_bytes or 0x1B in data_bytes:
        char = ""
        index = None
        if 0x8C in data_bytes:
            char = "\\x8C"
            index = data_bytes.index(0x8C)
        elif 0x8D in data_bytes:
            char = "\\x8D"
            index = data_bytes.index(0x8D)
        elif 0x1B in data_bytes:
            char = "\\x1B"
            index = data_bytes.index(0x1B)
        else:
            assert False, "???"
        part1 = try_decode_string(data_bytes[0:index], output_ends=False)
        part2 = try_decode_string(data_bytes[index + 1 :], output_ends=False)
        if part2 != "":
            result = (
                part1
                + (
                    ('"\n' + STR_INDENT + '.ascii "')
                    if part2[0] in hex_digits and part1 != ""
                    else ""
                )
                + char
                + (('"\n' + STR_INDENT + '.asciz "') if part2[0] in hex_digits else "")
                + part2
            )
            if output_ends and part2[0] in hex_digits and part1 == "":
                directive = "ascii"
        else:
            result = (
                part1
                + (
                    ('"\n' + STR_INDENT + '.ascii "')
                    if part2[0] in hex_digits and part1 != ""
                    else ""
                )
                + char
                + '"\n'
            )
    else:
        result = (
            data_bytes.decode("EUC-JP")
            .replace("\n", "\\n")
            .replace("\r", "\\r")
            .replace("\t", "\\t")
            .replace("\0", "")
        )

    return (
        (("." + directive + ' "') if output_ends else "")
        + result
        + ('"' if output_ends else "")
    )


def reduce_float(flt_str, is_double=False):
    def n_digits(str):
        if "." not in str:
            return 0
        return len(str.split(".")[1].strip())

    def str_round(string, precision):
        if "." not in string or precision < 0:
            return string
        int_part = string.split(".")[0]
        frac_part = string.split(".")[1]

        while len(frac_part) > precision:
            last_digit = int(frac_part[-1])
            frac_part = frac_part[:-1]
            # round up & carry
            if last_digit >= 5:
                while len(frac_part) != 0:
                    last_digit = int(frac_part[-1])
                    frac_part = frac_part[:-1]
                    if last_digit != 9:
                        # complete carry
                        last_digit += 1
                        frac_part += repr(last_digit)
                        break
                if len(frac_part) == 0:
                    int_part = repr(int(int_part) + 1)
                    frac_part = "0"
        return int_part + "." + frac_part

    def to_binary(flt_str):
        if is_double:
            return as_dword(struct.pack(">d", float(flt_str)))
        return as_word(struct.pack(">f", float(flt_str)))

    exponent = ""
    if "e" in flt_str:
        exponent = "e" + flt_str.split("e")[1]
        flt_str = flt_str.split("e")[0]

    original_binary = to_binary(flt_str + exponent)
    precision = n_digits(flt_str)

    if precision == 0:
        if exponent != "":
            return flt_str + exponent
        return flt_str + (".0" if not flt_str.endswith(".") else "0")

    while precision > 1:
        precision -= 1
        old_str = flt_str
        flt_str = str_round(flt_str, precision)

        if to_binary(flt_str + exponent) != original_binary:
            flt_str = old_str
            break

    if flt_str.endswith("."):
        flt_str += "0"

    return flt_str + exponent


def format_f64(d_dwd):
    d = as_double(struct.pack(">Q", d_dwd))
    if math.isnan(d):
        return f".long 0x{d_dwd:016X}"
    return f".double {reduce_float(repr(d), is_double=True)}"


def format_f32(f_wd):
    # GNU AS isn't ieee compliant?
    if f_wd in [0xB8E4AECD, 0xB8E4C3AA, 0x38D1B718]:
        return f".word 0x{f_wd:08X}"

    if f_wd == 0x7F7FFFFF:  # FLT_MAX
        return ".float 3.4028235e+38"

    f = as_float(struct.pack(">I", f_wd))
    if math.isnan(f):
        return f".word 0x{f_wd:08X}"
    return f".float {reduce_float(repr(f))}"


def put_symbol(symbols_dict, setname, symbol):
    if setname in symbols_dict:
        symbols_dict[setname].add(symbol)
    else:
        symbols_dict[setname] = {symbol}


def put_symbols(symbols_dict, setname, symbols):
    if setname in symbols_dict:
        symbols_dict[setname].update(symbols)
    else:
        symbols_dict[setname] = symbols.copy()


def put_text(name, text):
    files_text[name] = text


def update_symbols_from_dict(symbols_dict):
    file_text = []
    if type(symbols_dict) == tuple:
        symbols_dict, file_text = symbols_dict

    for setname, symbol in symbols_dict.items():
        if setname == "functions":
            functions.update(symbol)
        elif setname == "data_labels":
            data_labels.update(symbol)
        elif setname == "branch_labels":
            branch_labels.update(symbol)
        elif setname == "jtbls":
            jtbls.update(symbol)
        elif setname == "jtbl_labels":
            jtbl_labels.update(symbol)
        elif setname == "floats":
            floats.update(symbol)
        elif setname == "doubles":
            doubles.update(symbol)
        elif setname == "prospective_strings":
            prospective_strings.update(symbol)
        elif setname == "strings":
            strings.update(symbol)
        elif setname == "symbols":
            symbols.update(symbol)
        elif setname == "constants":
            constants.update(symbol)
        elif setname == "dwords":
            dwords.update(symbol)
        elif setname == "files":
            files.update(symbol)

    for file in file_text:
        put_text(file[0], file[1])


def find_symbols_in_text(section, rodata_section, data_regions):
    data, rodata = section[4], rodata_section[4] if rodata_section else None
    vram, vram_rodata = section[0], rodata_section[0] if rodata_section else None
    relocs, info = section[5], section[-1]

    symbols_dict = dict()

    print(f"Finding symbols from .text in {info['name']}")

    if rodata is not None:
        rodata_words = as_word_list(rodata)

    raw_insns = as_word_list(data)

    assert vram % 0x10 == 0

    put_symbol(symbols_dict, "functions", vram)
    put_symbol(symbols_dict, "files", vram)

    # lui trackers are saved at branches to be restored when the branch target is reached
    saved_lui_trackers = {}  # vram: tracker list

    def save_tracker(restore_at, tracker):
        if restore_at in saved_lui_trackers.keys():
            saved_lui_trackers[restore_at].update(tracker)
        else:
            saved_lui_trackers.update({restore_at: tracker})

    lui_tracker = {}  # register : (addr, immediate)

    prospective_jtbls = set()

    func_branch_labels = set()
    func_jtbl_labels = set()
    individual_jtbl_labels = {}

    clobber_later = {}  # addr : reg

    delay_slot = False
    delayed_insn = None
    next_jtbl_jr = 0

    def clobber_conditionally(insn):
        # Don't clobber immediately if in a branch likely's delay slot as it only runs if the branch is taken,
        # instead clobber at the branch target.
        # This may appear suspicious at first since something could have set a good register in another code path,
        # however that does not make sense since all code paths must resolve a valid symbol, so if one code path clobbers,
        # that means no code path produces a valid symbol at he convergent code, unless the convergent code provides all the
        # new registers.

        # assert insn.value_forname(insn.fields[0]) is not None
        # print(f"insn: {insn.mnemonic}, rt: {insn.rt}, first: {insn.value_forname(insn.fields[0])}")
        # assert insn.id not in [MIPS_INS_ORI, MIPS_INS_ADDIU, *MIPS_LOAD_STORE_INSNS] or insn.rt == insn.value_forname(insn.fields[0])

        if (
            delay_slot
            and delayed_insn is not None
            and delayed_insn.id in MIPS_BRANCH_LIKELY_INSNS
        ):
            clobber_later.update(
                {delayed_insn.offset: insn.value_forname(insn.fields[0])}
            )
        else:
            lui_tracker.pop(insn.value_forname(insn.fields[0]), None)

    for region in data_regions:
        assert region[1] != 0
        put_symbol(symbols_dict, "functions", region[1])
        if region[1] % 0x10 == 0:
            put_symbol(symbols_dict, "files", region[1])

    insns = []
    for i, raw_insn in enumerate(raw_insns, 0):
        insn = decode_insn(raw_insn, vram + i * 4)

        if insn.id == MIPS_INS_JR and insn.rs != MIPS_REG_RA:
            # It's hard to find when two jump tables next to each other end, so do a naive first pass
            # to try and find as many jump tables as possible.
            # Luckily IDO has a very homogeneous output for jump tables for which it is very unlikely
            # that other instructions will break up:
            #   lui $at, %hi(jtbl)
            #   addu $at, $at, $reg
            #   lw $reg, %lo(jtbl)($at)
            #   jr $reg
            insn_m1 = insns[-1]
            insn_m2 = insns[-2]
            insn_m3 = insns[-3]
            if (
                insn_m1.id == MIPS_INS_LW
                and insn_m2.id == MIPS_INS_ADDU
                and insn_m3.id == MIPS_INS_LUI
            ):
                prospective_jtbls.add((insn_m3.imm << 0x10) + insn_m1.imm)
        insns.append(insn)

    if relocs is not None:
        """
        Relocation info is our friend. Get symbols via relocations first.
        """
        prev_hi = None
        hi_vram = -1
        for reloc in relocs:
            insn = insns[reloc[2] // 4]

            if reloc[1] == 2:  # R_MIPS_32
                assert False, "R_MIPS_32 in .text section?"
            elif reloc[1] == 4:  # R_MIPS_26
                """
                Relocated jump targets give us functions in this section
                """
                assert (
                    insn.id == MIPS_INS_JAL
                ), f"R_MIPS_26 applied to {insn.mnemonic} when it should be JAL"
                put_symbol(symbols_dict, "functions", insn.target)
            elif reloc[1] == 5:  # R_MIPS_HI16
                """
                Relocated %hi gives us %hi values to match with associated %lo
                """
                assert (
                    insn.id == MIPS_INS_LUI
                ), f"R_MIPS_HI16 applied to {insn.mnemonic} when it should be LUI"
                prev_hi = insn.imm
                hi_vram = vram + reloc[2]
            elif reloc[1] == 6:  # R_MIPS_LO16
                """
                Relocated %lo + a %hi to match with gives us relocated symbols in data sections
                """
                assert (
                    insn.id == MIPS_INS_ADDIU or insn.id in MIPS_LOAD_STORE_INSNS
                ), f"R_MIPS_HI16 applied to {insn.mnemonic} when it should be ADDIU or a load/store"
                symbol_value = (prev_hi << 0x10) + insn.imm
                put_symbols(symbols_dict, "symbols", {hi_vram: symbol_value})
                put_symbols(symbols_dict, "symbols", {vram + reloc[2]: symbol_value})
            else:
                assert False, "Invalid relocation type encountered"

    result_files = []
    results = [asm_header(".text")]
    raw_insns = as_word_list(data)

    cur_file = ""
    cur_vaddr = 0

    segment_dirname = ("" if info["type"] != "overlay" else "overlays/") + info["name"]

    delayed_insn = None
    delay_slot = False

    for i, insn in enumerate(insns, 0):
        vaddr = vram + i * 4

        # sometimes there's data embedded in .text in handwritten asm files that don't respect section contents
        in_data = False
        for region in data_regions:
            if vaddr in range(region[0], region[1], 4):
                in_data = True
                break
        if in_data:
            results.append(
                {
                    "vaddr": vaddr,
                    "insn": {"id": insn.id},
                    "addr": f"/* {i*4:06X} {vaddr:08X} {raw_insns[i]:08X} */  ",
                    "mnem": "",
                    "op": [f"  .word 0x{raw_insns[i]:08X}"],
                    "data": True,
                }
            )
            continue

        if vaddr in functions or vaddr in symbols_dict["functions"]:
            # add func branch labels to all branch labels
            put_symbols(symbols_dict, "branch_labels", func_branch_labels)
            func_branch_labels.clear()
            # add func jtbl labels to all jtbl labels
            put_symbols(symbols_dict, "jtbl_labels", func_jtbl_labels)
            func_jtbl_labels.clear()
            # clear individual jtbl labels
            individual_jtbl_labels.clear()
            # destroy lui tracking state
            lui_tracker.clear()
            saved_lui_trackers.clear()
        else:
            # restore lui tracking state if previously saved
            lui_tracker.update(saved_lui_trackers.pop(vaddr, {}))

        # register clobbering in branch likely delay slots
        cl = clobber_later.pop(vaddr, None)
        if cl is not None:
            lui_tracker.pop(cl, None)

        if insn.id in MIPS_BRANCH_INSNS:
            func_branch_labels.add(insn.offset)
            delayed_insn = insn
        elif insn.id == MIPS_INS_ERET:
            put_symbol(symbols_dict, "functions", vaddr + 4)
        elif insn.id in MIPS_JUMP_INSNS:
            if insn.id == MIPS_INS_JAL:
                # mark function at target
                put_symbol(symbols_dict, "functions", insn.target)
            elif insn.id == MIPS_INS_J:
                # mark label at target
                func_branch_labels.add(insn.target)
            elif insn.id == MIPS_INS_JR:
                # check if anything branches past it in either branch or jtbl labels
                if vaddr >= max(func_branch_labels, default=0) and vaddr >= max(
                    func_jtbl_labels, default=0
                ):  # vaddr being largest in list means nothing branches past here
                    # mark next function after delay slot and after any nop padding if present
                    if len(insns) > i + 2:
                        n_padding = 0
                        end = False
                        while raw_insns[i + 2 + n_padding] == 0:
                            n_padding += 1
                            if len(raw_insns) <= i + 2 + n_padding:
                                end = True
                                break
                        if not end:
                            if n_padding > 0:
                                assert (
                                    vaddr + 8 + n_padding * 4
                                ) % 0x10 == 0, f"padding to non-0x10 alignment?, 0x{vaddr + 8 + n_padding * 4:08X}"
                                put_symbol(
                                    symbols_dict, "functions", vaddr + 8 + n_padding * 4
                                )
                            put_symbol(
                                symbols_dict, "functions", vaddr + 8 + n_padding * 4
                            )
            delayed_insn = insn
        elif insn.id == MIPS_INS_LUI:
            """
            Process LUI instruction

            All symbol loading involves LUI, and tracking how %hi values loaded via LUI instructions propagate
            through a function is key to identifying symbol references
            """
            # add lui to tracker
            if (
                delay_slot
                and delayed_insn is not None
                and delayed_insn.id in MIPS_BRANCH_LIKELY_INSNS
            ):
                # for branch likelies, the current tracker does not update but the lui is saved to be tracked at the branch target
                save_tracker(delayed_insn.offset, {insn.rt: (vaddr, insn.imm)})
            else:
                lui_tracker.update({insn.rt: (vaddr, insn.imm)})
        elif insn.id == MIPS_INS_ADDIU or insn.id in MIPS_LOAD_STORE_INSNS:
            # try match with tracked lui and mark symbol
            hi_vram, imm_value = lui_tracker.get(
                insn.rs if insn.id == MIPS_INS_ADDIU else insn.base, (None, None)
            )
            # if a match was found, validate and record the symbol, TODO improve validation
            if hi_vram != None and (
                (((imm_value >> 0x8) & 0xF) != 0 and imm_value < 0x1000)
                or (imm_value >= 0x8000 and imm_value < 0x80D0)
                or (imm_value >= 0xA400 and imm_value < 0xA480)
                or (imm_value < 0x0400 and insn.id == MIPS_INS_ADDIU)
            ):
                lo_vram = vaddr
                symbol_value = (imm_value << 0x10) + insn.imm
                put_symbols(symbols_dict, "symbols", {hi_vram: symbol_value})
                put_symbols(symbols_dict, "symbols", {lo_vram: symbol_value})
                if insn.id == MIPS_INS_LW:
                    # try find jr within the same block
                    cur_idx = i
                    lookahead_insn = insns[cur_idx]  # TODO fix vaddr here
                    # still in same block unless one of these instructions are found
                    while lookahead_insn.id not in [
                        *MIPS_BRANCH_INSNS,
                        MIPS_INS_JAL,
                        MIPS_INS_JALR,
                        MIPS_INS_J,
                    ]:
                        if lookahead_insn.id == MIPS_INS_JR:
                            if lookahead_insn.rs == (
                                insn.ft
                                if insn.id in MIPS_FP_LOAD_STORE_INSNS
                                else insn.rt
                            ):
                                # read the jtbl and add targets to func_jtbl_labels
                                assert (
                                    rodata is not None
                                ), "A rodata section should be present if functions use jump tables"

                                next_jtbl_jr = vaddr + cur_idx * 4
                                individual_jtbl_labels.update({next_jtbl_jr: set()})

                                offset = (symbol_value - vram_rodata) // 4
                                label = rodata_words[offset]
                                while (
                                    label >= vram
                                    and label < vram + len(data)
                                    and (
                                        vram_rodata + offset * 4
                                        not in prospective_jtbls
                                        or vram_rodata + offset * 4 == symbol_value
                                    )
                                ):
                                    func_jtbl_labels.add(label)
                                    individual_jtbl_labels[next_jtbl_jr].add(label)
                                    offset += 1
                                    if offset >= len(rodata_words):
                                        break
                                    label = rodata_words[offset]

                                put_symbol(symbols_dict, "jtbls", symbol_value)
                                # found a jr that matches, no need to keep searching
                                break
                        elif (
                            insn.ft if insn.id in MIPS_FP_LOAD_STORE_INSNS else insn.rt
                        ) in [
                            lookahead_insn.value_forname(field)
                            for field in lookahead_insn.fields[1:]
                        ]:
                            # register clobbered, no need to keep searching
                            break
                        cur_idx += 1
                        # found end before finding jr insn, not a jtbl
                        if cur_idx >= len(raw_insns):
                            break
                        lookahead_insn = insns[cur_idx]  # TODO fix vaddr here
                elif insn.id == MIPS_INS_LD:  # doubleword loads
                    put_symbol(symbols_dict, "dwords", symbol_value)
                elif insn.id in [MIPS_INS_LWC1, MIPS_INS_SWC1]:  # float load/stores
                    # add float
                    put_symbol(symbols_dict, "floats", symbol_value)
                elif insn.id in [MIPS_INS_LDC1, MIPS_INS_SDC1]:  # double load/stores
                    # add double
                    put_symbol(symbols_dict, "doubles", symbol_value)
                elif (
                    insn.id == MIPS_INS_ADDIU and vaddr % 4 == 0
                ):  # strings seem to only ever be 4-byte aligned
                    # add possible string
                    put_symbol(symbols_dict, "prospective_strings", symbol_value)
            # clear lui tracking state if register is clobbered by the addiu/load instruction itself
            # insn.rt == (insn.rs if insn.id == MIPS_INS_ADDIU else insn.base) and
            if insn.id not in MIPS_STORE_INSNS and insn.id not in MIPS_FP_LOAD_INSNS:
                clobber_conditionally(insn)
        elif insn.id == MIPS_INS_ORI:
            # try match with tracked lui and mark constant
            hi_vram, imm_value = lui_tracker.get(insn.rs, (None, None))
            if hi_vram != None:  # found match
                lo_vram = vaddr
                const_value = (imm_value << 0x10) | insn.imm
                put_symbols(symbols_dict, "constants", {hi_vram: const_value})
                put_symbols(symbols_dict, "constants", {lo_vram: const_value})
            # clear lui tracking state if register is clobbered by the ori instruction itself
            # insn.rt == insn.rs or
            if insn.rt in lui_tracker.keys():
                clobber_conditionally(insn)
        else:
            # clear lui tracking if register is clobbered by something unrelated
            if (
                insn.id == MIPS_INS_ADDU
                and insn.rs in lui_tracker.keys()
                and (insn.rd == insn.rs)
            ):
                # array accesses optimisation:
                #   lui  reg, %hi(symbol)
                #   addu reg, reg, idx
                #   lw   reg, %lo(symbol)(reg)
                # instead of clobbering, keep it if the second operand is also the first
                # if the output is not currently tracked it will behave as intended anyway
                pass
            # insns listed either write to fprs/cop0 or don't write to any
            elif insn.id not in [
                MIPS_INS_MTC0,
                MIPS_INS_MTC1,
                MIPS_INS_DMTC1,
                MIPS_INS_MULT,
                MIPS_INS_MULTU,
                MIPS_INS_DMULT,
                MIPS_INS_DMULTU,
                MIPS_INS_DIV,
                MIPS_INS_DIVU,
                MIPS_INS_DDIV,
                MIPS_INS_DDIVU,
                MIPS_INS_MTHI,
                MIPS_INS_MTLO,
                MIPS_INS_CTC1,
                MIPS_INS_NOP,
                MIPS_INS_BREAK,
                MIPS_INS_TLBP,
                MIPS_INS_TLBR,
                MIPS_INS_TLBWI,
                MIPS_INS_MOV_S,
                MIPS_INS_MOV_D,
                MIPS_INS_C_LT_S,
                MIPS_INS_C_LT_D,
                MIPS_INS_DIV_S,
                MIPS_INS_MUL_S,
                MIPS_INS_TRUNC_W_S,
                MIPS_INS_CVT_S_W,
                MIPS_INS_SUB_S,
                MIPS_INS_ADD_S,
            ]:
                clobber_conditionally(insn)

        ############# Start text disassembly ##########
        # Symbols aren't avaialble here yet, so placeholders are added
        # in each instruction, to be looked up later
        mnemonic = f" {insn.mnemonic}" if delay_slot else insn.mnemonic
        op_str = insn.op_str
        instr = {"id": insn.id}

        if vaddr in full_file_list[info["name"]]:
            if cur_file != "":
                if cur_vaddr in info["syms"]:
                    result_files.append([cur_file, results])
                results = [asm_header(".text")]
            cur_vaddr = vaddr
            cur_file = full_file_list[info["name"]][vaddr]
            if cur_file == "":
                cur_file = f"{info['name']}_{vaddr:08X}"

        if insn.id in MIPS_BRANCH_INSNS:
            op_str_parts = []
            for field in insn.fields:
                if field == "offset":
                    op_str_parts.append(f".L{insn.offset:08X}")
                else:
                    op_str_parts.append(insn.format_field(field))
            op_str = [", ".join(op_str_parts)]

        elif insn.id in MIPS_JUMP_INSNS:
            op_str = []
            op_str_parts = []
            for field in insn.fields:
                if field == "target":
                    op_str_parts.append([insn.target, False, True])
                else:
                    op_str_parts.append(insn.format_field(field))
            for x, part in enumerate(op_str_parts):
                if x + 1 < len(op_str_parts):
                    part += ", "
                op_str.append(part)

        elif insn.id == MIPS_INS_LUI:
            op_str = [op_str]
            instr["rt"] = insn.rt

        elif insn.id == MIPS_INS_ADDIU or insn.id in MIPS_LOAD_STORE_INSNS:
            op_str = [op_str]
            instr["rt"] = insn.rt
            instr["rs"] = insn.rs
            instr["ft"] = insn.ft
            instr["base"] = insn.base

        elif insn.id == MIPS_INS_ORI:
            op_str = [op_str]
            instr["rt"] = insn.rt
            instr["rs"] = insn.rs

        results.append(
            {
                "vaddr": vaddr,
                "insn": instr,
                "addr": f"/* {i*4:06X} {vaddr:08X} {raw_insns[i]:08X} */  ",
                "mnem": mnemonic,
                "op": op_str,
                "data": False,
            }
        )

        ######### End text disassembly ##############

        if delay_slot and delayed_insn is not None:
            if (
                delayed_insn.id == MIPS_INS_JAL
                or delayed_insn.id == MIPS_INS_JALR
                or (delayed_insn.id == MIPS_INS_JR and delayed_insn.rs == MIPS_REG_RA)
            ):
                # destroy lui tracking state
                lui_tracker.clear()
            elif delayed_insn.id == MIPS_INS_JR and vaddr == next_jtbl_jr + 4:
                # save lui tracking state for each jtbl label
                for label in individual_jtbl_labels[next_jtbl_jr]:
                    save_tracker(label, lui_tracker.copy())
                next_jtbl_jr = 0
            else:
                # save lui tracking state
                save_tracker(delayed_insn.offset, lui_tracker.copy())
                # destroy current lui tracking state for unconditional branches
                if delayed_insn.id == MIPS_INS_B:
                    lui_tracker.clear()

            delayed_insn = None

        delay_slot = delayed_insn is not None

    result_files.append([cur_file, results])

    put_symbols(symbols_dict, "branch_labels", func_branch_labels)
    put_symbols(symbols_dict, "jtbl_labels", func_jtbl_labels)

    return symbols_dict, result_files


def find_symbols_in_data(section):
    data, vram, end, relocs = section[4], section[0], section[1], section[5]
    symbols_dict = dict()

    print(f"Finding symbols from .data in {section[-1]['name']}")

    # read relocations for symbols
    if relocs is not None:
        for reloc in relocs:
            if reloc[1] == 2:  # R_MIPS_32
                put_symbol(
                    symbols_dict, "data_labels", as_word(data[reloc[2] : reloc[2] + 4])
                )
            elif reloc[1] == 4:  # R_MIPS_26
                assert False, "R_MIPS_26 in .data section?"
            elif reloc[1] == 5:  # R_MIPS_HI16
                assert False, "R_MIPS_HI16 in .data section?"
            elif reloc[1] == 6:  # R_MIPS_LO16
                assert False, "R_MIPS_LO16 in .data section?"
            else:
                assert False, "Invalid relocation type encountered"

    return symbols_dict
    # TODO more


# matches several codepoint regions of EUC-JP
strings_regex = re.compile(
    rb"^(?:[\x00\x1A\x1B\n\t\x20-\x7E\x8C\x8D]|\x30[\x00-\xFF]|[\x4E-\x9F][\x00-\xFF]|[\xA4\xA5\xBB][\xA1-\xF6]|[\xA1-\xA3\xB0-\xBF\xC0-\xCF][\xA1-\xFE]|\xFF[\x00-\xEF])+$"
)


def find_symbols_in_rodata(section):
    data, vram, end, relocs = section[4], section[0], section[1], section[5]
    symbols_dict = dict()

    print(f"Finding symbols from .rodata in {section[-1]['name']}")

    # read relocations for symbols
    if relocs is not None:
        for reloc in relocs:
            if reloc[1] == 2:  # R_MIPS_32
                put_symbol(
                    symbols_dict, "data_labels", as_word(data[reloc[2] : reloc[2] + 4])
                )
            elif reloc[1] == 4:  # R_MIPS_26
                assert False, "R_MIPS_26 in .rodata section?"
            elif reloc[1] == 5:  # R_MIPS_HI16
                assert False, "R_MIPS_HI16 in .rodata section?"
            elif reloc[1] == 6:  # R_MIPS_LO16
                assert False, "R_MIPS_LO16 in .rodata section?"
            else:
                assert False, "Invalid relocation type encountered"

    section_symbols = set(
        [sym for sym in symbols.values() if sym >= vram and sym < end]
    )
    section_symbols.add(vram)
    section_symbols.update(
        set([sym for sym in data_labels if sym >= vram and sym < end])
    )
    # TODO temp hack, move
    for data_file_st in [
        sym for sym in section[-1]["syms"].keys() if sym >= vram and sym < end
    ]:
        section_symbols.add(data_file_st)

    rodata_starts = [
        addr
        for addr, name in section[-1]["syms"].items()
        if addr >= vram and addr < end
    ]
    section_symbols.update(set(rodata_starts))

    section_symbols = list(section_symbols)

    section_symbols.sort()

    section_late_rodata = [
        sym
        for sym in section_symbols
        if sym in floats or sym in doubles or sym in jtbls
    ]

    # string finding is best done per-file as the late_rodata sections are not merged per-segment, so you get stripes of
    # rodata - late_rodata -(file boundary)- rodata - late_rodata -(file boundary)- etc.

    # all rodata file starts
    for fi, rodata_start in enumerate(rodata_starts, 0):
        next_rodata_start = (
            rodata_starts[fi + 1] if fi < len(rodata_starts) - 1 else end
        )

        # symbols in this file
        file_symbols = [
            sym
            for sym in section_symbols
            if sym >= rodata_start and sym < next_rodata_start
        ]

        # the first (minimum st_value) symbol in section_late_rodata in this file is the start of late_rodata
        late_rodata_start = min(
            [sym for sym in file_symbols if sym in section_late_rodata],
            default=next_rodata_start,
        )

        for i, symbol in enumerate(file_symbols, 0):
            next_symbol = (
                file_symbols[i + 1] if i < len(file_symbols) - 1 else next_rodata_start
            )

            # not late_rodata
            if symbol >= late_rodata_start:
                break
            else:
                if symbol in dwords or symbol % 4 != 0:
                    continue

                data_offset = symbol - vram
                data_size = next_symbol - symbol
                string_data = data[data_offset : data_offset + data_size]

                if len(string_data) > 0 and string_data[0] == 0:
                    # empty strings that are auto-detected are dubious
                    continue

                # charset validation
                if strings_regex.match(string_data) != None:
                    k = 0
                    done = False
                    for j, b in enumerate(string_data, 0):
                        if b == 0 and (
                            j + 1 >= len(string_data) or string_data[j + 1] != 0
                        ):
                            # try:
                            #     decoded = try_decode_string(string_data[k:string_data.index(0)])
                            # except UnicodeDecodeError:
                            #     # not a string, also suggests nothing past here is a string either
                            #     done = True
                            # if done:
                            #     break
                            put_symbol(symbols_dict, "data_labels", symbol + k)
                            put_symbol(symbols_dict, "data_labels", symbol + j + 1)
                            put_symbol(symbols_dict, "strings", symbol + k)
                            k = j + 1

    # TODO more
    return symbols_dict


def asm_header(section_name):
    return f""".include "macro.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section {section_name}

.balign 16
"""


def fixup_text_symbols(data, vram, data_regions, info):
    segment_dirname = "" if info["type"] != "overlay" else "overlays/"
    if info["type"] in ("boot", "code"):
        segment_dirname += info["type"]
    else:
        segment_dirname += info["name"]

    os.makedirs(f"{ASM_OUT}/{segment_dirname}/", exist_ok=True)

    file = files_text[info["name"]]
    # header
    text = [file.pop(0)]

    # We didn't have full symbols available during initial disassembly,
    # so here we loop over each instruction, and do symbol lookups, add labels etc

    for i, entry in enumerate(file):
        vaddr = entry["vaddr"]

        if vaddr in functions:
            text.append(f"\nglabel {proper_name(vaddr, in_data=entry['data'])}\n")
        if vaddr in jtbl_labels:
            text.append(f"glabel L{vaddr:08X}\n")
        if vaddr in branch_labels:
            text.append(f".L{vaddr:08X}:\n")

        line = entry["addr"]
        if not entry["data"]:
            line += f"{entry['mnem']:12}"

        insn = entry["insn"]
        if insn["id"] in MIPS_JUMP_INSNS:
            for op_part in entry["op"]:
                if type(op_part) == list:
                    line += proper_name(
                        op_part[0], in_data=op_part[1], is_symbol=op_part[2]
                    )
                else:
                    line += op_part

        elif insn["id"] == MIPS_INS_LUI:
            symbol_value = symbols.get(vaddr, None)
            if symbol_value is not None:
                line += (
                    f"{mips_gpr_names[insn['rt']]}, %hi({proper_name(symbol_value)})"
                )
            else:
                constant_value = constants.get(vaddr, None)
                if constant_value is not None:
                    line += (
                        f"{mips_gpr_names[insn['rt']]}, (0x{constant_value:08X} >> 16)"
                    )
                else:
                    line += entry["op"][0]

        elif insn["id"] == MIPS_INS_ADDIU or insn["id"] in MIPS_LOAD_STORE_INSNS:
            symbol_value = symbols.get(vaddr, None)
            if symbol_value is not None:
                if insn["id"] == MIPS_INS_ADDIU:
                    line += f"{mips_gpr_names[insn['rt']]}, {mips_gpr_names[insn['rs']]}, %lo({proper_name(symbol_value)})"
                else:
                    line += f"{mips_fpr_names[insn['ft']] if insn['id'] in MIPS_FP_LOAD_STORE_INSNS else mips_gpr_names[insn['rt']]}, %lo({proper_name(symbol_value)})({mips_gpr_names[insn['base']]})"
            else:
                line += entry["op"][0]

        elif insn["id"] == MIPS_INS_ORI:
            constant_value = constants.get(vaddr, None)
            if constant_value is not None:
                line += f"{mips_gpr_names[insn['rt']]}, {mips_gpr_names[insn['rs']]}, (0x{constant_value:08X} & 0xFFFF)"
            else:
                line += entry["op"][0]

        else:
            for part in entry["op"]:
                if type(part) == list:
                    line += (
                        f"{proper_name(part[0], in_data=part[1], is_symbol=part[2])}"
                    )
                else:
                    line += part

        line += "\n"
        text.append(line)

    with open(f"{ASM_OUT}/{segment_dirname}/{info['name']}.text.s", "w") as outfile:
        outfile.write("".join(text))


def disassemble_text(data, vram, data_regions, info):
    result = asm_header(".text")
    raw_insns = as_word_list(data)

    cur_file = ""
    cur_vaddr = 0

    segment_dirname = ("" if info["type"] != "overlay" else "overlays/") + info["name"]
    os.makedirs(f"{ASM_OUT}/{segment_dirname}/", exist_ok=True)

    delayed_insn = None
    delay_slot = False

    for i, raw_insn in enumerate(raw_insns, 0):
        i *= 4
        vaddr = vram + i
        insn = decode_insn(raw_insns[i // 4], vaddr)
        mnemonic = insn.mnemonic
        op_str = insn.op_str

        if vaddr in full_file_list[info["name"]]:
            if cur_file != "":
                if cur_vaddr in info["syms"]:
                    os.makedirs(f"{ASM_OUT}/{segment_dirname}/", exist_ok=True)
                    with open(
                        f"{ASM_OUT}/{segment_dirname}/{cur_file}.text.s", "w"
                    ) as outfile:
                        outfile.write(result)
                result = asm_header(".text")
            cur_vaddr = vaddr
            cur_file = full_file_list[info["name"]][vaddr]
            if cur_file == "":
                cur_file = f"{info['name']}_{vaddr:08X}"

        # DATA EMBEDDED IN TEXT
        in_data = False
        for region in data_regions:
            if vaddr in range(region[0], region[1], 4):
                in_data = True
                break
        if in_data:
            # TODO not really a function if it falls in a data region...
            if vaddr in functions:
                result += f"\nglabel {proper_name(vaddr, True)}\n"
            result += (
                f"/* {i:06X} {vaddr:08X} {raw_insn:08X} */  .word 0x{raw_insn:08X}\n"
            )
            continue

        # LABELS
        if vaddr in functions:
            result += f"\nglabel {proper_name(vaddr)}\n"
        if vaddr in jtbl_labels:
            result += f"glabel L{vaddr:08X}\n"
        if vaddr in branch_labels:
            result += f".L{vaddr:08X}:\n"

        # INSTRUCTIONS FORMATTING/CORRECTING
        if insn.id in MIPS_BRANCH_INSNS:
            op_str_parts = []
            for field in insn.fields:
                if field == "offset":
                    op_str_parts.append(f".L{insn.offset:08X}")
                else:
                    op_str_parts.append(insn.format_field(field))
            op_str = ", ".join(op_str_parts)
            delayed_insn = insn
        elif insn.id in MIPS_JUMP_INSNS:
            op_str_parts = []
            for field in insn.fields:
                if field == "target":
                    op_str_parts.append(proper_name(insn.target, is_symbol=True))
                else:
                    op_str_parts.append(insn.format_field(field))
            op_str = ", ".join(op_str_parts)
            delayed_insn = insn
        elif insn.id == MIPS_INS_LUI:
            symbol_value = symbols.get(vaddr, None)
            if symbol_value is not None:
                op_str = f"{mips_gpr_names[insn.rt]}, %hi({proper_name(symbol_value)})"
            else:
                constant_value = constants.get(vaddr, None)
                if constant_value is not None:
                    op_str = (
                        f"{mips_gpr_names[insn.rt]}, (0x{constant_value:08X} >> 16)"
                    )
        elif insn.id == MIPS_INS_ADDIU or insn.id in MIPS_LOAD_STORE_INSNS:
            symbol_value = symbols.get(vaddr, None)
            if symbol_value is not None:
                if insn.id == MIPS_INS_ADDIU:
                    op_str = f"{mips_gpr_names[insn.rt]}, {mips_gpr_names[insn.rs]}, %lo({proper_name(symbol_value)})"
                else:
                    op_str = f"{mips_fpr_names[insn.ft] if insn.id in MIPS_FP_LOAD_STORE_INSNS else mips_gpr_names[insn.rt]}, %lo({proper_name(symbol_value)})({mips_gpr_names[insn.base]})"
        elif insn.id == MIPS_INS_ORI:
            constant_value = constants.get(vaddr, None)
            if constant_value is not None:
                op_str = f"{mips_gpr_names[insn.rt]}, {mips_gpr_names[insn.rs]}, (0x{constant_value:08X} & 0xFFFF)"

        if delay_slot:
            mnemonic = " " + mnemonic
            delayed_insn = None
        delay_slot = False
        if delayed_insn is not None:
            delay_slot = True

        result += f"/* {i:06X} {vaddr:08X} {raw_insn:08X} */  {mnemonic:12}{op_str}\n"

    with open(f"{ASM_OUT}/{segment_dirname}/{cur_file}.text.s", "w") as outfile:
        outfile.write(result)


def disassemble_data(data, vram, end, info):
    section_symbols = [sym for sym in symbols.values() if sym >= vram and sym < end]
    section_symbols.append(vram)
    section_symbols.extend([sym for sym in data_labels if sym >= vram and sym < end])
    section_symbols.extend(
        [sym for sym in variables_ast.keys() if sym >= vram and sym < end]
    )
    # TODO temp hack, move
    section_symbols.extend(
        [sym for sym in info["syms"].keys() if sym >= vram and sym < end]
    )

    # remove symbols that are addends of other symbols
    section_symbols = [
        sym
        for sym in section_symbols
        if " + 0x" not in proper_name(sym, True)
        and " - 0x" not in proper_name(sym, True)
    ]

    section_symbols = list(set(section_symbols))

    section_symbols.sort()

    segment_dirname = info["name"]
    if info["type"] in ("boot", "code"):
        segment_dirname = info["type"]

    os.makedirs(f"{DATA_OUT}/{segment_dirname}/", exist_ok=True)

    if info["type"] in ("boot", "code"):
        sym_list = full_file_list[info["type"]]
    else:
        sym_list = full_file_list[info["name"]]

    file_syms = []
    syms = []
    file_name = ""
    for i, sym in enumerate(section_symbols):
        if i == 0:
            if info["type"] == "overlay":
                file_name = info["name"]
            else:
                file_name = sym_list[sym]

        if sym in sym_list:
            new_file = sym_list[sym]
            if file_name != new_file:
                file_syms.append(
                    {"name": file_name, "first_sym": syms[0], "syms": syms}
                )
                syms = []
                file_name = new_file
        syms.append(sym)
    if len(syms) > 0:
        file_syms.append({"name": file_name, "first_sym": syms[0], "syms": syms})

    for i, file in enumerate(file_syms):
        if file["first_sym"] not in info["syms"]:
            continue

        result = [asm_header(".data")]

        for x, symbol in enumerate(file["syms"]):
            if symbol >= end:
                break
            if x + 1 < len(file["syms"]):
                next_symbol = file["syms"][x + 1]
            elif i + 1 < len(file_syms):
                next_symbol = file_syms[i + 1]["first_sym"]
            else:
                next_symbol = end

            data_offset = symbol - vram
            data_size = next_symbol - symbol

            if data_offset == len(data):
                continue

            r = f"\nglabel {proper_name(symbol, True)}\n"

            if symbol % 8 == 0 and data_size % 8 == 0 and symbol in doubles:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j * 8:06X} {symbol + j * 8:08X} {dbl_dwd:016X} */ {format_f64(dbl_dwd)}"
                            for j, dbl_dwd in enumerate(
                                as_dword_list(
                                    data[data_offset : data_offset + data_size]
                                ),
                                0,
                            )
                        ]
                    )
                    + "\n"
                )
            elif symbol % 8 == 0 and data_size % 8 == 0 and symbol in dwords:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j * 8:06X} {symbol + j * 8:08X} */ .quad 0x{dword:08X}"
                            for j, dword in enumerate(
                                as_dword_list(
                                    data[data_offset : data_offset + data_size]
                                ),
                                0,
                            )
                        ]
                    )
                    + "\n"
                )
            elif symbol % 4 == 0 and data_size % 4 == 0:
                if symbol in floats:
                    r += (
                        "\n".join(
                            [
                                f"/* {data_offset + j * 4:06X} {symbol + j * 4:08X} {flt_wd:08X} */ {format_f32(flt_wd)}"
                                for j, flt_wd in enumerate(
                                    as_word_list(
                                        data[data_offset : data_offset + data_size]
                                    ),
                                    0,
                                )
                            ]
                        )
                        + "\n"
                    )
                else:
                    r += (
                        "\n".join(
                            [
                                f"/* {data_offset + j * 4:06X} {symbol + j * 4:08X} */ .word {lookup_name(symbol, word)}"
                                for j, word in enumerate(
                                    as_word_list(
                                        data[data_offset : data_offset + data_size]
                                    ),
                                    0,
                                )
                            ]
                        )
                        + "\n"
                    )
            elif symbol % 2 == 0 and data_size % 2 == 0:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j * 2:06X} {symbol + j * 2:08X} */ .half 0x{hword:04X}"
                            for j, hword in enumerate(
                                as_hword_list(
                                    data[data_offset : data_offset + data_size]
                                ),
                                0,
                            )
                        ]
                    )
                    + "\n"
                )
            else:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j:06X} {symbol + j:08X} */ .byte 0x{byte:02X}"
                            for j, byte in enumerate(
                                data[data_offset : data_offset + data_size], 0
                            )
                        ]
                    )
                    + "\n"
                )
            result.append(r)

        if len(result) > 1:
            with open(
                f"{DATA_OUT}/{segment_dirname}/{file['name']}.data.s", "w"
            ) as outfile:
                outfile.write("".join(result))


def disassemble_rodata(data, vram, end, info):
    section_symbols = [sym for sym in symbols.values() if sym >= vram and sym < end]
    section_symbols.append(vram)
    section_symbols.extend([sym for sym in data_labels if sym >= vram and sym < end])
    section_symbols.extend(
        [sym for sym in variables_ast.keys() if sym >= vram and sym < end]
    )
    # TODO temp hack, move
    section_symbols.extend(
        [sym for sym in info["syms"].keys() if sym >= vram and sym < end]
    )

    # remove symbols that are addends of other symbols
    section_symbols = [
        sym
        for sym in section_symbols
        if " + 0x" not in proper_name(sym, True)
        and " - 0x" not in proper_name(sym, True)
    ]

    section_symbols = list(set(section_symbols))

    if len(section_symbols) == 0:
        return

    section_symbols.sort()

    segment_dirname = info["name"]
    if info["type"] in ("boot", "code"):
        segment_dirname = info["type"]
    os.makedirs(f"{DATA_OUT}/{segment_dirname}/", exist_ok=True)

    if info["type"] in ("boot", "code"):
        sym_list = full_file_list[info["type"]]
    else:
        sym_list = full_file_list[info["name"]]

    force_ascii_str = False  # hack for non-null-terminated strings in .data

    file_syms = []
    syms = []
    file_name = ""
    for i, sym in enumerate(section_symbols):
        if i == 0:
            if info["type"] == "overlay":
                file_name = info["name"]
            else:
                file_name = sym_list[sym]

        if sym in sym_list:
            new_file = sym_list[sym]
            if file_name != new_file:
                file_syms.append(
                    {"name": file_name, "first_sym": syms[0], "syms": syms}
                )
                syms = []
                file_name = new_file
        syms.append(sym)
    if len(syms) > 0:
        file_syms.append({"name": file_name, "first_sym": syms[0], "syms": syms})

    for i, file in enumerate(file_syms):
        if file["first_sym"] not in info["syms"]:
            continue

        result = [asm_header(".rodata")]

        for x, symbol in enumerate(file["syms"]):
            if symbol >= end:
                break
            if x + 1 < len(file["syms"]):
                next_symbol = file["syms"][x + 1]
            elif i + 1 < len(file_syms):
                next_symbol = file_syms[i + 1]["first_sym"]
            else:
                next_symbol = end

            data_offset = symbol - vram
            data_size = next_symbol - symbol

            if data_offset == len(data):
                continue

            force_ascii_str = symbol in [0x801D0708]

            r = f"\nglabel {proper_name(symbol, True)}\n"

            if symbol in strings:
                string_data = data[data_offset : data_offset + data_size]
                string_data = string_data[: string_data.index(0)]
                # ensure strings don't have a null char midway through
                assert all(
                    [b != 0 for b in string_data[:-1]]
                ), f"{symbol:08X} , {data_size:X} , {string_data}"
                r += f"/* {data_offset:06X} {symbol:08X} */ {try_decode_string(string_data, force_ascii=force_ascii_str)}\n{STR_INDENT}.balign 4\n"
            elif symbol % 8 == 0 and data_size % 8 == 0 and symbol in doubles:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j * 8:06X} {symbol + j * 8:08X} {dbl_dwd:016X} */ {format_f64(dbl_dwd)}"
                            for j, dbl_dwd in enumerate(
                                as_dword_list(
                                    data[data_offset : data_offset + data_size]
                                ),
                                0,
                            )
                        ]
                    )
                    + "\n"
                )
            elif symbol % 4 == 0 and data_size % 4 == 0:
                if symbol in floats:
                    r += (
                        "\n".join(
                            [
                                f"/* {data_offset + j * 4:06X} {symbol + j * 4:08X} {flt_wd:08X} */ {format_f32(flt_wd)}"
                                for j, flt_wd in enumerate(
                                    as_word_list(
                                        data[data_offset : data_offset + data_size]
                                    ),
                                    0,
                                )
                            ]
                        )
                        + "\n"
                    )
                else:
                    r += (
                        "\n".join(
                            [
                                f"/* {data_offset + j * 4:06X} {symbol + j * 4:08X} */ .word {lookup_name(symbol, word)}"
                                for j, word in enumerate(
                                    as_word_list(
                                        data[data_offset : data_offset + data_size]
                                    ),
                                    0,
                                )
                            ]
                        )
                        + "\n"
                    )
            elif symbol % 2 == 0 and data_size % 2 == 0:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j * 2:06X} {symbol + j * 2:08X} */ .half 0x{hword:04X}"
                            for j, hword in enumerate(
                                as_hword_list(
                                    data[data_offset : data_offset + data_size]
                                ),
                                0,
                            )
                        ]
                    )
                    + "\n"
                )
            else:
                r += (
                    "\n".join(
                        [
                            f"/* {data_offset + j:06X} {symbol + j:08X} */ .byte 0x{byte:02X}"
                            for j, byte in enumerate(
                                data[data_offset : data_offset + data_size], 0
                            )
                        ]
                    )
                    + "\n"
                )

            result.append(r)

        if len(result) > 1:
            with open(
                f"{DATA_OUT}/{segment_dirname}/{file['name']}.rodata.s", "w"
            ) as outfile:
                outfile.write("".join(result))


def disassemble_bss(vram, end, info):
    section_symbols = [sym for sym in symbols.values() if sym >= vram and sym < end]
    section_symbols.append(vram)
    section_symbols.extend([sym for sym in data_labels if sym >= vram and sym < end])
    section_symbols.extend(
        [sym for sym in variables_ast.keys() if sym >= vram and sym < end]
    )
    # TODO temp hack, move
    section_symbols.extend(
        [sym for sym in info["syms"].keys() if sym >= vram and sym < end]
    )

    # remove symbols that are addends of other symbols
    section_symbols = [
        sym
        for sym in section_symbols
        if " + 0x" not in proper_name(sym, True)
        and " - 0x" not in proper_name(sym, True)
    ]

    section_symbols = list(set(section_symbols))

    section_symbols.sort()

    # ("" if info["type"] != "overlay" else "overlays/"
    segment_dirname = (
        info["name"] if info["type"] not in ("boot", "code") else info["type"]
    )
    os.makedirs(f"{DATA_OUT}/{segment_dirname}/", exist_ok=True)

    if info["type"] in ("boot", "code"):
        sym_list = full_file_list[info["type"]]
    else:
        sym_list = full_file_list[info["name"]]

    file_syms = []
    syms = []
    file_name = ""
    for i, sym in enumerate(section_symbols):
        if i == 0:
            if info["type"] == "overlay":
                file_name = info["name"]
            else:
                file_name = sym_list[sym]

        if sym in sym_list:
            new_file = sym_list[sym]
            if file_name != new_file:
                file_syms.append(
                    {"name": file_name, "first_sym": syms[0], "syms": syms}
                )
                syms = []
                file_name = new_file
        syms.append(sym)
    if len(syms) > 0:
        file_syms.append({"name": file_name, "first_sym": syms[0], "syms": syms})

    for i, file in enumerate(file_syms):
        if file["first_sym"] not in info["syms"]:
            continue

        result = [asm_header(".bss")]

        for x, symbol in enumerate(file["syms"]):
            if symbol >= end:
                break
            if x + 1 < len(file["syms"]):
                next_symbol = file["syms"][x + 1]
            elif i + 1 < len(file_syms):
                next_symbol = file_syms[i + 1]["first_sym"]
            else:
                next_symbol = end

            result.append(f"\nglabel {proper_name(symbol, True)}\n")
            result.append(
                f"/* {symbol - vram:06X} {symbol:08X} */ .space 0x{next_symbol - symbol:X}\n"
            )

        if len(result) > 1:
            with open(
                f"{DATA_OUT}/{segment_dirname}/{file['name']}.bss.s", "w"
            ) as outfile:
                outfile.write("".join(result))


def get_overlay_sections(vram, overlay):
    header_loc = len(overlay) - as_word_list(overlay)[-1]
    text_size, data_size, rodata_size, bss_size, n_relocs = as_word_list(
        overlay[header_loc : header_loc + 0x14]
    )
    text_vram = vram
    data_vram = vram + text_size
    rodata_vram = data_vram + data_size

    bss_vram = vram + len(overlay)
    bss_end_vram = bss_vram + bss_size

    reloc = as_word_list(overlay[header_loc + 0x14 : header_loc + 0x14 + n_relocs * 4])
    reloc = [
        (
            (rel >> 30) & ((1 << 2) - 1),
            (rel >> 24) & ((1 << 6) - 1),
            (rel) & ((1 << 24) - 1),
        )
        for rel in reloc
    ]

    rel_text = [r for r in reloc if r[0] == 1]
    rel_data = [r for r in reloc if r[0] == 2]
    rel_rodata = [r for r in reloc if r[0] == 3]
    rel_bss = [r for r in reloc if r[0] == 4]

    return [
        [text_vram, data_vram, "text", None, overlay[0:text_size], rel_text],
        [
            data_vram,
            rodata_vram,
            "data",
            None,
            overlay[text_size : text_size + data_size],
            rel_data,
        ],
        [
            rodata_vram,
            bss_vram,
            "rodata",
            None,
            overlay[text_size + data_size : text_size + data_size + rodata_size],
            rel_rodata,
        ],
        [bss_vram, bss_end_vram, "bss", None, None, rel_bss],
        [bss_end_vram, bss_end_vram, "reloc", None, overlay[header_loc:], None],
    ]


def disassemble_makerom(section):
    os.makedirs(f"{ASM_OUT}/makerom/", exist_ok=True)

    if section[2] == "rom_header":
        (
            pi_dom1_reg,
            clockrate,
            entrypoint,
            revision,
            chksum1,
            chksum2,
            pad1,
            pad2,
            rom_name,
            pad3,
            cart,
            cart_id,
            region,
            version,
        ) = struct.unpack(">IIIIIIII20sII2s1sB", section[4])

        out = f"""/*
 * The Legend of Zelda: Majora's Mask ROM header
 */

.word  0x{pi_dom1_reg:08X}             /* PI BSD Domain 1 register */
.word  0x{clockrate:08X}             /* Clockrate setting */
.word  0x{entrypoint:08X}             /* Entrypoint function (`entrypoint`) */
.word  0x{revision:08X}             /* Revision */
.word  0x{chksum1:08X}             /* Checksum 1 */
.word  0x{chksum2:08X}             /* Checksum 2 */
.word  0x{pad1:08X}             /* Unknown */
.word  0x{pad2:08X}             /* Unknown */
.ascii "{rom_name.decode('ascii')}" /* Internal ROM name */
.word  0x{pad3:08X}             /* Unknown */
.word  0x{cart:08X}             /* Cartridge */
.ascii "{cart_id.decode('ascii')}"                   /* Cartridge ID */
.ascii "{region.decode('ascii')}"                    /* Region */
.byte  0x{version:02X}                   /* Version */
"""
        with open(ASM_OUT + "/makerom/rom_header.s", "w") as outfile:
            outfile.write(out)

    elif section[-1]["type"] == "ipl3":
        # TODO disassemble this eventually, low priority
        out = f"{asm_header('.text')}\n.incbin \"baserom/makerom\", 0x40, 0xFC0\n"

        with open(ASM_OUT + "/makerom/ipl3.s", "w") as outfile:
            outfile.write(out)

    elif section[-1]["type"] == "entry":
        # hack: add symbol relocations manually
        entry_addr = 0x80080000

        functions.add(entry_addr)
        symbols.update(
            {
                entry_addr + 0x00: 0x80099500,
                entry_addr + 0x04: 0x80099500,
                entry_addr + 0x20: 0x80080060,
                entry_addr + 0x24: 0x80099EF0,
                entry_addr + 0x28: 0x80080060,
                entry_addr + 0x30: 0x80099EF0,
            }
        )
        branch_labels.add(entry_addr + 0xC)
        disassemble_text(section[4], entry_addr, [], section[-1])

        # manually set boot bss size...
        entry_asm = ""
        with open(f"{ASM_OUT}/makerom/entry.text.s") as infile:
            entry_asm = infile.read()

        entry_asm = entry_asm.replace("0x63b0", "%lo(_bootSegmentBssSize)")
        with open(f"{ASM_OUT}/makerom/entry.s", "w") as outfile:
            outfile.write(entry_asm)

        os.remove(f"{ASM_OUT}/makerom/entry.text.s")


def disassemble_dmadata(section):
    if section[2] == "bss":
        return
    os.makedirs(f"{ASM_OUT}/dmadata/", exist_ok=True)
    out = f""".include "macro.inc"

.macro DMA_TABLE_ENTRY segment
    .4byte _\segment\()SegmentRomStart
    .4byte _\segment\()SegmentRomEnd
    .4byte _\segment\()SegmentRomStart
    .4byte 0x00000000
.endm

.macro DMA_TABLE_ENTRY_UNSET segment
    .4byte _\segment\()SegmentRomStart
    .4byte _\segment\()SegmentRomEnd
    .word 0xFFFFFFFF
    .word 0xFFFFFFFF
.endm

glabel {variables_ast[0x8009F8B0][0]}
"""
    filenames = []
    with open("tools/disasm/dma_filenames.txt", "r") as infile:
        filenames = ast.literal_eval(infile.read())

    dmadata = section[4]
    i = 0
    dmadata_entry = dmadata[i * 0x10 : (i + 1) * 0x10]
    while any([word != 0 for word in as_word_list(dmadata_entry)]):
        vrom_start, vrom_end, prom_start, prom_end = as_word_list(dmadata_entry)
        if prom_start == 0xFFFFFFFF and prom_end == 0xFFFFFFFF:
            out += f"DMA_TABLE_ENTRY_UNSET {filenames[i]}\n"
        else:
            out += f"DMA_TABLE_ENTRY {filenames[i]}\n"

        vrom_variables.append(("_" + filenames[i] + "SegmentRomStart", vrom_start))
        vrom_variables.append(("_" + filenames[i] + "SegmentRomEnd", vrom_end))

        i += 1
        dmadata_entry = dmadata[i * 0x10 : (i + 1) * 0x10]

    out += """
.space 0x100

.section .bss

.space 0x10
"""
    with open(ASM_OUT + "/dmadata/dmadata.s", "w") as outfile:
        outfile.write(out)


def disassemble_segment(section):
    if section[-1]["name"] == "[PADDING]":
        return

    print(f"Disassembling {section[-1]['name']} .{section[2]}")

    if section[2] == "text":
        fixup_text_symbols(section[4], section[0], data_regions, section[-1])
    elif section[2] == "data":
        disassemble_data(section[4], section[0], section[1], section[-1])
    elif section[2] == "rodata":
        disassemble_rodata(section[4], section[0], section[1], section[-1])
    elif section[2] == "bss":
        disassemble_bss(section[0], section[1], section[-1])
    elif section[2] == "reloc":
        words = as_word_list(section[4])

        segment_dirname = section[-1]["name"]

        result = asm_header(".rodata")
        result += f"\nglabel {section[-1]['name']}_Reloc\n"

        lines = [words[i * 8 : (i + 1) * 8] for i in range(0, (len(words) // 8) + 1)]
        for line in [line for line in lines if len(line) != 0]:
            result += f"    .word {', '.join([f'0x{word:08X}' for word in line])}\n"

        os.makedirs(f"{DATA_OUT}/{segment_dirname}/", exist_ok=True)
        with open(
            f"{DATA_OUT}/{segment_dirname}/{section[-1]['name']}.reloc.s", "w"
        ) as outfile:
            outfile.write(result)


def rodata_block_size(block):
    def align(x, n):
        while x % n != 0:
            x += 1
        return x

    accumulator = 0
    for part in block.split(" */ ."):
        part = part.strip()
        if part.startswith("# "):
            continue
        elif part.startswith("asciz "):
            part = part[len("asciz ") :]
            string = part[1:-1].encode("utf-8", "ignore").decode("unicode_escape")
            accumulator += len(string.encode("euc-jp") + b"\x00")
        elif part.startswith("ascii"):
            part = part[len("ascii ") :]
            string = part[1:-1].encode("utf-8", "ignore").decode("unicode_escape")
            accumulator += len(string.encode("euc-jp"))
        elif part.startswith("balign "):
            part = part[len("balign ") :]
            accumulator = align(
                accumulator, int(part, 16 if part.startswith("0x") else 10)
            )
        elif part.startswith("double "):
            part = part[len("double ") :]
            accumulator = align(accumulator, 8)
            accumulator += 8 * (part.count(",") + 1)
        elif part.startswith("float "):
            part = part[len("float ") :]
            accumulator = align(accumulator, 4)
            accumulator += 4 * (part.count(",") + 1)
        elif part.startswith("word "):
            part = part[len("word ") :]
            accumulator = align(accumulator, 4)
            accumulator += 4 * (part.count(",") + 1)
        elif part.startswith("half "):
            part = part[len("half ") :]
            accumulator = align(accumulator, 2)
            accumulator += 2 * (part.count(",") + 1)
        elif part.startswith("byte "):
            part = part[len("byte ") :]
            accumulator += 1 * (part.count(",") + 1)
    return accumulator


def late_rodata_size(blocks):
    return sum([rodata_block_size(block) for block in blocks])


def text_block_size(asm):
    return 4 * len([line for line in asm.split("\n") if line.startswith("/*")])


def rodata_syms(rodata):
    return re.findall(rodata_symbols_regex, rodata)


def rodata_blocks(rodata):
    return ["glabel" + b for b in rodata.split("glabel")[1:]]


def find_late_rodata_start(rodata):
    """
    Returns the symbol that is the first late_rodata symbol, or None if there is no late_rodata

    Note this is approximate as const qualified floats/doubles end up in rdata and not late_rodata,
        so there may be some overlap. This should not pose much of a problem however.
    Also note that this method assumes the input rodata consists only of at most one block rodata and one block late_rodata,
        that is that the file splits are correct.
    """
    first = None

    for sym, body in rodata:
        if sym.startswith("jtbl_") and ".word L" in body:
            # jump tables are always late_rodata, so we can return early
            # floats and doubles are very rarely not late_rodata, this is mostly seen in libultra, so we cannot return early for those
            if first is not None:
                return first
            else:
                return sym
        elif (".float " in body or ".double " in body) and first is None:
            # may be late_rodata, but we aren't sure yet
            # it is confirmed either by reaching the end or by finding a jumptable, and it is proven wrong if something that is not late_rodata occurs after it
            first = sym
        elif (
            ".asciz" in body
            or (".word " in body and ".float" not in body)
            or ".half " in body
            or ".byte " in body
        ) and first is not None:
            # reset first if something that is definitely not late_rodata is found
            # word and not float is due to some floats needing to be output as words either due to being a specific NaN value, or GAS can't convert it properly
            first = None
    # May still be None at this point, that just means there is no late_rodata
    return first


# ==========================================#

print("Setting Up")

files_spec = None
with open("tools/disasm/files.txt", "r") as infile:
    files_spec = ast.literal_eval(infile.read())

with open("tools/disasm/functions.txt", "r") as infile:
    functions_ast = ast.literal_eval(infile.read())

with open("tools/disasm/variables.txt", "r") as infile:
    variables_ast = ast.literal_eval(infile.read())

# We need to keep a full list of original file offsets to know where to split files later
full_file_list = {}
for segment in files_spec:
    new = {}
    for offset, name in segment[4].items():
        if name == "":
            name = f"{segment[2]}_{offset:08X}"
        new[offset] = name
    full_file_list[segment[0]] = new

if args.full:
    for segment in files_spec:
        for offset, name in segment[4].items():
            if name == "":
                name = f"{segment[2]}_{offset:08X}"
            segment[4][offset] = name
else:
    # Prune
    old_file_count = sum([len(f[4].keys()) for f in files_spec])

    files_spec = discard_decomped_files(files_spec)

    new_file_count = sum([len(f[4].keys()) for f in files_spec])

    pruned = old_file_count - new_file_count
    print(f"Pruned {pruned}/{old_file_count} files ({pruned / old_file_count:.02%})")

# Precompute variable addends for all variables, this uses a lot of memory but the lookups later are fast
for var in sorted(variables_ast.keys()):
    for i in range(var, var + variables_ast[var][3], 1):
        addend = i - var
        assert addend >= 0
        vars_cache.update(
            {i: f"{variables_ast[var][0]}" + (f" + 0x{addend:X}" if addend > 0 else "")}
        )
    # also add to floats, doubles & strings
    var_type = variables_ast[var][1]

    if var_type == "f64":
        doubles.add(var)
    elif var_type == "f32":
        floats.add(var)
    elif var_type == "char" and variables_ast[var][2].startswith("["):
        strings.add(var)

# Read in binary and relocation data for each segment
for seg, segment in enumerate(files_spec):
    binary = None
    with open(segment[1] + "/" + segment[0], "rb") as infile:
        binary = bytes(infile.read())

    if segment[2] == "overlay":
        segment_start = list(segment[4])[0]  # start addr of first file in segment
        segment[3] = get_overlay_sections(segment_start, binary)
        segment[4] = {}
        for section in segment[3]:
            segment[4].update({section[0]: segment[0]})
    else:
        # start addr of first section of segment's sections
        segment_start = segment[3][0][0]
        # read section binary regions
        for i, section in enumerate(segment[3]):
            if section[2] == "bss":
                continue
            # section[4]
            section.append(
                binary[section[0] - segment_start : section[1] - segment_start]
            )
            section.append(None)  # section[5]

print(f"Finding segment positions")

for segment in files_spec:
    if segment[2] == "makerom":
        continue

    print(f"Finding segment positions in {segment[0]}")

    # vram segment start
    if segment[3][0][0] not in variables_ast:
        variables_ast.update(
            {segment[3][0][0]: (f"_{segment[0]}SegmentStart", "u8", "[]", 0x1)}
        )
    # vram segment end
    if segment[3][-2][1] not in variables_ast:
        variables_ast.update(
            {segment[3][-2][1]: (f"_{segment[0]}SegmentEnd", "u8", "[]", 0x1)}
        )

# Flatten out files_spec so we can process everything evenly
# Otherwise the entire code and boot sections are done by a single thread
all_sections = []
for segment in files_spec:
    if segment[0] == "boot" or segment[0] == "code":
        file_list = list(full_file_list[segment[0]])
        section_starts = [x[0] for x in segment[3]]

        for off, name in segment[4].items():
            # loop over the vram starts for this segment's sections to find where it belongs (text, data, etc)
            for i, s in enumerate(section_starts):
                if off < s:
                    break
            else:
                i = len(section_starts)
            i -= 1

            # Calculate the offset and size of this section relative to the section
            data_offset = off - segment[3][i][0]
            full_index = file_list.index(off)
            if segment[0] == "code" and name == "buffers" and segment[3][i][2] == "bss":
                # This is the end of code, hardcode it
                data_size = 0x80800000 - file_list[full_index]
            elif segment[0] == "boot" and name == "vimgr" and segment[3][i][2] == "bss":
                # This is the end of boot, hardcode it
                data_size = 0x800A5AC0 - file_list[full_index]
            else:
                data_size = file_list[full_index + 1] - file_list[full_index]

            # Create the section entry for this file
            new_entry = [
                off,
                off + data_size,
                segment[3][i][2],
                None,
                segment[3][i][4][data_offset : data_offset + data_size]
                if segment[3][i][2] not in ("bss")
                else None,
                None if segment[3][i][2] in ["text", "reloc", "data"] else [],
                {
                    "name": name,
                    "type": segment[2],
                    "syms": {
                        x: name for x in segment[4] if x >= off and x < off + data_size
                    },
                },
            ]

            all_sections.append(new_entry)

    # I don't remember what this is for but it's still needed
    for i, entry in enumerate(segment[3]):
        if segment[0] == "makerom" and i == 1:
            segment[2] = "ipl3"
        elif segment[0] == "makerom" and i == 2:
            segment[2] = "entry"
        entry.append({"name": segment[0], "type": segment[2], "syms": segment[4]})

    all_sections.extend(segment[3])

del files_spec[:]

pool = Pool(jobs)
# Find symbols for each segment
for section in all_sections:
    if section[-1]["name"] == "makerom":
        continue

    if section[2] == "text":
        data_regions = []
        if section[3] is not None:
            for override_region in section[3]:
                if override_region[2] == "data":
                    data_regions.append((override_region[0], override_region[1]))
        # try find a rodata section
        for s in all_sections:
            if (
                s[-1]["name"] == section[-1]["name"]
                and s[2] == "rodata"
                and s[0] != s[1]
            ):
                rodata_section = s
                break
        else:
            rodata_section = None
        pool.apply_async(
            find_symbols_in_text,
            args=(section, rodata_section if rodata_section else None, data_regions),
            callback=update_symbols_from_dict,
        )
    elif section[2] == "data":
        pool.apply_async(
            find_symbols_in_data, args=(section), callback=update_symbols_from_dict
        )

pool.close()
pool.join()

pool = Pool(jobs)
for section in all_sections:
    if section[-1]["type"] == "makerom":
        continue

    if section[2] == "rodata":
        pool.apply_async(
            find_symbols_in_rodata, args=(section), callback=update_symbols_from_dict
        )

pool.close()
pool.join()

for section in all_sections:
    if section[-1]["name"] == "makerom":
        print(f"Disassembling makerom")
        disassemble_makerom(section)
    elif section[-1]["name"] == "dmadata":
        print(f"Disassembling dmadata")
        disassemble_dmadata(section)

# Textual disassembly for each segment
with Pool(jobs) as p:
    p.map(
        disassemble_segment,
        [
            sec
            for sec in all_sections
            if sec[-1]["name"] not in ("boot", "code", "makerom", "dmadata")
        ],
    )

print("Splitting text and migrating rodata")

func_regex = re.compile(r"\n\nglabel \S+\n")
rodata_symbols_regex = re.compile(r"(?<=\n)glabel (.+)(?=\n)")
asm_symbols_regex = re.compile(r"%(?:lo|hi)\((.+?)\)")

# Split files and migrate rodata that should be migrated
for root, dirs, files in os.walk(ASM_OUT):
    for f in files:
        if "non_matchings" in root:
            continue
        asm_path = os.path.join(root, f)
        rodata_path = (
            asm_path.replace(ASM_OUT + "overlays/", DATA_OUT)
            .replace(ASM_OUT, DATA_OUT)
            .replace(".text.s", ".rodata.s")
        )

        print(asm_path)

        asm = ""
        with open(asm_path, "r") as infile:
            asm = infile.read()

        rodata = ""
        if os.path.exists(rodata_path):
            # print(rodata_path)
            with open(rodata_path, "r") as rodata_file:
                rodata = rodata_file.read()

            rodata_info = list(zip(rodata_syms(rodata), rodata_blocks(rodata)))

            # populate rdata and late_rodata lists
            first_late_rodata = find_late_rodata_start(rodata_info)
            rdata_info = []
            late_rodata_info = []
            target = rdata_info  # first populate rdata
            for sym, block in rodata_info:
                # now populate late_rodata, if there is any
                if sym == first_late_rodata:
                    target = late_rodata_info
                target.append((sym, block))

        # print([(sym,block.split("\n")[1:]) for sym,block in zip(rdata_syms,rdata_blocks)])

        function_info = list(
            zip(
                [s.replace("glabel", "").strip() for s in func_regex.findall(asm)],
                func_regex.split(asm)[1:],
            )
        )

        rdata_map = {}
        late_rodata_map = {}

        # pass 1 to resolve rodata splits
        if rodata != "":
            last_fn = None

            referenced_in = {}  # key=rodata label , value=function label

            for sym, _ in rodata_info:
                all_refs = [
                    label for label, body in function_info if "%lo(" + sym + ")" in body
                ]
                # ignore multiple refs, take only the first
                referenced_in.update({sym: all_refs[0] if len(all_refs) != 0 else None})

            def do_splits(out_dict, info):
                first = True
                last_ref = None
                cr = None
                for sym, block in info:
                    ref = referenced_in[sym]
                    if first:
                        cr = ref or sym

                    if ref is not None and not first:
                        if ref != last_ref:
                            # existing function
                            cr = ref
                    elif last_ref is not None:
                        # new GLOBAL_ASM
                        cr = sym

                    # add to output
                    if cr not in out_dict.keys():
                        out_dict.update({cr: []})
                    out_dict[cr].append((sym, block))

                    # setup next iter
                    last_ref = ref
                    first = False

            do_splits(rdata_map, rdata_info)
            do_splits(late_rodata_map, late_rodata_info)

        # all output files, order is irrelevant at this point
        all_output = set([label for label, _ in function_info]).union(
            set(rdata_map.keys()), set(late_rodata_map.keys())
        )

        # pass 2 to output splits
        for label in all_output:
            fn_body = dict(function_info).get(label, None)

            text_out = ""
            rodata_out = ""

            if fn_body is not None:
                text_out = "glabel " + label.strip() + "\n" + fn_body.strip() + "\n"

            if rodata != "":
                rdata = rdata_map.get(label, None)
                late_rodata = late_rodata_map.get(label, None)

                # check for late_rodata_alignment
                late_rodata_alignment = ""
                if fn_body is not None and late_rodata is not None:
                    ratio = late_rodata_size(
                        [block for _, block in late_rodata]
                    ) / text_block_size(fn_body)
                    if ratio > 1.0 / 3:
                        # print(f"{label} : {ratio}")
                        # TODO hack: getting the address from a comment
                        first_block_split = late_rodata[0][1].split(" */ .")
                        vaddr = None
                        if first_block_split[1].startswith(
                            "float"
                        ) or first_block_split[1].startswith("double"):
                            vaddr = first_block_split[0].split(" ")[-2]
                        else:
                            vaddr = first_block_split[0].split(" ")[-1]
                        assert vaddr is not None
                        vaddr = int(vaddr, 16)
                        if vaddr not in [
                            0x801E0E28,
                            0x80C1C2B0,
                            0x80AA7820,
                            0x80AA3CC0,
                            0x80AA418C,
                            0x80BE0160,
                            0x80B591D8,
                            0x80B59610,
                            0x80B59780,
                            0x80964E00,
                            0x80964F10,
                            0x80BB40A0,
                            0x80952038,
                            0x80AFB920,
                            0x80AFBBFC,
                            0x80AFBE28,
                            0x80983320,
                        ]:
                            # hacks for especially badly behaved rodata, TODO these are ALL jumptables associated with
                            # comparatively tiny functions, can we swat these programmatically?
                            late_rodata_alignment = f".late_rodata_alignment {'8' if vaddr % 8 == 0 else '4'}\n"

                rdata_out = ""
                if rdata is not None:
                    rdata_out = ".rdata\n" + "".join([block for _, block in rdata])

                late_rodata_out = ""
                if late_rodata is not None:
                    late_rodata_out = (
                        ".late_rodata\n"
                        + late_rodata_alignment
                        + "".join([block for _, block in late_rodata])
                    )

                rodata_out = (
                    rdata_out
                    + late_rodata_out
                    + (
                        "\n.text\n"
                        if (
                            (rdata is not None or late_rodata is not None)
                            and fn_body is not None
                        )
                        else ""
                    )
                )

            all_out = rodata_out + text_out

            # write it out
            out_path = (
                root.replace(ASM_OUT, f"{ASM_OUT}/non_matchings/")
                + "/"
                + ((f.replace(".text.s", "") + "/") if "overlays" not in root else "")
            )
            os.makedirs(out_path, exist_ok=True)
            with open(out_path + label + ".s", "w") as outfile:
                outfile.write(all_out.strip() + "\n")

            # remove rodata and unsplit file
            # TODO
