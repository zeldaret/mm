#!/usr/bin/env python3

import hashlib, io, struct, sys
from os import path

from libyaz0 import decompress

UNCOMPRESSED_SIZE = 0x2F00000

def as_word(b, off=0):
    return struct.unpack(">I", b[off:off+4])[0]

def as_word_list(b):
    return [i[0] for i in struct.iter_unpack(">I",  b)]

def calc_crc(rom_data, cic_type):
    start = 0x1000
    end = 0x101000

    unsigned_long = lambda i: i & 0xFFFFFFFF
    rol = lambda i, b: unsigned_long(i << b) | (i >> (-b & 0x1F))

    if cic_type == 6101 or cic_type == 6102:
        seed = 0xF8CA4DDC
    elif cic_type == 6103:
        seed = 0xA3886759
    elif cic_type == 6105:
        seed = 0xDF26F436
    elif cic_type == 6106:
        seed = 0x1FEA617A
    else:
        assert False , f"Unknown cic type: {cic_type}"

    t1 = t2 = t3 = t4 = t5 = t6 = seed

    for pos in range(start, end, 4):
        d = as_word(rom_data, pos)
        r = rol(d, d & 0x1F)

        t6d = unsigned_long(t6 + d)
        if t6d < t6:
            t4 = unsigned_long(t4 + 1)
        t6 = t6d
        t3 ^= d
        t5 = unsigned_long(t5 + r)

        if t2 > d:
            t2 ^= r
        else:
            t2 ^= t6 ^ d

        if cic_type == 6105:
            t1 = unsigned_long(t1 + (as_word(rom_data, 0x0750 + (pos & 0xFF)) ^ d))
        else:
            t1 = unsigned_long(t1 + (t5 ^ d))

    chksum = [0,0]

    if cic_type == 6103:
        chksum[0] = unsigned_long((t6 ^ t4) + t3)
        chksum[1] = unsigned_long((t5 ^ t2) + t1)
    elif cic_type == 6106:
        chksum[0] = unsigned_long((t6 * t4) + t3)
        chksum[1] = unsigned_long((t5 * t2) + t1)
    else:
        chksum[0] = t6 ^ t4 ^ t3
        chksum[1] = t5 ^ t2 ^ t1

    return struct.pack(">II", chksum[0], chksum[1])

def read_dmadata_entry(addr):
    return as_word_list(fileContent[addr:addr+0x10])

def read_dmadata(start):
    dmadata = []
    addr = start
    entry = read_dmadata_entry(addr)
    i = 0
    while any([e != 0 for e in entry]):
        # print(f"0x{addr:08X} " + str([f"{e:08X}" for e in entry]))
        dmadata.append(entry)
        addr += 0x10
        i += 1
        entry = read_dmadata_entry(addr)
    # print(f"0x{addr:08X} " + str([f"{e:08X}" for e in entry]))
    return dmadata

def update_crc(decompressed):
    print("Recalculating crc...")
    new_crc = calc_crc(decompressed.getbuffer(), 6105)

    decompressed.seek(0x10)
    decompressed.write(new_crc)
    return decompressed

def decompress_rom(dmadata_addr, dmadata):
    rom_segments = {} # vrom start : data s.t. len(data) == vrom_end - vrom_start
    new_dmadata = bytearray() # new dmadata: {vrom start , vrom end , vrom start , 0}

    decompressed = io.BytesIO(b"")

    for v_start, v_end, p_start, p_end in dmadata:
        if p_start == 0xFFFFFFFF and p_end == 0xFFFFFFFF:
            new_dmadata.extend(struct.pack(">IIII", v_start, v_end, p_start, p_end))
            continue
        if p_end == 0: # uncompressed
            rom_segments.update({v_start : fileContent[p_start:p_start + v_end - v_start]})
        else: # compressed
            rom_segments.update({v_start : decompress(fileContent[p_start:p_end])})
        new_dmadata.extend(struct.pack(">IIII", v_start, v_end, v_start, 0))

    # write rom segments to vaddrs
    for vrom_st,data in rom_segments.items():
        decompressed.seek(vrom_st)
        decompressed.write(data)
    # write new dmadata
    decompressed.seek(dmadata_addr)
    decompressed.write(new_dmadata)
    # pad to size
    decompressed.seek(UNCOMPRESSED_SIZE-1)
    decompressed.write(bytearray([0]))
    # re-calculate crc
    return update_crc(decompressed)

