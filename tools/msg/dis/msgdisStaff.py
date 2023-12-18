#!/usr/bin/env python3

import argparse
import sys
import struct

from msgdisTable import parseTable

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
        0: "HS_HORSE_ARCHERY",
        1: "HS_POE_POINTS",
        2: "HS_LARGEST_FISH",
        3: "HS_HORSE_RACE",
        4: "HS_MARATHON",
        6: "HS_DAMPE_RACE"

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

                    if char == 0x22: # Need to escape "
                        self.decodedText += "\\"
                    self.decodedText += chr(char)

                    prevText = True
                    prevNewline = False
                elif char == 0x1: # New line??
                    if not prevText:
                        self.decodedText += '"'

                    self.decodedText += f'\\n"\n'

                    prevText = False
                    prevNewline = True
                else: # Control Codes
                    if prevText:
                        self.decodedText += '" '

                    prevText = False
                    prevNewline = False

                    if char == 0x2: # End
                        continue
                    elif char == 0x3: # None
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0x4: # Box Break
                        self.decodedText += f'\nCMD_BOX_BREAK\n'
                    elif char == 0x5: # Color
                        color = self.text[i]
                        i += 1
                        self.decodedText += f'CMD_COLOR({MessageCredits.COLORS[color]}) '
                    elif char == 0x6: # Shift
                        # shift = self.text[i]
                        # i += 1
                        # self.decodedText += f'CMD_SHIFT({shift}) '
                        self.decodedText += f'CMD_SHIFT("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0x7: # Next Text Id
                        # nextId = struct.unpack(">H", self.text[i:i+2])[0]
                        # i += 2
                        # self.decodedText += f'CMD_TEXTID({nextId}) '
                        self.decodedText += f'CMD_TEXTID("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x8: # Quick Text Enable
                        self.decodedText += f'CMD_QUICKTEXT_ENABLE '
                    elif char == 0x9: # Quick Text Disable
                        self.decodedText += f'CMD_QUICKTEXT_DISABLE '
                    elif char == 0xA: # Persistent
                        self.decodedText += f'CMD_PERSISTENT '
                    elif char == 0xB: # Event
                        self.decodedText += f'CMD_EVENT '
                    elif char == 0xC: # Box Break Delayed
                        # timer = self.text[i]
                        # i += 1
                        # self.decodedText += f'CMD_BOX_BREAK_DELAY({timer}) '
                        self.decodedText += f'CMD_BOX_BREAK_DELAY("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0xD: # Await Input
                        self.decodedText += f'CMD_WAIT_INPUT '
                    elif char == 0xE: # Fade
                        # timer = self.text[i]
                        # i += 1
                        # self.decodedText += f'CMD_FADE({timer}) '
                        self.decodedText += f'CMD_FADE("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0xF: # Player Name
                        self.decodedText += f'CMD_PLAYERNAME '
                    elif char == 0x10: # Ocarina
                        self.decodedText += f'CMD_OCARINA '
                    elif char == 0x11: # Fade 2
                        # timer = struct.unpack(">H", self.text[i:i+2])[0]
                        # i += 2
                        # self.decodedText += f'CMD_FADE2({timer}) '
                        self.decodedText += f'CMD_FADE2("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x12: # Sound
                        # sound = struct.unpack(">H", self.text[i:i+2])[0]
                        # i += 2
                        # self.decodedText += f'CMD_SOUND(0x{sound:04X}) '
                        self.decodedText += f'CMD_SOUND("\\x{self.text[i]:02X}\\x{self.text[i+1]:02X}") '
                        i += 2
                    elif char == 0x13: # Item Icon
                        # itemIcon = self.text[i]
                        # i += 1
                        # self.decodedText += f'CMD_ITEM_ICON(0x{itemIcon:02X}) '
                        self.decodedText += f'CMD_ITEM_ICON("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0x14: # Delay
                        # delay = self.text[i]
                        # i += 1
                        # self.decodedText += f'CMD_DELAY({delay}) '
                        self.decodedText += f'CMD_DELAY("\\x{self.text[i]:02X}") '
                        i += 1
                    elif char == 0x15: # Background
                        arg0, arg1, arg2 = struct.unpack(">BBB")
                        i += 3
                        self.decodedText += f'CMD_BACKGROUND("\\x{arg0:02X}, \\x{arg1:02X}, \\x{arg2:02X})'
                    elif char == 0x16: # Marathon Time
                        self.decodedText += f'CMD_MARATHONTIME '
                    elif char == 0x17: # Race Time
                        self.decodedText += f'CMD_RACETIME '
                    elif char == 0x18: # Points
                        self.decodedText += f'CMD_POINTS '
                    elif char == 0x19: # Nothing
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0x1A: # Unskippable
                        self.decodedText += f'CMD_UNSKIPPABLE '
                    elif char == 0x1B: # Two Choice
                        self.decodedText += f'CMD_TWO_CHOICE '
                    elif char == 0x1C: # Three Choice
                        self.decodedText += f'CMD_THREE_CHOICE '
                    elif char == 0x1D: # Another minigame score
                        self.decodedText += f'CMD_FISH_INFO '
                    elif char == 0x1E: # HighScore
                        hsType = self.text[i]
                        i += 1
                        self.decodedText += f'CMD_HIGHSCORE({MessageCredits.HIGHSCORES[hsType]}) '
                    elif char == 0x1F: # Time
                        self.decodedText += f'CMD_TIME '
                    else: # Other control codes
                        print(f"Error Unknown [\\x{char:02X}] command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'

def main():
    parser = argparse.ArgumentParser(description="Extract staff_message_data_static text")
    parser.add_argument("output", help="path to place extracted text")
    args = parser.parse_args()
    
    msgTable = parseTable(0x12A048) # Location of Staff message table in baserom/code

    buf = []
    with open("baserom/staff_message_data_static", "rb") as f:
        buf = f.read()

    bufLen = len(buf)
    i = 0
    messages = []
    while i < bufLen:
        addr = 0x07000000 + i

        start = i
        while i < bufLen and buf[i] != 0x2:
            i += 1
        i += 1

        if i >= bufLen:
            break

        id, typePos, segment = msgTable[addr]
        msg = MessageCredits(id, typePos, segment, buf[start:i])
        messages.append(msg)

        i = (i + 3) & ~0x3

    with open(args.output, "w") as f:
        for msg in messages:
            f.write(msg.macro())
            f.write("\n")

if __name__ == '__main__':
    main()
