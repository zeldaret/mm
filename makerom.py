import os
import struct
import sys

FILENAME = 'makerom_files.txt'
OUT = 'rom.z64'

def read_uint32_be(offset):
    return struct.unpack('>I', fileData[offset:offset+4])[0]

def read_uint16_be(offset):
    return struct.unpack('>H', fileData[offset:offset+2])[0]

with open(OUT, 'wb') as w, open(FILENAME, 'rt') as f:
    file_name = f.readline().strip()
    total_size = 0

    while file_name:
        try:
            with open(file_name, 'rb') as current_file:
                file_data = current_file.read()
                w.write(file_data)
                total_size += len(file_data)
        except:
            print('Could not open file ' + file_name)
            sys.exit(1)
        file_name = f.readline().strip()

    while total_size < 0x2000000:
        w.write((total_size % 256).to_bytes(1,"big"))
        total_size += 1

