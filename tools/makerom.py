import os, struct, sys, ast, argparse

def read_uint32_be(data, offset):
    return struct.unpack('>I', data[offset:offset+4])[0]

def generate_checksum(data):
    seed = 0xDF26F436

    t1 = t2 = t3 = t4 = t5 = t6 = seed

    for i in range(0x1000, 0x1000 + 0x100000, 4):
        d = read_uint32_be(data, i)

        shift = d & 0x1F
        r = ((d << shift) & 0xFFFFFFFF) | ((d >> (32 - shift)) & 0xFFFFFFFF)

        if t6 + d > 0xFFFFFFFF:
            t4 += 1

        t6 = (t6 + d) & 0xFFFFFFFF
        t3 ^= d
        t5 = (t5 + r) & 0xFFFFFFFF

        if t2 > d:
            t2 ^= r
        else:
            t2 ^= t6 ^ d

        t1 = (t1 + (read_uint32_be(data, 0x0750 + (i & 0xFF)) ^ d)) & 0xFFFFFFFF

    chksum0 = t6 ^ t4 ^ t3
    chksum1 = t5 ^ t2 ^ t1

    return chksum0, chksum1

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('files', help='file list')
    parser.add_argument('out', help='output file')
    args = parser.parse_args()

    outputBuffer = bytearray()

    with open(args.out, 'wb') as w, open(args.files, 'rt') as f:
        total_size = 0

        dmadata_table = ast.literal_eval(f.read())
        for base_file, comp_file, _, _ in dmadata_table:
            file_name = base_file if comp_file == '' else comp_file
            if file_name != '':
                try:
                    with open(file_name, 'rb') as current_file:
                        file_data = current_file.read()
                        outputBuffer += file_data
                        total_size += len(file_data)
                except:
                    print('Could not open file ' + file_name)
                    sys.exit(1)

        while total_size < 0x2000000:
            outputBuffer.append(total_size % 256)
            total_size += 1

        chksum0, chksum1 = generate_checksum(outputBuffer)
        outputBuffer[0x10:0x18] = chksum0.to_bytes(4, byteorder='big') + chksum1.to_bytes(4, byteorder='big')

        w.write(outputBuffer)

