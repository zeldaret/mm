#!/usr/bin/env python3

import sys
import struct

from msgdisTable import parseTable

class MessageHeaderNES:
    def __init__(self, unk11F08, itemId, nextTextId, unk1206C, unk12070, unk12074):
        self.unk11F08 = unk11F08
        self.itemId = itemId
        self.nextTextId = nextTextId
        self.unk1206C = unk1206C
        self.unk12070 = unk12070
        self.unk12074 = unk12074

    def __str__(self):
        return (f'unk11F08: 0x{self.unk11F08:0X},\n' 
        f'    itemId: 0x{self.itemId:0X},\n' 
        f'    nextTextId: 0x{self.nextTextId:0X},\n' 
        f'    unk1206C: 0x{self.unk1206C:0X},\n'
        f'    unk12070: 0x{self.unk12070:0X},\n' 
        f'    unk12074: 0x{self.unk12074:0X}')

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
        f'    Decoded: "{self.decodedText}"')

    def decode(self):
        if self.decodedText == "":
            i = 0
            textLen = len(self.text)
            while i < textLen:
                char = self.text[i]
                i += 1
                if char >= 0 and char <= 0x8: # Colors
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x9: # Nothing
                    print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xA: # ??
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xB: # Boat Archery High Score
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC: # Stray Fairies
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD: # Skull Count
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xE: # Minigame score 2 digits
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xF: # Minigame score 4 digits
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x10: # New box
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x11: # New line??
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x12: # New box??
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x13: # Like 0x15
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x14:
                    spaces = self.text[i]
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({spaces})]'
                elif char == 0x15: # Like 0xBF
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x16: # Player Name
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x17: # Quick Text Enable
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x18: # Quick Text Disable
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x19: # ??
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1A: # ??
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1B: # State Timer
                    time = struct.unpack(">H", buf[i:i+2])[0]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}({time})]'
                elif char == 0x1C: # State Timer
                    time = struct.unpack(">H", buf[i:i+2])[0]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}({time})]'
                elif char == 0x1D: # State Timer
                    time = struct.unpack(">H", buf[i:i+2])[0]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}({time})]'
                elif char == 0x1E: # Play Sound
                    sound = struct.unpack(">H", buf[i:i+2])[0]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}(0x{sound:04X})]'
                elif char == 0x1F: # Delay Timer
                    time = struct.unpack(">H", buf[i:i+2])[0]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}({time})]'
                elif char >= 0x20 and char <= 0xAF: # Regular Characters
                    self.decodedText += chr(char)
                elif char >= 0xB0 and char <= 0xBB: # Texture Characters (buttons)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xBC and char <= 0xBE: # Nothing
                    print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xBF: # End Text Id
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC0: # Nothing
                    print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC1: # Background?
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC2: # 2 Choices
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC3: # 3 Choices
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC4: # Timer 1
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xC5 and char <= 0xC9: # Timer 2
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xCA: # Time
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xCB: # Flags_GetAllTreasure
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xCC: # Rupees 1
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xCD: # Rupees 2
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xCE: # Rupees 3
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xCF: # Time Until Moon Crash
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD0: # Rupees 4
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD1: # Bombers code?
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD2: # ???
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD3: # Time Speed
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD4: # Owl Warp
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD5: # Bombers code 2?
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xD6: # Spider Mask Order
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xD7 and char <= 0xDA: # Stray Fairies left
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xDB: # Minigame points
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xDC: # Lottery Code
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xDD: # Lottery Code Guess
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xDE: # Item Price
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xDF: # Actual Bomber's Code
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xE0: # End Conversation
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xE1 and char <= 0xE6: # Single Spider Mask Order
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xE7: # Hours to moon crash
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xE8: # Time to New Day
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xE9 and char <= 0xEF: # Nothing
                    print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xF0 and char <= 0xF2: # High Score points 10s
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xF3 and char <= 0xF5: # High Score points 60s
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xF6: # Town Shooting Gallery High Score
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xF7: # High Score points timers
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xF8: # High Score points 10s
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xF9 and char <= 0xFC: # High Score timers
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0xFD and char <= 0xFF: # Deku Playground Name
                    self.decodedText += f'[\\x{char:02X}]'
                else: # Other control codes
                    print(f"Error Unknown [\\x{char:02X}] command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'


if __name__ == '__main__':
    msgTable = parseTable(0x1210D8)

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

    for msg in messages:
        msg.decode()
        print(f'{msg}')