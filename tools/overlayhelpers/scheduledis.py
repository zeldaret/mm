#!/usr/bin/env python3
#
#   MM Event Script Disassembler
#

import argparse, os, struct, math
from actor_symbols import resolve_symbol

cmd_info = [
    ('SCHEDULE_CMD_CHECK_FLAG_S',         0x04, '>Hb',    (1, )),
    ('SCHEDULE_CMD_CHECK_FLAG_L',         0x05, '>Hh',    (1, )),
    ('SCHEDULE_CMD_CHECK_TIME_RANGE_S',   0x06, '>BBBBb', (4, )),
    ('SCHEDULE_CMD_CHECK_TIME_RANGE_L',   0x07, '>BBBBh', (4, )),
    ('SCHEDULE_CMD_RET_VAL_L',            0x03, '>H',     (   )),
    ('SCHEDULE_CMD_RET_NONE',             0x01, '',       (   )),
    ('SCHEDULE_CMD_RET_EMPTY',            0x01, '',       (   )),
    ('SCHEDULE_CMD_NOP',                  0x04, '>BBB',   (   )),
    ('SCHEDULE_CMD_CHECK_MISC_S',         0x03, '>Bb',    (1, )),
    ('SCHEDULE_CMD_RET_VAL_S',            0x02, '>B',     (   )),
    ('SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S', 0x04, '>Hb',    (1, )),
    ('SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L', 0x05, '>Hh',    (1, )),
    ('SCHEDULE_CMD_CHECK_NOT_IN_DAY_S',   0x04, '>Hb',    (1, )),
    ('SCHEDULE_CMD_CHECK_NOT_IN_DAY_L',   0x05, '>Hh',    (1, )),
    ('SCHEDULE_CMD_RET_TIME',             0x06, '>BBBBB', (   )),
    ('SCHEDULE_CMD_CHECK_BEFORE_TIME_S',  0x04, '>BBb',   (2, )),
    ('SCHEDULE_CMD_CHECK_BEFORE_TIME_L',  0x05, '>BBh',   (2, )),
    ('SCHEDULE_CMD_BRANCH_S',             0x02, '>b',     (0, )),
    ('SCHEDULE_CMD_BRANCH_L',             0x03, '>h',     (0, )),
]

scene_names = [
    'SCENE_20SICHITAI2',
    'SCENE_UNSET_1',
    'SCENE_UNSET_2',
    'SCENE_UNSET_3',
    'SCENE_UNSET_4',
    'SCENE_UNSET_5',
    'SCENE_UNSET_6',
    'SCENE_KAKUSIANA',
    'SCENE_SPOT00',
    'SCENE_UNSET_9',
    'SCENE_WITCH_SHOP',
    'SCENE_LAST_BS',
    'SCENE_HAKASHITA',
    'SCENE_AYASHIISHOP',
    'SCENE_UNSET_E',
    'SCENE_UNSET_F',
    'SCENE_OMOYA',
    'SCENE_BOWLING',
    'SCENE_SONCHONOIE',
    'SCENE_IKANA',
    'SCENE_KAIZOKU',
    'SCENE_MILK_BAR',
    'SCENE_INISIE_N',
    'SCENE_TAKARAYA',
    'SCENE_INISIE_R',
    'SCENE_OKUJOU',
    'SCENE_OPENINGDAN',
    'SCENE_MITURIN',
    'SCENE_13HUBUKINOMITI',
    'SCENE_CASTLE',
    'SCENE_DEKUTES',
    'SCENE_MITURIN_BS',
    'SCENE_SYATEKI_MIZU',
    'SCENE_HAKUGIN',
    'SCENE_ROMANYMAE',
    'SCENE_PIRATE',
    'SCENE_SYATEKI_MORI',
    'SCENE_SINKAI',
    'SCENE_YOUSEI_IZUMI',
    'SCENE_KINSTA1',
    'SCENE_KINDAN2',
    'SCENE_TENMON_DAI',
    'SCENE_LAST_DEKU',
    'SCENE_22DEKUCITY',
    'SCENE_KAJIYA',
    'SCENE_00KEIKOKU',
    'SCENE_POSTHOUSE',
    'SCENE_LABO',
    'SCENE_DANPEI2TEST',
    'SCENE_UNSET_31',
    'SCENE_16GORON_HOUSE',
    'SCENE_33ZORACITY',
    'SCENE_8ITEMSHOP',
    'SCENE_F01',
    'SCENE_INISIE_BS',
    'SCENE_30GYOSON',
    'SCENE_31MISAKI',
    'SCENE_TAKARAKUJI',
    'SCENE_UNSET_3A',
    'SCENE_TORIDE',
    'SCENE_FISHERMAN',
    'SCENE_GORONSHOP',
    'SCENE_DEKU_KING',
    'SCENE_LAST_GORON',
    'SCENE_24KEMONOMITI',
    'SCENE_F01_B',
    'SCENE_F01C',
    'SCENE_BOTI',
    'SCENE_HAKUGIN_BS',
    'SCENE_20SICHITAI',
    'SCENE_21MITURINMAE',
    'SCENE_LAST_ZORA',
    'SCENE_11GORONNOSATO2',
    'SCENE_SEA',
    'SCENE_35TAKI',
    'SCENE_REDEAD',
    'SCENE_BANDROOM',
    'SCENE_11GORONNOSATO',
    'SCENE_GORON_HAKA',
    'SCENE_SECOM',
    'SCENE_10YUKIYAMANOMURA',
    'SCENE_TOUGITES',
    'SCENE_DANPEI',
    'SCENE_IKANAMAE',
    'SCENE_DOUJOU',
    'SCENE_MUSICHOUSE',
    'SCENE_IKNINSIDE',
    'SCENE_MAP_SHOP',
    'SCENE_F40',
    'SCENE_F41',
    'SCENE_10YUKIYAMANOMURA2',
    'SCENE_14YUKIDAMANOMITI',
    'SCENE_12HAKUGINMAE',
    'SCENE_17SETUGEN',
    'SCENE_17SETUGEN2',
    'SCENE_SEA_BS',
    'SCENE_RANDOM',
    'SCENE_YADOYA',
    'SCENE_KONPEKI_ENT',
    'SCENE_INSIDETOWER',
    'SCENE_26SARUNOMORI',
    'SCENE_LOST_WOODS',
    'SCENE_LAST_LINK',
    'SCENE_SOUGEN',
    'SCENE_BOMYA',
    'SCENE_KYOJINNOMA',
    'SCENE_KOEPONARACE',
    'SCENE_GORONRACE',
    'SCENE_TOWN',
    'SCENE_ICHIBA',
    'SCENE_BACKTOWN',
    'SCENE_CLOCKTOWER',
    'SCENE_ALLEY'
]

