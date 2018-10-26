import os
import struct

FILENAME = 'build/rom.elf'
OUT = 'rom.z64'

try:
    with open(FILENAME, 'rb') as f:
        fileData = f.read()
except IOError:
    print('failed to read file ' + FILENAME)

def read_uint32_be(offset):
    return struct.unpack('>I', fileData[offset:offset+4])[0]

def read_uint16_be(offset):
    return struct.unpack('>H', fileData[offset:offset+2])[0]

with open(OUT, 'wb') as w:
    sht_off = read_uint32_be(0x20)
    sh_size = read_uint16_be(0x2E)
    num_sections = read_uint16_be(0x30)

    total_size = 0
    for i in range(0, num_sections):
        type_ = read_uint32_be(sht_off + i*sh_size + 0x04)
        offset = read_uint32_be(sht_off + i*sh_size + 0x10)
        size = read_uint32_be(sht_off + i*sh_size + 0x14)
        if type_ == 1:# SHT_PROGBITS
            total_size += size
            w.write(fileData[offset:offset+size])

    while total_size < 0x2000000:
        w.write((total_size % 256).to_bytes(1,"big"))
        total_size += 1
    
