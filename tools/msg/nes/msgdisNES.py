#!/usr/bin/env python3

import argparse
import sys
import struct

class MessageHeaderNES:
    def __init__(self, unk11F08, itemId, nextTextId, unk1206C, unk12070, unk12074):
        self.unk11F08 = unk11F08
        self.itemId = itemId
        self.nextTextId = nextTextId
        self.unk1206C = unk1206C
        self.unk12070 = unk12070
        self.unk12074 = unk12074

    def __str__(self):
        return (
            f'unk11F08: 0x{self.unk11F08:04X},\n'
            f'itemId: 0x{self.itemId:02X},\n'
            f'nextTextId: 0x{self.nextTextId:04X},\n'
            f'unk1206C: 0x{self.unk1206C:04X},\n'
            f'unk12070: 0x{self.unk12070:04X},\n'
            f'unk12074: 0x{self.unk12074:04X}'
        )

    def macro(self):
        unk11F08 = struct.pack(">H", self.unk11F08)
        itemId = struct.pack(">B", self.itemId)
        nextTextId = struct.pack(">H", self.nextTextId)
        unk1206C = struct.pack(">H", self.unk1206C)
        unk12070 = struct.pack(">H", self.unk12070)
        unk12074 = struct.pack(">H", self.unk12074)
        return (
            f'"\\x{unk11F08[0]:02X}\\x{unk11F08[1]:02X}" '
            f'"\\x{itemId[0]:02X}" '
            f'"\\x{nextTextId[0]:02X}\\x{nextTextId[1]:02X}" '
            f'"\\x{unk1206C[0]:02X}\\x{unk1206C[1]:02X}" '
            f'"\\x{unk12070[0]:02X}\\x{unk12070[1]:02X}" '
            f'"\\x{unk12074[0]:02X}\\x{unk12074[1]:02X}"'
        )


