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
        self.prop = struct.pack(">HBHHHH", unk11F08, itemId, nextTextId, unk1206C, unk12070, unk12074)

    def __str__(self):
        return (f'unk11F08: 0x{self.unk11F08:0X},\n' 
        f'    itemId: 0x{self.itemId:0X},\n' 
        f'    nextTextId: 0x{self.nextTextId:0X},\n' 
        f'    unk1206C: 0x{self.unk1206C:0X},\n'
        f'    unk12070: 0x{self.unk12070:0X},\n' 
        f'    unk12074: 0x{self.unk12074:0X}')

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
            f'"\\x{unk12074[0]:02X}\\x{unk12074[1]:02X}" '
        )


class MessageNES:
    def __init__(self, id, typePos, addr, hdr, text):
        self.id = id
        self.typePos = typePos
        self.addr = addr
        self.hdr = hdr
        self.text = text
        self.decodedText = ""

    def __str__(self):
        return (f' Message 0x{self.id:04X}:\n'
        f'    Segment: 0x{self.addr:08X}\n'
        f'    TypePos: 0x{self.typePos:02X}\n'
        f'    {str(self.hdr)}\n'
        f'    Text: {self.text}\n'
        f'    Decoded:\n{self.decodedText}')

    def macro(self):
        self.decode()
        return ( 
                f"DEFINE_MESSAGE(0x{self.id:04X}, "
                f"{self.typePos}, "
                f"{self.hdr.macro()}\n"
                f"{self.decodedText}\n)\n"
        )

    def decode(self):
        ButtonMap = {
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
        if self.decodedText == "":
            prevText = False
            prevNewline = False
            i = 0
            textLen = len(self.text)
            while i < textLen:
                char = self.text[i]
                i += 1
                if char >= 0x20 and char <= 0xBB: # Characters
                    if not prevText or prevNewline:
                        self.decodedText += '"'

                    if char == 0x22: # Handle escaping "
                        self.decodedText += '\\"'
                    elif char >= 0xB0: # Button characters
                        self.decodedText += f'{ButtonMap[char]}'
                    else:
                        self.decodedText += chr(char)

                    prevText = True
                    prevNewline = False
                elif char == 0x11: # New line
                    if not prevText or prevNewline:
                        self.decodedText += '"'

                    self.decodedText += f'\\n"\n'

                    prevText = False
                    prevNewline = True
                else: # Control Codes (see message_data_fmt_nes.h)
                    if prevText and not prevNewline:
                        self.decodedText += '" '

                    prevText = False
                    prevNewline = False
                    if char == 0x0:
                        self.decodedText += f'CMD_COLOR_DEFAULT '
                    elif char == 0x1:
                        self.decodedText += f'CMD_COLOR_RED '
                    elif char == 0x2:
                        self.decodedText += f'CMD_COLOR_GREEN '
                    elif char == 0x3:
                        self.decodedText += f'CMD_COLOR_BLUE '
                    elif char == 0x4:
                        self.decodedText += f'CMD_COLOR_YELLOW '
                    elif char == 0x5:
                        self.decodedText += f'CMD_COLOR_LIGHTBLUE '
                    elif char == 0x6:
                        self.decodedText += f'CMD_COLOR_PINK '
                    elif char == 0x7:
                        self.decodedText += f'CMD_COLOR_SILVER '
                    elif char == 0x8:
                        self.decodedText += f'CMD_COLOR_ORANGE '
                    elif char == 0x9:
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}] '
                    elif char == 0xA:
                        self.decodedText += f'CMD_0A '
                    elif char == 0xB:
                        self.decodedText += f'CMD_HS_BOAT_ARCHERY '
                    elif char == 0xC:
                        self.decodedText += f'CMD_STRAY_FAIRIES '
                    elif char == 0xD:
                        self.decodedText += f'CMD_TOKENS '
                    elif char == 0xE:
                        self.decodedText += f'CMD_0E '
                    elif char == 0xF:
                        self.decodedText += f'CMD_0F '
                    elif char == 0x10:
                        self.decodedText += f'\nCMD_BOX_BREAK\n'
                    elif char == 0x12:
                        self.decodedText += f'\nCMD_BOX_BREAK2\n'
                    elif char == 0x13:
                        self.decodedText += f'CMD_13 '
                    elif char == 0x14:
                        self.decodedText += f'CMD_SHIFT("\\x{self.text[i]}") '
                        i += 1
                    elif char == 0x15:
                        self.decodedText += f'CMD_15 '
                    elif char == 0x16:
                        self.decodedText += f'CMD_NAME '
                    elif char == 0x17:
                        self.decodedText += f'CMD_QUICKTEXT_ENABLE '
                    elif char == 0x18:
                        self.decodedText += f'CMD_QUICKTEXT_DISABLE '
                    elif char == 0x19:
                        self.decodedText += f'CMD_EVENT '
                    elif char == 0x1A:
                        self.decodedText += f'CMD_PERSISTENT '
                    elif char == 0x1B:
                        self.decodedText += f'CMD_BOX_BREAK_DELAYED("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x1C:
                        self.decodedText += f'CMD_FADE("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x1D:
                        self.decodedText += f'CMD_1D("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x1E:
                        self.decodedText += f'CMD_SFX("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x1F:
                        self.decodedText += f'CMD_DELAY("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char >= 0xBC and char <= 0xBE:
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0xBF:
                        continue # Don't add the end Ctrl code
                    elif char == 0xC0:
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}] '
                    elif char == 0xC1:
                        self.decodedText += f'CMD_BACKGROUND '
                    elif char == 0xC2:
                        self.decodedText += f'CMD_TWO_CHOICE '
                    elif char == 0xC3:
                        self.decodedText += f'CMD_THREE_CHOICE '
                    elif char == 0xC4:
                        self.decodedText += f'CMD_TIMER_POSTMAN '
                    elif char == 0xC5:
                        self.decodedText += f'CMD_TIMER_MINIGAME_1 '
                    elif char == 0xC6:
                        self.decodedText += f'CMD_TIMER_2 '
                    elif char == 0xC7:
                        self.decodedText += f'CMD_TIMER_MOON_CRASH '
                    elif char == 0xC8:
                        self.decodedText += f'CMD_TIMER_MINIGAME_2 '
                    elif char == 0xC9:
                        self.decodedText += f'CMD_TIMER_TIMER_ENV_HAZARD '
                    elif char == 0xCA:
                        self.decodedText += f'CMD_TIME '
                    elif char == 0xCB:
                        self.decodedText += f'CMD_CHEST_FLAGS '
                    elif char == 0xCC:
                        self.decodedText += f'CMD_BANK_INPUT '
                    elif char == 0xCD:
                        self.decodedText += f'CMD_CD '
                    elif char == 0xCE:
                        self.decodedText += f'CMD_CE '
                    elif char == 0xCF:
                        self.decodedText += f'CMD_TIME_UNTIL_MOON_CRASH '
                    elif char == 0xD0:
                        self.decodedText += f'CMD_DOGGY_RACETRACK_BET_INPUT '
                    elif char == 0xD1:
                        self.decodedText += f'CMD_BOMBER_CODE_INPUT '
                    elif char == 0xD2:
                        self.decodedText += f'CMD_D2 '
                    elif char == 0xD3:
                        self.decodedText += f'CMD_TIME_SPEED '
                    elif char == 0xD4:
                        self.decodedText += f'CMD_OWL_WARP '
                    elif char == 0xD5:
                        self.decodedText += f'CMD_LOTTERY_CODE_INPUT '
                    elif char == 0xD6:
                        self.decodedText += f'CMD_SPIDER_HOUSE_MASK_CODE '
                    elif char == 0xD7:
                        self.decodedText += f'CMD_STRAY_FAIRIES_LEFT_WOODFALL '
                    elif char == 0xD8:
                        self.decodedText += f'CMD_STRAY_FAIRIES_LEFT_SNOWHEAD '
                    elif char == 0xD9:
                        self.decodedText += f'CMD_STRAY_FAIRIES_LEFT_GREAT_BAY '
                    elif char == 0xDA:
                        self.decodedText += f'CMD_STRAY_FAIRIES_LEFT_STONE_TOWER '
                    elif char == 0xDB:
                        self.decodedText += f'CMD_DB '
                    elif char == 0xDC:
                        self.decodedText += f'CMD_LOTTERY_CODE '
                    elif char == 0xDD:
                        self.decodedText += f'CMD_LOTTERY_CODE_GUESS '
                    elif char == 0xDE:
                        self.decodedText += f'CMD_HELD_ITEM_PRICE '
                    elif char == 0xDF:
                        self.decodedText += f'CMD_BOMBER_CODE '
                    elif char == 0xE0:
                        self.decodedText += f'CMD_E0 '
                    elif char >= 0xE1 and char <= 0xE6:
                        self.decodedText += f'CMD_SPIDER_HOUSE_MASK_CODE_{char - 0xE1 + 1} '
                    elif char == 0xE7:
                        self.decodedText += f'CMD_HOURS_UNTIL_MOON_CRASH '
                    elif char == 0xE8:
                        self.decodedText += f'CMD_TIME_UNTIL_NEW_DAY '
                    elif char >= 0xE9 and char <= 0xEF:
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}] '
                    elif char >= 0xF0 and char <= 0xF2:
                        self.decodedText += f'CMD_{char:02X} '
                    elif char >= 0xF3 and char <= 0xF5:
                        self.decodedText += f'CMD_{char:02X} '
                    elif char == 0xF6:
                        self.decodedText += f'CMD_HS_TOWN_SHOOTING_GALLERY '
                    elif char == 0xF7:
                        self.decodedText += f'CMD_HS_UNK_1 '
                    elif char == 0xF8:
                        self.decodedText += f'CMD_HS_UNK_3_LOWER '
                    elif char == 0xF9:
                        self.decodedText += f'CMD_HS_HORSE_BACK_BALLOON '
                    elif char >= 0xFA and char <= 0xFC:
                        self.decodedText += f'CMD_HS_DEKU_PLAYGROUND_DAY_{char - 0xFA + 1} '
                    elif char >= 0xFD and char <= 0xFF:
                        self.decodedText += f'CMD_DEKU_PLAYGROUND_NAME_DAY_{char - 0xFD + 1} '
                    else:
                        print(f"Error Unknown [\\x{char:02X}] command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}] '

def parseTable(start):
    table = {}
    with open("baserom/code","rb") as f:
        f.seek(start)
        buf = f.read(8)
        textId, typePos, segment = struct.unpack(">HBxI", buf)
        while segment != 0:
            table[segment] = (textId, typePos, segment)
            buf = f.read(8)
            textId, typePos, segment = struct.unpack(">HBxI", buf)

    return table

def main(outfile):
    msgTable = parseTable(0x1210D8) # Location of NES message table in baserom/code

    buf = []
    with open("baserom/message_data_static", "rb") as f:
        buf = f.read()

    bufLen = len(buf)
    i = 0
    messages = []
    while i < bufLen:
        addr = 0x08000000 + i

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

        i = (i + 3) & ~0x3

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
