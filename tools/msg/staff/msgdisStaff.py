#!/usr/bin/env python3

import argparse
import sys
import struct

class MessageCredits:
    def __init__(self, id, typePos, addr, text):
        self.id = id
        self.typePos = typePos
        self.addr = addr
        self.text = text
        self.decodedText = ""
        self.decodePos = 0

    def __str__(self):
        return (f' Message 0x{self.id:04X}:\n'
        f'    Segment: 0x{self.addr:08X}\n'
        f'    TypePos: 0x{self.typePos:02X}\n'
        f'    Text: {self.text}\n'
        f'    Decoded:\n{self.decodedText}')

    def macro(self):
        self.decode()
        return (
                f"DEFINE_MESSAGE(0x{self.id:04X}, 0x{self.typePos:02X},\n"
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

    def decode_cmd_color(self, cmd):
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
        color = self.text[self.decodePos]
        self.decodePos += 1
        return f'{cmd}({COLORS[color]}) '

    def decode_cmd_background(self, cmd):
        arg1 = self.text[self.decodePos]
        arg2 = self.text[self.decodePos + 1]
        arg3 = self.text[self.decodePos + 2]
        self.decodePos += 3
        return f'{cmd}("\\x{arg1:02X}","\\x{arg2:02X}","\\x{arg3:02X}")'

    def decode_cmd_highscore(self, cmd):
        HIGHSCORES = {
            0: "HS_BANK_RUPEES",
            1: "HS_UNK_1",
            2: "HS_FISHING",
            3: "HS_BOAT_ARCHERY",
            4: "HS_HORSE_BACK_BALLOON",
            6: "HS_SHOOTING_GALLERY"
        }
        highscore = self.text[self.decodePos]
        self.decodePos += 1
        return f'{cmd}({HIGHSCORES[highscore]})'

    def decode(self):
        CMDMAP = {
            0x00: ("CMD_COLOR_DEFAULT", self.decode_cmd_arg_none),
            0x04: ("CMD_BOX_BREAK", self.decode_cmd_arg_none),
            0x05: ("CMD_COLOR", self.decode_cmd_color),
            0X06: ("CMD_SHIFT", self.decode_cmd_arg_1byte),
            0x07: ("CMD_TEXTID", self.decode_cmd_arg_2byte),
            0x08: ("CMD_QUICKTEXT_ENABLE", self.decode_cmd_arg_none),
            0x09: ("CMD_QUICKTEXT_DISABLE", self.decode_cmd_arg_none),
            0x0A: ("CMD_PERSISTENT", self.decode_cmd_arg_none),
            0x0B: ("CMD_EVENT", self.decode_cmd_arg_none),
            0x0C: ("CMD_BOX_BREAK_DELAY", self.decode_cmd_arg_2byte),
            0x0D: ("CMD_WAIT_INPUT", self.decode_cmd_arg_none),
            0x0E: ("CMD_FADE", self.decode_cmd_arg_1byte),
            0x0F: ("CMD_NAME", self.decode_cmd_arg_none),
            0x10: ("CMD_OCARINA", self.decode_cmd_arg_none),
            0x11: ("CMD_FADE2", self.decode_cmd_arg_2byte),
            0x12: ("CMD_SFX", self.decode_cmd_arg_2byte),
            0x13: ("CMD_ITEM_ICON", self.decode_cmd_arg_1byte),
            0x14: ("CMD_TEXT_SPEED", self.decode_cmd_arg_1byte),
            0x15: ("CMD_BACKGROUND", self.decode_cmd_background),
            0x16: ("CMD_MARATHONTIME", self.decode_cmd_arg_none),
            0x17: ("CMD_RACETIME", self.decode_cmd_arg_none),
            0x18: ("CMD_POINTS", self.decode_cmd_arg_none),
            0x1A: ("CMD_UNSKIPPABLE", self.decode_cmd_arg_none),
            0x1B: ("CMD_TWO_CHOICE", self.decode_cmd_arg_none),
            0x1C: ("CMD_THREE_CHOICE", self.decode_cmd_arg_none),
            0x1D: ("CMD_FISH_INFO", self.decode_cmd_arg_none),
            0x1E: ("CMD_HIGHSCORE", self.decode_cmd_highscore),
            0x1F: ("CMD_TIME", self.decode_cmd_arg_none),
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

            if char >= 0x20 and char <= 0xAF: # Regular Characters
                if prevCmd:
                    self.decodedText += ' "'
                elif prevNewline:
                    self.decodedText += '"'

                if char == 0x22: # Handle escaping "
                    self.decodedText += '\\"'
                else:
                    self.decodedText += chr(char)

                prevText = True
                prevNewline = False
                prevCmd = False
            elif char == 0x1: # New line
                if prevCmd:
                    self.decodedText += ' "'
                elif prevNewline:
                    self.decodedText += '"'

                self.decodedText += f'\\n"\n'

                prevText = False
                prevNewline = True
                prevCmd = False
            elif char == 0x04 or char == 0x0C: # Box Breaks add automatic newlines
                if prevText:
                    self.decodedText += '"'

                cmd, decoder = CMDMAP[char]
                self.decodedText += f'\n{decoder(cmd)}\n'

                prevText = False
                prevNewline = True
                prevCmd = False
            elif char == 0x02: # End command, do nothing
                if prevText:
                    self.decodedText += '"'
            else: # Control Codes (see message_data_fmt_staff.h)
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