class MessageNES:
    BUTTONMAP = {
        0xB0: '[A]',
        0xB1: '[B]',
        0xB2: '[C]',
        0xB3: '[L]',
        0xB4: '[R]',
        0xB5: '[Z]',
        0xB6: '[C-Up]',
        0xB7: '[C-Down]',
        0xB8: '[C-Left]',
        0xB9: '[C-Right]',
        0xBA: '▼',
        0xBB: '[Control-Pad]'
    }

    def __init__(self, id, typePos, addr, hdr, text):
        self.id = id
        self.typePos = typePos
        self.addr = addr
        self.hdr = hdr
        self.text = text
        self.decodedText = ""
        self.decodePos = 0

    def __str__(self):
        return (
            f'Message 0x{self.id:04X}:\n'
            f'Segment: 0x{self.addr:08X}\n'
            f'TypePos: 0x{self.typePos:02X}\n'
            f'{str(self.hdr)}\n'
            f'Text: {self.text}\n'
            f'Decoded:\n{self.decodedText}'
        )

    def macro(self):
        self.decode()
        return ( 
                f"DEFINE_MESSAGE(0x{self.id:04X}, 0x{self.typePos:02X}, {self.hdr.macro()}\n"
                f"{self.decodedText}\n)\n"
        )

    def decode_cmd_arg_none(self, cmd):
        return f'{cmd}'

    def decode_cmd_arg_1byte(self, cmd):
        arg = self.text[self.decodePos]
        self.decodePos += 1
        return f'{cmd}("\\x{arg:02X}")'

    def decode_cmd_arg_2byte(self, cmd):
        arg1 = self.text[self.decodePos]
        arg2 = self.text[self.decodePos + 1]
        self.decodePos += 2
        return f'{cmd}("\\x{arg1:02X}\\x{arg2:02X}")'

    def decode(self):
        CMDMAP = {
            0x00: ("CMD_COLOR_DEFAULT", self.decode_cmd_arg_none),
            0x01: ("CMD_COLOR_RED", self.decode_cmd_arg_none),
            0x02: ("CMD_COLOR_GREEN", self.decode_cmd_arg_none),
            0x03: ("CMD_COLOR_BLUE", self.decode_cmd_arg_none),
            0x04: ("CMD_COLOR_YELLOW", self.decode_cmd_arg_none),
            0x05: ("CMD_COLOR_LIGHTBLUE", self.decode_cmd_arg_none),
            0X06: ("CMD_COLOR_PINK", self.decode_cmd_arg_none),
            0x07: ("CMD_COLOR_SILVER", self.decode_cmd_arg_none),
            0x08: ("CMD_COLOR_ORANGE", self.decode_cmd_arg_none),
            0x0A: ("CMD_TEXT_SPEED", self.decode_cmd_arg_none),
            0x0B: ("CMD_HS_BOAT_ARCHERY", self.decode_cmd_arg_none),
            0x0C: ("CMD_STRAY_FAIRIES", self.decode_cmd_arg_none),
            0x0D: ("CMD_TOKENS", self.decode_cmd_arg_none),
            0x0E: ("CMD_POINTS_TENS", self.decode_cmd_arg_none),
            0x0F: ("CMD_POINTS_THOUSANDS", self.decode_cmd_arg_none),
            0x10: ("CMD_BOX_BREAK", self.decode_cmd_arg_none),
            0x12: ("CMD_BOX_BREAK2", self.decode_cmd_arg_none),
            0x13: ("CMD_CARRIAGE_RETURN", self.decode_cmd_arg_none),
            0x14: ("CMD_SHIFT", self.decode_cmd_arg_1byte),
            0x15: ("CMD_CONTINUE", self.decode_cmd_arg_none),
            0x16: ("CMD_NAME", self.decode_cmd_arg_none),
            0x17: ("CMD_QUICKTEXT_ENABLE", self.decode_cmd_arg_none),
            0x18: ("CMD_QUICKTEXT_DISABLE", self.decode_cmd_arg_none),
            0x19: ("CMD_EVENT", self.decode_cmd_arg_none),
            0x1A: ("CMD_PERSISTENT", self.decode_cmd_arg_none),
            0x1B: ("CMD_BOX_BREAK_DELAYED", self.decode_cmd_arg_2byte),
            0x1C: ("CMD_FADE", self.decode_cmd_arg_2byte),
            0x1D: ("CMD_FADE_SKIPPABLE", self.decode_cmd_arg_2byte),
            0x1E: ("CMD_SFX", self.decode_cmd_arg_2byte),
            0x1F: ("CMD_DELAY", self.decode_cmd_arg_2byte),
            0xC1: ("CMD_BACKGROUND", self.decode_cmd_arg_none),
            0xC2: ("CMD_TWO_CHOICE", self.decode_cmd_arg_none),
            0xC3: ("CMD_THREE_CHOICE", self.decode_cmd_arg_none),
            0xC4: ("CMD_TIMER_POSTMAN", self.decode_cmd_arg_none),
            0xC5: ("CMD_TIMER_MINIGAME_1", self.decode_cmd_arg_none),
            0xC6: ("CMD_TIMER_2", self.decode_cmd_arg_none),
            0xC7: ("CMD_TIMER_MOON_CRASH", self.decode_cmd_arg_none),
            0xC8: ("CMD_TIMER_MINIGAME_2", self.decode_cmd_arg_none),
            0xC9: ("CMD_TIMER_TIMER_ENV_HAZARD", self.decode_cmd_arg_none),
            0xCA: ("CMD_TIME", self.decode_cmd_arg_none),
            0xCB: ("CMD_CHEST_FLAGS", self.decode_cmd_arg_none),
            0xCC: ("CMD_INPUT_BANK", self.decode_cmd_arg_none),
            0xCD: ("CMD_RUPEES_SELECTED", self.decode_cmd_arg_none),
            0xCE: ("CMD_RUPEES_TOTAL", self.decode_cmd_arg_none),
            0xCF: ("CMD_TIME_UNTIL_MOON_CRASH", self.decode_cmd_arg_none),
            0xD0: ("CMD_INPUT_DOGGY_RACETRACK_BET", self.decode_cmd_arg_none),
            0xD1: ("CMD_INPUT_BOMBER_CODE", self.decode_cmd_arg_none),
            0xD2: ("CMD_PAUSE_MENU", self.decode_cmd_arg_none),
            0xD3: ("CMD_TIME_SPEED", self.decode_cmd_arg_none),
            0xD4: ("CMD_OWL_WARP", self.decode_cmd_arg_none),
            0xD5: ("CMD_INPUT_LOTTERY_CODE", self.decode_cmd_arg_none),
            0xD6: ("CMD_SPIDER_HOUSE_MASK_CODE", self.decode_cmd_arg_none),
            0xD7: ("CMD_STRAY_FAIRIES_LEFT_WOODFALL", self.decode_cmd_arg_none),
            0xD8: ("CMD_STRAY_FAIRIES_LEFT_SNOWHEAD", self.decode_cmd_arg_none),
            0xD9: ("CMD_STRAY_FAIRIES_LEFT_GREAT_BAY", self.decode_cmd_arg_none),
            0xDA: ("CMD_STRAY_FAIRIES_LEFT_STONE_TOWER", self.decode_cmd_arg_none),
            0xDB: ("CMD_POINTS_BOAT_ARCHERY", self.decode_cmd_arg_none),
            0xDC: ("CMD_LOTTERY_CODE", self.decode_cmd_arg_none),
            0xDD: ("CMD_LOTTERY_CODE_GUESS", self.decode_cmd_arg_none),
            0xDE: ("CMD_HELD_ITEM_PRICE", self.decode_cmd_arg_none),
            0xDF: ("CMD_BOMBER_CODE", self.decode_cmd_arg_none),
            0xE0: ("CMD_EVENT2", self.decode_cmd_arg_none),
            0xE1: ("CMD_SPIDER_HOUSE_MASK_CODE_1", self.decode_cmd_arg_none),
            0xE2: ("CMD_SPIDER_HOUSE_MASK_CODE_2", self.decode_cmd_arg_none),
            0xE3: ("CMD_SPIDER_HOUSE_MASK_CODE_3", self.decode_cmd_arg_none),
            0xE4: ("CMD_SPIDER_HOUSE_MASK_CODE_4", self.decode_cmd_arg_none),
            0xE5: ("CMD_SPIDER_HOUSE_MASK_CODE_5", self.decode_cmd_arg_none),
            0xE6: ("CMD_SPIDER_HOUSE_MASK_CODE_6", self.decode_cmd_arg_none),
            0xE7: ("CMD_HOURS_UNTIL_MOON_CRASH", self.decode_cmd_arg_none),
            0xE8: ("CMD_TIME_UNTIL_NEW_DAY", self.decode_cmd_arg_none),
            0xF0: ("CMD_HS_POINTS_BANK_RUPEES", self.decode_cmd_arg_none),
            0xF1: ("CMD_HS_POINTS_UNK_1", self.decode_cmd_arg_none),
            0xF2: ("CMD_HS_POINTS_FISHING", self.decode_cmd_arg_none),
            0xF3: ("CMD_HS_TIME_BOAT_ARCHERY", self.decode_cmd_arg_none),
            0xF4: ("CMD_HS_TIME_HORSE_BACK_BALLOON", self.decode_cmd_arg_none),
            0xF5: ("CMD_HS_TIME_LOTTERY_GUESS", self.decode_cmd_arg_none),
            0xF6: ("CMD_HS_TOWN_SHOOTING_GALLERY", self.decode_cmd_arg_none),
            0xF7: ("CMD_HS_UNK_1", self.decode_cmd_arg_none),
            0xF8: ("CMD_HS_UNK_3_LOWER", self.decode_cmd_arg_none),
            0xF9: ("CMD_HS_HORSE_BACK_BALLOON", self.decode_cmd_arg_none),
            0xFA: ("CMD_HS_DEKU_PLAYGROUND_DAY_1", self.decode_cmd_arg_none),
            0xFB: ("CMD_HS_DEKU_PLAYGROUND_DAY_2", self.decode_cmd_arg_none),
            0xFC: ("CMD_HS_DEKU_PLAYGROUND_DAY_3", self.decode_cmd_arg_none),
            0xFD: ("CMD_DEKU_PLAYGROUND_NAME_DAY_1", self.decode_cmd_arg_none),
            0xFE: ("CMD_DEKU_PLAYGROUND_NAME_DAY_2", self.decode_cmd_arg_none),
            0xFF: ("CMD_DEKU_PLAYGROUND_NAME_DAY_3", self.decode_cmd_arg_none)
        }
        if self.decodedText != "":
            return

        prevText = False
        prevNewline = True
        prevCmd = False
        self.decodePos = 0
        textLen = len(self.text)
        while self.decodePos < textLen:
            char = self.text[self.decodePos]
            self.decodePos += 1

            if char >= 0x20 and char <= 0xBB: # Characters
                if prevCmd:
                    self.decodedText += ' "'
                elif prevNewline:
                    self.decodedText += '"'

                if char == 0x22: # Handle escaping "
                    self.decodedText += '\\"'
                elif char >= 0xB0: # Button characters
                    self.decodedText += f'{MessageNES.BUTTONMAP[char]}'
                else:
                    self.decodedText += chr(char)

                prevText = True
                prevNewline = False
                prevCmd = False
            elif char == 0x11: # New line
                if prevCmd:
                    self.decodedText += ' "'
                elif prevNewline:
                    self.decodedText += '"'

                self.decodedText += f'\\n"\n'

                prevText = False
                prevNewline = True
                prevCmd = False
            elif char == 0x10 or char == 0x12 or char == 0x1B: # Box Breaks add automatic newlines
                if prevText:
                    self.decodedText += '"'

                cmd, decoder = CMDMAP[char]
                self.decodedText += f'\n{decoder(cmd)}\n'

                prevText = False
                prevNewline = True
                prevCmd = False
            elif char == 0xBF: # End command, do nothing
                if prevText:
                    self.decodedText += '"'
            else: # Control Codes (see message_data_fmt_nes.h)
                if prevText:
                    self.decodedText += '" '
                elif prevCmd:
                    self.decodedText += ' '

                cmd, decoder = CMDMAP[char]
                self.decodedText += decoder(cmd)

                prevText = False
                prevNewline = False
                prevCmd = True

