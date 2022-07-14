#!/usr/bin/env python3
#
#   Message Event Script Disassembler
#

import argparse, os, struct
from actor_symbols import resolve_symbol

cmd_info = [
    ('MSCRIPT_BRANCH_ON_WEEK_EVENT_REG', 0x05, '', '>BBh', (2,)),
    ('MSCRIPT_BRANCH_IF_GORON', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_IF_ZORA', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_IF_DEKU', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_IF_HUMAN', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_ON_TEXT_CHOICE', 0x07, '', '>hhh', (0,1,2)),
    ('MSCRIPT_OFFER_ITEM', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_CMD07', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_ON_RUPEES', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_BRANCH_ON_CALLBACK_OPTIONAL', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_ON_DAY', 0x0d, '', '>hhhhhh', (0,1,2,3,4,5)),
    ('MSCRIPT_CMD11', 0x03, '', '>h', (0,)),
    ('MSCRIPT_AWAIT_TEXT', 0x01, '', '', ()),
    ('MSCRIPT_CMD13', 0x01, '', '', ()),
    ('MSCRIPT_BEGIN_TEXT', 0x03, '', '>H', ()),
    ('MSCRIPT_CONTINUE_TEXT', 0x03, '', '>H', ()),
    ('MSCRIPT_DONE',  0x01, '', '', ()),
    ('MSCRIPT_WEEK_EVENT_REG_SET', 0x03, '', '>BB', ()),
    ('MSCRIPT_CLOSE_TEXT', 0x01, '', '', ()),
    ('MSCRIPT_COLLECT_SET', 0x03, '', '>H', ()),
    ('MSCRIPT_CHANGE_RUPEES', 0x03, '', '>H', ()),
    ('MSCRIPT_PAUSE', 0x01, '', '', ()),
    ('MSCRIPT_CMD22', 0x01, '', '', ()),
    ('MSCRIPT_FOCUS_TO_CHILD', 0x01, '', '', ()),
    ('MSCRIPT_FOCUS_TO_SELF', 0x01, '', '', ()),
    ('MSCRIPT_JUMP', 0x03, '', '>h', (0,)),
    ('MSCRIPT_BRANCH_ON_QUEST_ITEM', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_BRANCH_ON_EVENT_INF', 0x05, '', '>BBh', (2,)),
    ('MSCRIPT_SET_EVENT_INF', 0x03, '', '>BB', ()),
    ('MSCRIPT_UNSET_EVENT_INF', 0x03, '', '>BB', ()),
    ('MSCRIPT_BRANCH_ON_ITEMACTION', 0x09, '', '>Hhhh', (1,2,3)),
    ('MSCRIPT_BRANCH_ON_SONG_OBTAINED', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_BRANCH_ON_WORN_MASK', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_BRANCH_ON_TIME_GT', 0x05, '', '>BBh', (2,)),
    ('MSCRIPT_BRANCH_ON_TIME_LEQ', 0x05, '', '>BBh', (2,)),
    ('MSCRIPT_BRANCH_ON_SWITCH_FLAG', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_SET_SWITCH_FLAG', 0x03, '', '>H', ()),
    ('MSCRIPT_BRANCH_ON_ITEM', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_BRANCH_ON_TIME_INTERVAL', 0x07, '', '>BBBBh', (4,)),
    ('MSCRIPT_BRANCH_IF_DAY', 0x05, '', '>Hh', (1,)),
    ('MSCRIPT_BRANCH_ON_CALLBACK_2', 0x03, '', '>h', (0,)),
    ('MSCRIPT_HAS_POWDER_KEG', 0x03, '', '>h', (0,)),
    ('MSCRIPT_DEL_ITEM', 0x03, '', '>h', ()),
    ('MSCRIPT_BRANCH_ON_CALLBACK', 0x07, '', '>hhh', (0,1,2)),
    ('MSCRIPT_CMD44', 0x03, '', '>H', ()),
    ('MSCRIPT_NOTEBOOK_EVENT', 0x03, '', '>H', ()),
    ('MSCRIPT_CMD46', 0x01, '', '', ()),
    ('MSCRIPT_JUMP_3', 0x03, '', '>h', (0,)),
    ('MSCRIPT_PLAY_DECIDE', 0x01, '', '', ()),
    ('MSCRIPT_PLAY_CANCEL', 0x01, '', '', ()),
    ('MSCRIPT_PLAY_ERROR', 0x01, '', '', ()),
]

item_names = (
    "ITEM_OCARINA",
    "ITEM_BOW",
    "ITEM_ARROW_FIRE",
    "ITEM_ARROW_ICE",
    "ITEM_ARROW_LIGHT",
    "ITEM_OCARINA_FAIRY",
    "ITEM_BOMB",
    "ITEM_BOMBCHU",
    "ITEM_STICK",
    "ITEM_NUT",
    "ITEM_MAGIC_BEANS",
    "ITEM_SLINGSHOT",
    "ITEM_POWDER_KEG",
    "ITEM_PICTOGRAPH_BOX",
    "ITEM_LENS",
    "ITEM_HOOKSHOT",
    "ITEM_SWORD_GREAT_FAIRY",
    "ITEM_LONGSHOT",
    "ITEM_BOTTLE",
    "ITEM_POTION_RED",
    "ITEM_POTION_GREEN",
    "ITEM_POTION_BLUE",
    "ITEM_FAIRY",
    "ITEM_DEKU_PRINCESS",
    "ITEM_MILK_BOTTLE",
    "ITEM_MILK_HALF",
    "ITEM_FISH",
    "ITEM_BUG",
    "ITEM_BLUE_FIRE",
    "ITEM_POE",
    "ITEM_BIG_POE",
    "ITEM_SPRING_WATER",
    "ITEM_HOT_SPRING_WATER",
    "ITEM_ZORA_EGG",
    "ITEM_GOLD_DUST",
    "ITEM_MUSHROOM",
    "ITEM_SEA_HORSE",
    "ITEM_CHATEAU",
    "ITEM_HYLIAN_LOACH",
    "ITEM_OBABA_DRINK",
    "ITEM_MOON_TEAR",
    "ITEM_DEED_LAND",
    "ITEM_DEED_SWAMP",
    "ITEM_DEED_MOUNTAIN",
    "ITEM_DEED_OCEAN",
    "ITEM_ROOM_KEY",
    "ITEM_LETTER_MAMA",
    "ITEM_LETTER_TO_KAFEI",
    "ITEM_PENDANT_OF_MEMORIES",
    "ITEM_TINGLE_MAP",
    "ITEM_MASK_DEKU",
    "ITEM_MASK_GORON",
    "ITEM_MASK_ZORA",
    "ITEM_MASK_FIERCE_DEITY",
    "ITEM_MASK_TRUTH",
    "ITEM_MASK_KAFEIS_MASK",
    "ITEM_MASK_ALL_NIGHT",
    "ITEM_MASK_BUNNY",
    "ITEM_MASK_KEATON",
    "ITEM_MASK_GARO",
    "ITEM_MASK_ROMANI",
    "ITEM_MASK_CIRCUS_LEADER",
    "ITEM_MASK_POSTMAN",
    "ITEM_MASK_COUPLE",
    "ITEM_MASK_GREAT_FAIRY",
    "ITEM_MASK_GIBDO",
    "ITEM_MASK_DON_GERO",
    "ITEM_MASK_KAMARO",
    "ITEM_MASK_CAPTAIN",
    "ITEM_MASK_STONE",
    "ITEM_MASK_BREMEN",
    "ITEM_MASK_BLAST",
    "ITEM_MASK_SCENTS",
    "ITEM_MASK_GIANT",
    "ITEM_BOW_ARROW_FIRE",
    "ITEM_BOW_ARROW_ICE",
    "ITEM_BOW_ARROW_LIGHT",
    "ITEM_SWORD_KOKIRI",
    "ITEM_SWORD_RAZOR",
    "ITEM_SWORD_GILDED",
    "ITEM_SWORD_DEITY",
    "ITEM_SHIELD_HERO",
    "ITEM_SHIELD_MIRROR",
    "ITEM_QUIVER_30",
    "ITEM_QUIVER_40",
    "ITEM_QUIVER_50",
    "ITEM_BOMB_BAG_20",
    "ITEM_BOMB_BAG_30",
    "ITEM_BOMB_BAG_40",
    "ITEM_WALLET_DEFAULT",
    "ITEM_WALLET_ADULT",
    "ITEM_WALLET_GIANT",
    "ITEM_FISHING_POLE",
    "ITEM_REMAINS_ODOLWA",
    "ITEM_REMAINS_GOHT",
    "ITEM_REMAINS_GYORG",
    "ITEM_REMAINS_TWINMOLD",
    "ITEM_SONG_SONATA",
    "ITEM_SONG_LULLABY",
    "ITEM_SONG_NOVA",
    "ITEM_SONG_ELEGY",
    "ITEM_SONG_OATH",
    "ITEM_SONG_SARIA",
    "ITEM_SONG_TIME",
    "ITEM_SONG_HEALING",
    "ITEM_SONG_EPONA",
    "ITEM_SONG_SOARING",
    "ITEM_SONG_STORMS",
    "ITEM_SONG_SUN",
    "ITEM_BOMBERS_NOTEBOOK",
    "ITEM_SKULL_TOKEN",
    "ITEM_HEART_CONTAINER",
    "ITEM_HEART_PIECE",
    None,
    None,
    "ITEM_SONG_LULLABY_INTRO",
    "ITEM_KEY_BOSS",
    "ITEM_COMPASS",
    "ITEM_DUNGEON_MAP",
    "ITEM_STRAY_FAIRIES",
    "ITEM_KEY_SMALL",
    "ITEM_MAGIC_SMALL",
    "ITEM_MAGIC_LARGE",
    "ITEM_HEART_PIECE_2",
    "ITEM_INVALID_1",
    "ITEM_INVALID_2",
    "ITEM_INVALID_3",
    "ITEM_INVALID_4",
    "ITEM_INVALID_5",
    "ITEM_INVALID_6",
    "ITEM_INVALID_7",
    "ITEM_HEART",
    "ITEM_RUPEE_GREEN",
    "ITEM_RUPEE_BLUE",
    "ITEM_RUPEE_10",
    "ITEM_RUPEE_RED",
    "ITEM_RUPEE_PURPLE",
    "ITEM_RUPEE_SILVER",
    "ITEM_RUPEE_HUGE",
    "ITEM_STICKS_5",
    "ITEM_STICKS_10",
    "ITEM_NUTS_5",
    "ITEM_NUTS_10",
    "ITEM_BOMBS_5",
    "ITEM_BOMBS_10",
    "ITEM_BOMBS_20",
    "ITEM_BOMBS_30",
    "ITEM_ARROWS_10",
    "ITEM_ARROWS_30",
    "ITEM_ARROWS_40",
    "ITEM_ARROWS_50",
    "ITEM_BOMBCHUS_20",
    "ITEM_BOMBCHUS_10",
    "ITEM_BOMBCHUS_1",
    "ITEM_BOMBCHUS_5",
    "ITEM_STICK_UPGRADE_20",
    "ITEM_STICK_UPGRADE_30",
    "ITEM_NUT_UPGRADE_30",
    "ITEM_NUT_UPGRADE_40",
    "ITEM_CHATEAU_2",
    "ITEM_MILK",
    "ITEM_GOLD_DUST_2",
    "ITEM_HYLIAN_LOACH_2",
    "ITEM_SEA_HORSE_CAUGHT",
)

gi_names = (
    "GI_NONE",
    "GI_RUPEE_GREEN",
    "GI_RUPEE_BLUE",
    "GI_RUPEE_10",
    "GI_RUPEE_RED",
    "GI_RUPEE_PURPLE",
    "GI_RUPEE_SILVER",
    "GI_RUPEE_HUGE",
    "GI_WALLET_ADULT",
    "GI_WALLET_GIANT",
    "GI_RECOVERY_HEART",
    None,
    "GI_HEART_PIECE",
    "GI_HEART_CONTAINER",
    "GI_MAGIC_SMALL",
    "GI_MAGIC_LARGE",
    None,
    "GI_STRAY_FAIRY",
    None,
    None,
    "GI_BOMBS_1",
    "GI_BOMBS_5",
    "GI_BOMBS_10",
    "GI_BOMBS_20",
    "GI_BOMBS_30",
    "GI_STICKS_1",
    "GI_BOMBCHUS_10",
    "GI_BOMB_BAG_20",
    "GI_BOMB_BAG_30",
    "GI_BOMB_BAG_40",
    "GI_ARROWS_10",
    "GI_ARROWS_30",
    "GI_ARROWS_40",
    "GI_ARROWS_50",
    "GI_QUIVER_30",
    "GI_QUIVER_40",
    "GI_QUIVER_50",
    "GI_ARROW_FIRE",
    "GI_ARROW_ICE",
    "GI_ARROW_LIGHT",
    "GI_NUTS_1",
    "GI_NUTS_5",
    "GI_NUTS_10",
    None,
    None,
    None,
    "GI_BOMBCHUS_20",
    None,
    None,
    None,
    "GI_SHIELD_HERO",
    "GI_SHIELD_MIRROR",
    "GI_POWDER_KEG",
    "GI_MAGIC_BEANS",
    "GI_BOMBCHUS_1",
    "GI_SWORD_KOKIRI",
    "GI_SWORD_RAZOR",
    "GI_SWORD_GILDED",
    "GI_BOMBCHUS_5",
    "GI_SWORD_GREAT_FAIRY",
    "GI_KEY_SMALL",
    "GI_KEY_BOSS",
    "GI_MAP",
    "GI_COMPASS",
    "GI_40",
    "GI_HOOKSHOT",
    "GI_LENS",
    "GI_PICTOGRAPH_BOX",
    None,
    None,
    None,
    None,
    None,
    None,
    None,
    None,
    "GI_OCARINA",
    None,
    None,
    None,
    "GI_BOMBERS_NOTEBOOK",
    None,
    "GI_SKULL_TOKEN",
    None,
    None,
    "GI_REMAINS_ODOLWA",
    "GI_REMAINS_GOHT",
    "GI_REMAINS_GYORG",
    "GI_REMAINS_TWINMOLD",
    "GI_POTION_RED_BOTTLE",
    "GI_BOTTLE",
    "GI_POTION_RED",
    "GI_POTION_GREEN",
    "GI_POTION_BLUE",
    "GI_FAIRY",
    "GI_DEKU_PRINCESS",
    "GI_MILK_BOTTLE",
    "GI_MILK_HALF",
    "GI_FISH",
    "GI_BUG",
    "GI_BLUE_FIRE",
    "GI_POE",
    "GI_BIG_POE",
    "GI_SPRING_WATER",
    "GI_HOT_SPRING_WATER",
    "GI_ZORA_EGG",
    "GI_GOLD_DUST",
    "GI_MUSHROOM",
    "GI_6C",
    "GI_6D",
    "GI_SEAHORSE",
    "GI_CHATEAU_BOTTLE",
    "GI_HYLIAN_LOACH",
    None,
    None,
    None,
    None,
    "GI_75",
    "GI_ICE_TRAP",
    None,
    "GI_MASK_DEKU",
    "GI_MASK_GORON",
    "GI_MASK_ZORA",
    "GI_MASK_FIERCE_DEITY",
    "GI_MASK_CAPTAIN",
    "GI_MASK_GIANT",
    "GI_MASK_ALL_NIGHT",
    "GI_MASK_BUNNY",
    "GI_MASK_KEATON",
    "GI_MASK_GARO",
    "GI_MASK_ROMANI",
    "GI_MASK_CIRCUS_LEADER",
    "GI_MASK_POSTMAN",
    "GI_MASK_COUPLE",
    "GI_MASK_GREAT_FAIRY",
    "GI_MASK_GIBDO",
    "GI_MASK_DON_GERO",
    "GI_MASK_KAMARO",
    "GI_MASK_TRUTH",
    "GI_MASK_STONE",
    "GI_MASK_BREMEN",
    "GI_MASK_BLAST",
    "GI_MASK_SCENTS",
    "GI_MASK_KAFEIS_MASK",
    "GI_CHATEAU",
    "GI_MILK",
    "GI_GOLD_DUST_2",
    "GI_HYLIAN_LOACH_2",
    "GI_SEAHORSE_CAUGHT",
    "GI_MOON_TEAR",
    "GI_DEED_LAND",
    "GI_DEED_SWAMP",
    "GI_DEED_MOUNTAIN",
    "GI_DEED_OCEAN",
    "GI_SWORD_GREAT_FAIRY_STOLEN",
    "GI_SWORD_KOKIRI_STOLEN",
    "GI_SWORD_RAZOR_STOLEN",
    "GI_SWORD_GILDED_STOLEN",
    "GI_SHIELD_HERO_STOLEN",
    "GI_ROOM_KEY",
    "GI_LETTER_TO_MAMA",
    "GI_A2",
    "GI_A3",
    "GI_A4",
    "GI_A5",
    "GI_A6",
    "GI_A7",
    "GI_A8",
    "GI_BOTTLE_STOLEN",
    "GI_LETTER_TO_KAFEI",
    "GI_PENDANT_OF_MEMORIES",
    "GI_TINGLE_MAP_CLOCK_TOWN",
    "GI_TINGLE_MAP_WOODFALL",
    "GI_TINGLE_MAP_SNOWHEAD",
    "GI_TINGLE_MAP_ROMANI_RANCH",
    "GI_TINGLE_MAP_GREAT_BAY",
    "GI_TINGLE_MAP_STONE_TOWER",
    "GI_MAX",
)

notebook_event = (
    "BOMBERS_NOTEBOOK_EVENT_MET_BOMBERS",
    "BOMBERS_NOTEBOOK_EVENT_MET_ANJU",
    "BOMBERS_NOTEBOOK_EVENT_MET_KAFEI",
    "BOMBERS_NOTEBOOK_EVENT_MET_CURIOSITY_SHOP_MAN",
    "BOMBERS_NOTEBOOK_EVENT_MET_BOMB_SHOP_LADY",
    "BOMBERS_NOTEBOOK_EVENT_MET_ROMANI",
    "BOMBERS_NOTEBOOK_EVENT_MET_CREMIA",
    "BOMBERS_NOTEBOOK_EVENT_MET_MAYOR_DOTOUR",
    "BOMBERS_NOTEBOOK_EVENT_MET_MADAME_AROMA",
    "BOMBERS_NOTEBOOK_EVENT_MET_TOTO",
    "BOMBERS_NOTEBOOK_EVENT_MET_GORMAN",
    "BOMBERS_NOTEBOOK_EVENT_MET_POSTMAN",
    "BOMBERS_NOTEBOOK_EVENT_MET_ROSA_SISTERS",
    "BOMBERS_NOTEBOOK_EVENT_MET_TOLIET_HAND",
    "BOMBERS_NOTEBOOK_EVENT_MET_ANJUS_GRANDMOTHER",
    "BOMBERS_NOTEBOOK_EVENT_MET_KAMARO",
    "BOMBERS_NOTEBOOK_EVENT_MET_GROG",
    "BOMBERS_NOTEBOOK_EVENT_MET_GORMAN_BROTHERS",
    "BOMBERS_NOTEBOOK_EVENT_MET_SHIRO",
    "BOMBERS_NOTEBOOK_EVENT_MET_GURU_GURU",

    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROOM_KEY",
    "BOMBERS_NOTEBOOK_EVENT_PROMISED_MIDNIGHT_MEETING",
    "BOMBERS_NOTEBOOK_EVENT_PROMISED_TO_MEET_KAFEI",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_LETTER_TO_KAFEI",
    "BOMBERS_NOTEBOOK_EVENT_DEPOSITED_LETTER_TO_KAFEI",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_PENDANT_OF_MEMORIES",
    "BOMBERS_NOTEBOOK_EVENT_DELIVERED_PENDANT_OF_MEMORIES",
    "BOMBERS_NOTEBOOK_EVENT_ESCAPED_SAKONS_HIDEOUT",
    "BOMBERS_NOTEBOOK_EVENT_PROMISED_TO_HELP_WITH_THEM",
    "BOMBERS_NOTEBOOK_EVENT_DEFENDED_AGAINST_THEM",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_MILK_BOTTLE",
    "BOMBERS_NOTEBOOK_EVENT_ESCORTED_CREMIA",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROMANIS_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_KEATON_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_PRIORITY_MAIL",
    "BOMBERS_NOTEBOOK_EVENT_DELIVERED_PRIORITY_MAIL",
    "BOMBERS_NOTEBOOK_EVENT_LEARNED_SECRET_CODE",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_BOMBERS_NOTEBOOK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_MAYOR_HP",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROSA_SISTERS_HP",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_TOILET_HAND_HP",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_GRANDMA_SHORT_STORY_HP",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_GRANDMA_LONG_STORY_HP",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_POSTMAN_HP",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_KAFEIS_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_ALL_NIGHT_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_BUNNY_HOOD",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_GAROS_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_CIRCUS_LEADERS_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_POSTMANS_HAT",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_COUPLES_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_BLAST_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_KAMAROS_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_STONE_MASK",
    "BOMBERS_NOTEBOOK_EVENT_RECEIVED_BREMEN_MASK",
)

def read_bytes(data_file, offset, len):
    with open(data_file,"rb") as infile:
        infile.seek(offset)
        return bytearray(infile.read(len))

def disassemble_msg_script(data_file, script_start, offset, length):
    out = ""
    cmd = None
    branch_targets = []

    # Keep trying to disassemble until it hits the terminator and no commands branch past it
    while any([branch >= offset for branch in branch_targets]) or cmd != 0x10:
        # print(offset)
        cmd = read_bytes(data_file, script_start + offset, 1)[0]
        # print(cmd)

        cmd_name = cmd_info[cmd][0]
        cmd_len = cmd_info[cmd][1]
        cmd_args = cmd_info[cmd][3]

        is_branch = False

        args_formatted = []
        if len(cmd_args) > 1: # handle args
            raw_args = read_bytes(data_file, script_start + offset + 1, cmd_len - 1)
            arg_values = struct.unpack(cmd_args, raw_args)

            # print(len(raw_args) + 1, f"0x{cmd:02X}", [f"0x{b:02X}" for b in raw_args])

            for i,(arg_value,arg_type) in enumerate(zip(arg_values, cmd_args[1:]),0):
                arg_formatted = ""

                if cmd == 6 and i == 0:
                    arg_formatted = gi_names[arg_value]
                    assert arg_formatted is not None
                elif cmd == 37 and i == 0:
                    arg_formatted = item_names[arg_value]
                    assert arg_formatted is not None
                elif cmd == 42 and i == 0:
                    arg_formatted = item_names[arg_value]
                    assert arg_formatted is not None
                elif cmd == 45 and i == 0:
                    arg_formatted = notebook_event[arg_value]
                    assert arg_formatted is not None
                else:
                    if arg_type == "h":
                        arg_formatted = f"{arg_value:#x}"
                    elif arg_type == "H":
                        arg_formatted = f"0x{arg_value:04X}"
                    elif arg_type == "B":
                        arg_formatted = f"0x{arg_value:02X}"

                    if i in cmd_info[cmd][4]: # skip argument indices
                        # add skip args to branch targets, and change the output to absolute differences rather than relative offsets
                        arg_value += cmd_len

                        is_branch = True
                        branch_pos = offset + cmd_len
                        branch_target = offset + arg_value

                        branch_targets.append(branch_target)

                        if arg_value == cmd_len:
                            arg_formatted == "0"
                        else:
                            arg_formatted = f"0x{branch_target:04X} - 0x{branch_pos:04X}"
                args_formatted.append(arg_formatted)
        # else:
        #     print(1, f"0x{cmd:02X}")

        args = ", ".join(args_formatted) if len(args_formatted) != 0 else ""

        line = f"    /* 0x{offset:04X} 0x{cmd_len:02X} */ {cmd_name}({args}),{f' // {cmd_info[cmd][2]}' if cmd_info[cmd][2] != '' else ''}\n"
        out += line

        if cmd == 0x10 or is_branch and branch_target < branch_pos: # maybe
            out += "\n"

        offset += cmd_len

        if is_branch and branch_target < branch_pos:
            # branch backwards, terminate if nothing branches past here
            # TODO if the branch is conditional we should not be terminating here
            if not any([branch >= offset for branch in branch_targets]):
                break

    length -= offset

    if length > 0:
        if length < 4 and all([b == 0 for b in read_bytes(data_file, script_start + offset, length)]):
            # padding
            pass
        else:
            # some data left over, try and disassemble it
            out += "                   // Unreachable\n"
            out += disassemble_msg_script(data_file, script_start, offset, length)

    return out

def main():
    parser = argparse.ArgumentParser(description="Disassembles MM behavior scripts")
    parser.add_argument('address', help="VRAM or ROM address to disassemble at", type=lambda s : int(s.replace("D_", "0x"), 16))
    parser.add_argument('length', help="Number of bytes to disassemble, by default it will disassemble all reachable commands", nargs='?', default=-1, type=int)
    parser.add_argument('--name', help="Array name", default="sMsgScript", type=str)
    args = parser.parse_args()

    file_result = resolve_symbol(args.address)

    if file_result[0] is None:
        print("Invalid address")
        return

    print(hex(file_result[1]), "in", file_result[0].split(os.sep)[-1])

    print(f"MsgScript {args.name}[] = {{")
    print(disassemble_msg_script(file_result[0], file_result[1], 0, args.length).rstrip())
    print("};")

if __name__ == "__main__":
    main()