def read_bytes(data_file, offset, len):
    data_file.seek(offset)
    return bytearray(data_file.read(len))

def calc_length(data_file, offset):
    off = 0
    cmd = None
    branch_targets = []

    # Parse script, just keeping track of branches, until we find the end
    while any([branch >= off for branch in branch_targets]) or cmd not in [0x04, 0x05, 0x06, 0x09]:
        cmd = read_bytes(data_file, offset + off, 1)[0]

        cmd_len = cmd_info[cmd][1]
        cmd_args = cmd_info[cmd][2]

        if len(cmd_args) > 1:
            arg_values = struct.unpack(cmd_args, read_bytes(data_file, offset + off + 1, cmd_len - 1))
            for i in cmd_info[cmd][3]:
                branch_targets.append(off + arg_values[i] + cmd_len)

        off += cmd_len

    return off

def disassemble_unk_script(data_file, offset):
    off = 0
    cmd = None
    branch_targets = []
    script_len = calc_length(data_file, offset);
    script_len_num_digits = 0 if script_len == 1 else int(math.ceil(math.log(script_len - 1, 16)))

    out = "static u8 sScheduleScript[] = {\n"

    # Keep trying to disassemble until it hits a terminator and no commands branch past it
    while any([branch >= off for branch in branch_targets]) or cmd not in [0x04, 0x05, 0x06, 0x09]:
        cmd = read_bytes(data_file, offset + off, 1)[0]

        cmd_name = cmd_info[cmd][0]
        cmd_len = cmd_info[cmd][1]
        cmd_args = cmd_info[cmd][2]

        args_formatted = []
        if len(cmd_args) > 1: # handle args
            arg_values = struct.unpack(cmd_args, read_bytes(data_file, offset + off + 1, cmd_len - 1))
            for i,(arg_value,arg_type) in enumerate(zip(arg_values, cmd_args[1:]),0):
                arg_formatted = ""
                if arg_type == "h":
                    arg_formatted = f"{arg_value:#x}"
                elif arg_type == "b":
                    arg_formatted = f"{arg_value:#x}"
                elif arg_type == "H":
                    if (cmd == 0x0A or cmd == 0x0B) and (arg_value < len(scene_names)):
                        arg_formatted = scene_names[arg_value]
                    elif cmd == 0x00 or cmd == 0x01:
                        arg_formatted = f"WEEKEVENTREG_{arg_value>>8:02}_{arg_value&0xFF:02X}"
                    else:
                        arg_formatted = f"{arg_value}"
                elif arg_type == "B":
                    if cmd == 0x00 or cmd == 0x01:
                        arg_formatted = f"0x{arg_value:02X}"
                    elif cmd == 0x08:
                        if arg_value == 0:
                            arg_formatted = "SCHEDULE_CHECK_MISC_ROOM_KEY"
                        elif arg_value == 1:
                            arg_formatted = "SCHEDULE_CHECK_MISC_LETTER_TO_KAFEI"
                        elif arg_value == 2:
                            arg_formatted = "SCHEDULE_CHECK_MISC_MASK_ROMANI"
                        else:
                            arg_formatted = f"0x{arg_value:02X}"
                    else:
                        arg_formatted = f"{arg_value:2}"
                elif arg_type == "S":
                    if arg_value < len(scene_names):
                        arg_formatted = scene_names[arg_value]
                    else:
                        arg_formatted = f"0x{arg_value:04X}"

                if i in cmd_info[cmd][3]: # skip argument indices
                    # add skip args to branch targets, and change the output to absolute differences rather than relative offsets
                    arg_value += cmd_len
                    branch_targets.append(off + arg_value)
                    if arg_value == cmd_len:
                        arg_formatted == "0"
                    else:
                        arg_formatted = f"0x{off + arg_value:0{script_len_num_digits}X} - 0x{off + cmd_len:0{script_len_num_digits}X}"
                args_formatted.append(arg_formatted)

        args = ", ".join(args_formatted) if len(args_formatted) != 0 else ""

        out += f"    /* 0x{off:0{script_len_num_digits}X} */ {cmd_name}({args}),\n"

        off += cmd_len

    out = out.strip()
    out += "\n};"

    print(out)

def hex_parse(s):
    return int(s, 16)

def main():
    parser = argparse.ArgumentParser(description="Disassembles MM event scripts")
    parser.add_argument('address', help="VRAM or ROM address to disassemble at", type=hex_parse)
    args = parser.parse_args()

    file_result = resolve_symbol(args.address)

    if file_result[0] is None:
        print("Invalid address")
        return

    print(hex(file_result[1]), "in", file_result[0].split(os.sep)[-1])

    with open(file_result[0],"rb") as data_file:
        disassemble_unk_script(data_file, file_result[1])

if __name__ == "__main__":
    main()
