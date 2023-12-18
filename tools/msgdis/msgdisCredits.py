#!/usr/bin/env python3
import sys
import struct

from msgdisTable import parseTable

class MessageCredits:
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

    def decode(self):
        if self.decodedText == "":
            prevText = False
            i = 0
            textLen = len(self.text)
            while i < textLen:
                char = self.text[i]
                i += 1

                if char >= 0x20 and char <= 0xAF: # Regular Characters
                    if not prevText:
                        self.decodedText += '"'
                    self.decodedText += chr(char)
                    prevText = True
                else: # Control Codes
                    if prevText:
                        self.decodedText += '" '
                        prevText = False
                    if char == 0x1: # Newline
                        self.decodedText += f'CTRL_NEWLINE\n'
                    elif char == 0x2: # End
                        self.decodedText += f'CTRL_END'
                    elif char == 0x3: # None
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0x4: # Box Break
                        self.decodedText += f'\nCTRL_BOX_BREAK\n'
                    elif char == 0x5: # Color
                        color = self.text[i]
                        i += 1
                        self.decodedText += f'CTRL_COLOR({color}) '
                    elif char == 0x6: # Shift
                        shift = self.text[i]
                        i += 1
                        self.decodedText += f'CTRL_SHIFT({shift}) '
                    elif char == 0x7: # Next Text Id
                        nextId = struct.unpack(">H", self.text[i:i+2])[0]
                        i += 2
                        self.decodedText += f'CTRL_TEXTID({nextId}) '
                    elif char == 0x8: # Quick Text Enable
                        self.decodedText += f'CTRL_QUICKTEXT_ENABLE '
                    elif char == 0x9: # Quick Text Disable
                        self.decodedText += f'CTRL_QUICKTEXT_DISABLE '
                    elif char == 0xA: # Persistent
                        self.decodedText += f'CTRL_PERSISTNET '
                    elif char == 0xB: # Event
                        self.decodedText += f'CTRL_EVENT '
                    elif char == 0xC: # Box Break Delayed
                        timer = self.text[i] << 8
                        i += 1
                        self.decodedText += f'CTRL_BOX_BREAK_DELAY(timer) '
                    elif char == 0xD: # Await Input
                        self.decodedText += f'CTRL_WAIT_INPUT '
                    elif char == 0xE: # Fade
                        timer = self.text[i] << 8
                        i += 1
                        self.decodedText += f'CTRL_FADE({timer}) '
                    elif char == 0xF: # Player Name
                        self.decodedText += f'CTRL_PLAYERNAME '
                    elif char == 0x10: # Ocarina
                        self.decodedText += f'CTRL_OCARINA '
                    elif char == 0x11: # Fade 2
                        timer = struct.unpack(">H", self.text[i:i+2])[0]
                        i += 2
                        self.decodedText += f'CTRL_FADE2({timer}) '
                    elif char == 0x12: # Sound
                        sound = struct.unpack(">H", self.text[i:i+2])[0]
                        i += 2
                        self.decodedText += f'CTRL_SOUND(0x{sound:04X}) '
                    elif char == 0x13: # Item Icon
                        itemIcon = self.text[i]
                        i += 1
                        self.decodedText += f'CTRL_ITEM_ICON(0x{itemIcon:02X}) '
                    elif char == 0x14: # Delay
                        delay = self.text[i]
                        i += 1
                        self.decodedText += f'CTRL_DELAY({delay}) '
                    elif char == 0x15: # Background
                        arg0, arg1, arg2 = struct.unpack(">BBB")
                        i += 3
                        self.decodedText += f'CTRL_BACKGROUND({arg0}, {arg1}, {arg2})'
                    elif char == 0x16: # Marathon Time
                        self.decodedText += f'CTRL_MARATHONTIME '
                    elif char == 0x17: # Race Time
                        self.decodedText += f'CTRL_RACETIME '
                    elif char == 0x18: # Points
                        self.decodedText += f'CTRL_POINTS '
                    elif char == 0x19: # Nothing
                        print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'
                    elif char == 0x1A: # Unskippable
                        self.decodedText += f'CTRL_UNSKIPPABLE '
                    elif char == 0x1B: # Two Choice
                        self.decodedText += f'CTRL_TWO_CHOICE '
                    elif char == 0x1C: # Three Choice
                        self.decodedText += f'CTRL_THREE_CHOICE '
                    elif char == 0x1D: # Another minigame score
                        self.decodedText += f'CTRL_MINIGAME '
                    elif char == 0x1E: # HighScore
                        hsType = self.text[i]
                        i += 1
                        self.decodedText += f'CTRL_HIGHSCORE({hsType}) '
                    elif char == 0x1F: # Time
                        self.decodedText += f'CTRL_TIME '
                    else: # Other control codes
                        print(f"Error Unknown [\\x{char:02X}] command", file=sys.stderr)
                        self.decodedText += f'[\\x{char:02X}]'

if __name__ == '__main__':
    msgTable = parseTable(0x12A048)

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

    for msg in messages:
        msg.decode()
        print(f'{msg}')
