#!/usr/bin/env python3

import argparse
import sys
import struct

class MessageCredits:
    COLORS = {
        0: "DEFAULT",
        1: "RED",
        2: "ADJUSTABLE",
        3: "BLUE",
        4: "LIGHTBLUE",
        5: "PURPLE",
        6: "YELLOW",
        7: "BLACK"
    }

    HIGHSCORES = {
        0: "HS_BANK_RUPEES",
        1: "HS_UNK_1",
        2: "HS_FISHING",
        3: "HS_BOAT_ARCHERY",
        4: "HS_HORSE_BACK_BALLOON",
        6: "HS_SHOOTING_GALLERY"
    }

    def __init__(self, id, typePos, addr, text):
        self.id = id
        self.typePos = typePos
        self.addr = addr
        # Has no header
        self.text = text
        self.decodedText = ""

    def __str__(self):
        return (f' Message 0x{self.id:04X}:\n'
        f'    Segment: 0x{self.addr:08X}\n'
        f'    TypePos: 0x{self.typePos:02X}\n'
        f'    Text: {self.text}\n'
        f'    Decoded:\n{self.decodedText}')

    def macro(self):
        self.decode()
        return (
                f"DEFINE_MESSAGE(0x{self.id:04X}, "
                f"0x{self.typePos:02X}, \n"
                f"{self.decodedText}\n)\n"
        )


    def decode(self):
        if self.decodedText == "":
            prevText = False
            prevNewline = False
            i = 0
            textLen = len(self.text)
            while i < textLen:
                char = self.text[i]
                i += 1

                if char >= 0x20 and char <= 0xAF: # Regular Characters
                    if not prevText:
                        self.decodedText += '"'

                    if char == 0x22: # Handle escaping "
                        self.decodedText += '\\"'
                    else:
                        self.decodedText += chr(char)

                    prevText = True
                    prevNewline = False
                elif char == 0x1: # New line
                    if not prevText or prevNewline:
                        self.decodedText += '"'

                    self.decodedText += f'\\n"\n'

                    prevText = False
                    prevNewline = True
                else: # Control Codes (see message_data_fmt_staff.h)
                    if prevText:
                        self.decodedText += '" '

                    prevText = False
                    prevNewline = False

                    if char == 0x2:
                        continue
                    elif char == 0x3:
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0x4:
                        self.decodedText += f'\nCMD_BOX_BREAK\n'
                    elif char == 0x5:
                        color = self.text[i]
                        i += 1
                        self.decodedText += f'CMD_COLOR({MessageCredits.COLORS[color]}) '
                    elif char == 0x6:
                        self.decodedText += f'CMD_SHIFT("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0x7:
                        self.decodedText += f'CMD_TEXTID("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x8:
                        self.decodedText += f'CMD_QUICKTEXT_ENABLE '
                    elif char == 0x9:
                        self.decodedText += f'CMD_QUICKTEXT_DISABLE '
                    elif char == 0xA:
                        self.decodedText += f'CMD_PERSISTENT '
                    elif char == 0xB:
                        self.decodedText += f'CMD_EVENT '
                    elif char == 0xC:
                        self.decodedText += f'CMD_BOX_BREAK_DELAY("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0xD:
                        self.decodedText += f'CMD_WAIT_INPUT '
                    elif char == 0xE:
                        self.decodedText += f'CMD_FADE("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0xF:
                        self.decodedText += f'CMD_PLAYERNAME '
                    elif char == 0x10:
                        self.decodedText += f'CMD_OCARINA '
                    elif char == 0x11:
                        self.decodedText += f'CMD_FADE2("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x12:
                        self.decodedText += f'CMD_SOUND("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x13:
                        self.decodedText += f'CMD_ITEM_ICON("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0x14:
                        self.decodedText += f'CMD_TEXT_SPEED("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0x15:
                        self.decodedText += f'CMD_BACKGROUND("\\x{self.text[i]:02X}, \\x{self.text[i + 1]:02X}, \\x{self.text[i + 2]:02X})'
                        i += 3
                    elif char == 0x16:
                        self.decodedText += f'CMD_MARATHONTIME '
                    elif char == 0x17:
                        self.decodedText += f'CMD_RACETIME '
                    elif char == 0x18:
                        self.decodedText += f'CMD_POINTS '
                    elif char == 0x19:
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0x1A:
                        self.decodedText += f'CMD_UNSKIPPABLE '
                    elif char == 0x1B:
                        self.decodedText += f'CMD_TWO_CHOICE '
                    elif char == 0x1C:
                        self.decodedText += f'CMD_THREE_CHOICE '
                    elif char == 0x1D:
                        self.decodedText += f'CMD_FISH_INFO '
                    elif char == 0x1E:
                        self.decodedText += f'CMD_HIGHSCORE({MessageCredits.HIGHSCORES[self.text[i]]}) '
                        i += 1
                    elif char == 0x1F:
                        self.decodedText += f'CMD_TIME '
                    else: # Other control codes
                        print(f"Error Unknown [\\x{char:02X}] command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'

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

STAFF_MESSAGE_TABLE_ADDR = 0x12A048 # Location of Staff message table in baserom/code
STAFF_SEGMENT_ADDR = 0x07000000

def main(outfile):
    msgTable = parseTable(STAFF_MESSAGE_TABLE_ADDR)

    buf = []
    with open("baserom/staff_message_data_static", "rb") as f:
        buf = f.read()

    bufLen = len(buf)
    i = 0
    messages = []
    while i < bufLen:
        addr = STAFF_SEGMENT_ADDR + i

        start = i
        while i < bufLen and buf[i] != 0x2:
            i += 1
        i += 1

        if i >= bufLen:
            break

        id, typePos, segment = msgTable[addr]
        msg = MessageCredits(id, typePos, segment, buf[start:i])
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
    parser = argparse.ArgumentParser(description="Extract staff_message_data_static text")
    parser.add_argument('-o', '--outfile', help='output file to write to. None for stdout')
    args = parser.parse_args()

    main(args.outfile)