correct_compressed_str_hash = "2a0a8acb61538235bc1094d297fb6556"
correct_str_hash = "f46493eaa0628827dbd6ad3ecd8d65d6"

def get_str_hash(byte_array):
    return str(hashlib.md5(byte_array).hexdigest())

# If the baserom exists and is correct, we don't need to change anything
if path.exists("baserom_uncompressed.z64"):
    with open("baserom_uncompressed.z64", mode="rb") as file:
        fileContent = bytearray(file.read())
        if get_str_hash(fileContent) == correct_str_hash:
            print("Found valid baserom - exiting early")
            sys.exit(0)

# Determine if we have a ROM file
romFileName = ""
if path.exists("baserom.mm.us.rev1.z64"):
    romFileName = "baserom.mm.us.rev1.z64"
elif path.exists("baserom.mm.us.rev1.n64"):
    romFileName = "baserom.mm.us.rev1.n64"
elif path.exists("baserom.mm.us.rev1.v64"):
    romFileName = "baserom.mm.us.rev1.v64"
else:
    print("Error: Could not find baserom.mm.us.rev1.z64/baserom.mm.us.rev1.n64/baserom.mm.us.rev1.v64.")
    sys.exit(1)

# Read in the original ROM
print("File '" + romFileName + "' found.")
with open(romFileName, mode="rb") as file:
    fileContent = bytearray(file.read())

fileContentLen = len(fileContent)

# Check if ROM needs to be byte/word swapped
# Little-endian
if fileContent[0] == 0x40:
    # Word Swap ROM
    print("ROM needs to be word swapped...")
    words = str(int(fileContentLen/4))
    little_byte_format = "<" + words + "I"
    big_byte_format = ">" + words + "I"
    tmp = struct.unpack_from(little_byte_format, fileContent, 0)
    struct.pack_into(big_byte_format, fileContent, 0, *tmp)

    print("Word swapping done.")

# Byte-swapped
elif fileContent[0] == 0x37:
    # Byte Swap ROM
    print("ROM needs to be byte swapped...")
    halfwords = str(int(fileContentLen/2))
    little_byte_format = "<" + halfwords + "H"
    big_byte_format = ">" + halfwords + "H"
    tmp = struct.unpack_from(little_byte_format, fileContent, 0)
    struct.pack_into(big_byte_format, fileContent, 0, *tmp)

    print("Byte swapping done.")

# Check to see if the ROM is a compressed "vanilla" ROM
compressed_str_hash = get_str_hash(bytearray(fileContent))
if compressed_str_hash != correct_compressed_str_hash:
    print("Error: Expected a hash of " + correct_compressed_str_hash + " but got " + compressed_str_hash + ". " +
          "The baserom has probably been tampered, find a new one")
    sys.exit(1)

# Decompress
FILE_TABLE_OFFSET = 0x1A500 # 0x1C110 for JP1.0, 0x1C050 for JP1.1, 0x24F60 for debug
if any([b != 0 for b in fileContent[FILE_TABLE_OFFSET + 0x9C:FILE_TABLE_OFFSET + 0x9C + 0x4]]):
    print("Decompressing rom...")
    fileContent = decompress_rom(FILE_TABLE_OFFSET, read_dmadata(FILE_TABLE_OFFSET)).getbuffer()

# FF Padding (TODO is there an automatic way we can find where to start padding from? Largest dmadata file end maybe?)
for i in range(0x2EE8000,UNCOMPRESSED_SIZE):
    fileContent[i] = 0xFF

# Check to see if the ROM is a "vanilla" ROM
str_hash = get_str_hash(bytearray(fileContent))
if str_hash != correct_str_hash:
    print("Error: Expected a hash of " + correct_str_hash + " but got " + str_hash + ". " +
          "The baserom has probably been tampered, find a new one")
    sys.exit(1)

# Write out our new ROM
print("Writing new ROM 'baserom_uncompressed.z64'.")
with open("baserom_uncompressed.z64", "wb") as file:
    file.write(bytes(fileContent))

print("Done!")
