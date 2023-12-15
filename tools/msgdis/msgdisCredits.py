#!/usr/bin/env python3
import sys

ADDRESSMAP = {
    0x07000000: 0x4E20,
    0x0700003C: 0x4E21,
    0x07000094: 0x4E22,
    0x070000F0: 0x4E23,
    0x07000140: 0x4E24,
    0x0700019C: 0x4E25,
    0x070001D8: 0x4E26,
    0x07000248: 0x4E27,
    0x0700027C: 0x4E28,
    0x070002E0: 0x4E29,
    0x0700033C: 0x4E2A,
    0x07000384: 0x4E2B,
    0x070003C8: 0x4E2C,
    0x0700040C: 0x4E2D,
    0x07000450: 0x4E2E,
    0x070004A8: 0x4E2F,
    0x07000504: 0x4E30,
    0x07000564: 0x4E31,
    0x070005CC: 0x4E32,
    0x07000610: 0x4E33,
    0x07000654: 0x4E34,
    0x07000698: 0x4E35,
    0x070006F8: 0x4E36,
    0x07000750: 0x4E37,
    0x07000798: 0x4E38,
    0x0700081C: 0x4E39,
    0x07000888: 0x4E3A,
    0x07000924: 0x4E3B,
    0x070009B4: 0x4E3C,
    0x070009E8: 0x4E3D,
    0x07000A78: 0x4E3E,
    0x07000AB0: 0x4E3F,
    0x07000B2C: 0x4E40,
    0x07000B54: 0x4E41,
    0x07000B7C: 0x4E42,
    0x07000BA4: 0x4E43,
    0x07000BCC: 0x4E44,
    0x07000BF4: 0x4E45,
    0x07000C1C: 0x4E46,
    0x07000C44: 0x4E47,
    0x07000C6C: 0x4E48,
    0x07000CEC: 0x4E49,
    0x07000D5C: 0x4E4A,
    0x07000DC8: 0x4E4B,
    0x07000E54: 0x4E4C,
}


class MessageHeader:
    def __init__(self, unk11F08):
        self.unk11F08 = unk11F08

    def __str__(self):
        return (f'unk11F08: 0x{self.unk11F08:0X}')

class Message:
    def __init__(self, addr, hdr, text):
        self.id = ADDRESSMAP[addr]
        self.addr = addr
        self.hdr = hdr
        self.text = text
        self.decodedText = ""

    def __str__(self):
        return (f' Message 0x{self.id:04X}:\n'
        f'    Segment: 0x{self.addr:08X}\n'
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
                if char == 0x1: # Newline
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x2: # End
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x3: # None
                    print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x4: # Box Break
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x5: # Color
                    color = self.text[i]
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({color})]'
                elif char == 0x6: # Shift
                    shift = self.text[i]
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({shift})]'
                elif char == 0x7: # Next Text Id
                    nextId = self.text[i] << 8 | self.text[i + 1]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}({nextId})]'
                elif char == 0x8: # Quick Text Enable
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x9: # Quick Text Disable
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xA: # Persistent
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xB: # Event
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xC: # Box Break Delayed
                    timer = self.text[i] << 8
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({timer})]'
                elif char == 0xD: # Await Input
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0xE: # Fade
                    timer = self.text[i] << 8
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({timer})]'
                elif char == 0xF: # Player Name
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x10: # Ocarina
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x11: # Fade 2
                    timer = self.text[i] << 8 | self.text[i + 1]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}({timer})]'
                elif char == 0x12: # Sound
                    sound = self.text[i] << 8 | self.text[i + 1]
                    i += 2
                    self.decodedText += f'[\\x{char:02X}(0x{sound:04X})]'
                elif char == 0x13: # Item Icon
                    itemIcon = self.text[i]
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({itemIcon})]'
                elif char == 0x14: # Delay
                    delay = self.text[i]
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({delay})]'
                elif char == 0x15: # Background
                    arg0 = self.text[i]
                    arg1 = self.text[i + 1]
                    arg2 = self.text[i + 2]
                    i += 3
                    self.decodedText += f'[\\x{char:02X}({arg0}, {arg1}, {arg2})]'
                elif char == 0x16: # Marathon Time
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x17: # Race Time
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x18: # Points
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x19: # Nothing
                    print(f"Error [\\x{char:02X}] is not a valid command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1A: # Unskippable
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1B: # Two Choice
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1C: # Three Choice
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1D: # Another minigame score
                    self.decodedText += f'[\\x{char:02X}]'
                elif char == 0x1E: # HighScore
                    hsType = self.text[i]
                    i += 1
                    self.decodedText += f'[\\x{char:02X}({hsType})]'
                elif char == 0x1F: # Time
                    self.decodedText += f'[\\x{char:02X}]'
                elif char >= 0x20 and char <= 0xAF: # Regular Characters
                    self.decodedText += chr(char)
                else: # Other control codes
                    print(f"Error Unknown [\\x{char:02X}] command", file=sys.stderr)
                    self.decodedText += f'[\\x{char:02X}]'



def parseHeader(buf, i):
    unk11F08 = buf[i] << 8 | buf[i + 1]
    hdr = MessageHeader(unk11F08)
    return hdr

messages = []

if __name__ == '__main__':
    buf = []
    with open("baserom/staff_message_data_static", "rb") as f:
        buf = f.read()

    bufLen = len(buf) - 5
    i = 0
    while i < bufLen:
        addr = 0x07000000 + i
        hdr = parseHeader(buf, i)
        i += 2
        start = i
        while buf[i] != 0x2:
            i += 1

        i += 1
        msg = Message(addr, hdr, buf[start:i])
        messages.append(msg)
        i = (i + 3) & ~0x3

    for msg in messages:
        msg.decode()
        print(f'{msg}')