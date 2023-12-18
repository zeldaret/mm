import struct

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