def parseTable(start):
    table = {}
    with open("baserom/code","rb") as f:
        f.seek(start)
        buf = f.read(8)
        textId, typePos, segment = struct.unpack(">HBxI", buf)
        while textId != 0xFFFF:
            table[segment] = (textId, typePos, segment)
            buf = f.read(8)
            textId, typePos, segment = struct.unpack(">HBxI", buf)

    return table

NES_MESSAGE_TABLE_ADDR = 0x1210D8 # Location of NES message table in baserom/code
NES_SEGMENT_ADDR = 0x08000000

def main(outfile):
    msgTable = parseTable(NES_MESSAGE_TABLE_ADDR)

    buf = []
    with open("baserom/message_data_static", "rb") as f:
        buf = f.read()

    bufLen = len(buf)
    i = 0
    messages = []
    while i + 12 < bufLen: # Next message must be able to fill a header + 1 at minimum
        addr = NES_SEGMENT_ADDR + i

        unk11F08, itemId, nextTextId, unk1206C, unk12070, unk12074 = struct.unpack(">HBHHHH", buf[i:i+11])
        i += 11
        hdr = MessageHeaderNES(unk11F08, itemId, nextTextId, unk1206C, unk12070, unk12074)

        start = i
        while i < bufLen and buf[i] != 0xBF:
            i += 1
        i += 1

        if i >= bufLen:
            break

        id, typePos, segment = msgTable[addr]
        msg = MessageNES(id, typePos, segment, hdr, buf[start:i])

        messages.append(msg)

        i = (i + 3) & ~0x3 # Next message starts on a 0x4 byte boundary

    if outfile is None:
        for msg in messages:
            sys.stdout.write(msg.macro())
            sys.stdout.write("\n")
    else:
        with open(outfile, "w") as f:
            for msg in messages:
                f.write(msg.macro())
                f.write("\n")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Extract message_data_static text")
    parser.add_argument('-o', '--outfile', help='output file to write to. None for stdout')
    args = parser.parse_args()

    main(args.outfile)
