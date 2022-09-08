#!/usr/bin/env python3
#
#   Message Table Parser
#

import argparse, os, struct, io
from actor_symbols import resolve_symbol

script_dir = os.path.dirname(os.path.realpath(__file__))
repo = script_dir + os.sep +  ".." + os.sep + ".." + os.sep






class Message():
    """Not quite sure what the format of this is, but has a chunk of character codes, and ends in \xbf"""
    
    MSG_END = b'\xbf'
    def __init__(self, data):
        self.data = data
    
    def dump(self, width=16):
        remainder = self.data
        while len(remainder) > 0:
            line, remainder = remainder[:width], remainder[width:]
            bytedump = " ".join(f"{char:02X}" for char in line)
            asciidump = "".join(f"{chr(char)}" for char in line)
            
            print(f"{bytedump:{3*width}} | {asciidump}")

    @property
    def size(self):
        return len(self.data)
    
    def __repr__(self):
        return f"Message({self.data})"

class MessageTableEntry():
    def __init__(self, text_id, typepos, psegment):
        self.text_id = text_id
        self.typepos = typepos
        self.psegment = psegment
        self._message = None

    @property
    def message(self):
        if self._message is None:
            with open(os.path.join("baserom","message_data_static"), 'rb') as f:
                f.seek( self.psegment & ~0x08000000)
                data = bytearray()
                ch = None
                while ch != Message.MSG_END:
                    ch = f.read(1)
                    data += ch
            self._message = Message(data)
        return self._message
        
    def __repr__(self):
        return f"MessageTableEntry(0x{self.text_id:X}, {self.typepos}, 0x{self.psegment:08X})"

class MessageTable():
    FMT = ">HBxL"

    def __init__(self, message_table_buffer):
        self.entries = [MessageTableEntry(*data) for data in struct.iter_unpack(MessageTable.FMT, message_table_buffer)]
    
    def __iter__(self):
        for e in self.entries:
            yield e
    
    def __getitem__(self, idx):
        return self.entries[idx]


def extract_message_table(address):
    """Extract the message table (in z_message.data.s) pointed to by the given address"""
    data = bytearray()
    with open(repo + os.path.join("data", "code", "z_message.data.s"), "r") as f:
        do_capture = False
        for line in f.readlines():
            if f"glabel D_{address:08X}" in line:
                do_capture = True
                continue
            if do_capture:
                if line == "\n":
                    break
                data.extend(struct.pack(">L", int(line.split("0x")[1].rstrip(),16)))
    return MessageTable(data)

def main():
    parser = argparse.ArgumentParser(description="Parses message table")
    parser.add_argument('address', help="VRAM or ROM address to parse", type=lambda s : int(s.replace("D_", "0x"), 16))
    parser.add_argument('text_id', help="textId to print to the console", nargs='?', default=-1, type=lambda s : int(s,0))
    args = parser.parse_args()

    msgtable = extract_message_table(args.address)

    msgentry = next(filter(lambda x: x.text_id == args.text_id, msgtable))
    print(msgentry)
    msgentry.message.dump()


if __name__ == "__main__":
    main()
