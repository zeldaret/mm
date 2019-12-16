#!/usr/bin/env python3
import os, sys, argparse

def read_file(name):
    file_data=[]

    try:
        with open(name, 'rb') as f:
            file_data = f.read()
    except IOError:
        print('failed to read file ' + name)
        sys.exit(2)
    return file_data


def write_file(name, file_data):
    try:
        with open(name, 'wb') as f:
            f.write(file_data)
    except IOError:
        print('failed to write file ' + name)
        sys.exit(2)


def yaz0_decompress(input):
    output = bytearray()

    return output


max_len = 0xFF + 0x12
def back_seach(input, size, start_pos):
    best_len = 1
    match_pos = 0
    search_pos = max(start_pos - 0x1000, 0)
    end_pos = min(size, start_pos + max_len)

    # Seach for substrings that are at least 3 bytes long (the smallest size resulting in a compressed chunk)
    token_end_pos = min(start_pos + 3, size)
    seatch_len = token_end_pos - start_pos
    token = input[start_pos:token_end_pos]

    while search_pos < start_pos:
        search_pos = input.find(token, search_pos, start_pos + seatch_len - 1)
        if search_pos == -1:
            break

        pos1 = search_pos + seatch_len
        pos2 = start_pos + seatch_len

        # Find how many more bytes match
        while pos2 < end_pos and input[pos1] == input[pos2]:
            pos1 += 1
            pos2 += 1

        found_len = pos2 - start_pos

        if found_len > best_len:
            best_len = found_len
            seatch_len = found_len
            match_pos = search_pos

            if best_len == max_len:
                break

            token_end_pos = start_pos + seatch_len
            token = input[start_pos:start_pos + seatch_len]

        search_pos += 1

    return best_len, match_pos


prev_flag = False
prev_len = 0
prev_pos = 0
def cached_encode(input, size, pos):
    global prev_flag
    global prev_len
    global prev_pos

    # If a previous search found that it was better to have an uncompressed byte, return the position and length that we already found
    if prev_flag:
        prev_flag = False
        return prev_len, prev_pos

    comp_len, comp_pos = back_seach(input, size, pos)

    # Check that it wouldn't be better to have an uncompressed byte then compressing the following data
    if comp_len >= 3:
        prev_len, prev_pos = back_seach(input, size, pos + 1)
        if prev_len >= comp_len + 2: # +2 to account for the uncompressed byte plus 1 more to see if it's better compression
            comp_len = 1
            prev_flag = True

    return comp_len, comp_pos


def write_yaz0_header(output, size):
    output += 'Yaz0'.encode()

    output.append((size & 0xFF000000) >> 24)
    output.append((size & 0x00FF0000) >> 16)
    output.append((size & 0x0000FF00) >> 8)
    output.append( size & 0x000000FF)

    output += '\0\0\0\0\0\0\0\0'.encode()


def yaz0_compress(input):
    output = bytearray()

    decompressed_size = len(input)

    write_yaz0_header(output, decompressed_size)

    curr_pos = 0
    chunk_bits = 0
    chunk_num_bits = 0
    chunk_data = bytearray()
    while curr_pos < decompressed_size:
        num_bytes, match_pos = cached_encode(input, decompressed_size, curr_pos)

        if num_bytes < 3:
            chunk_data.append(input[curr_pos])
            curr_pos += 1
            chunk_bits |= (0x80 >> chunk_num_bits)
        else:
            dist = curr_pos - match_pos - 1

            if num_bytes >= 0x12:
                chunk_data.append(dist >> 8)
                chunk_data.append(dist & 0xFF)
                chunk_data.append(num_bytes - 0x12)
            else:
                chunk_data.append(((num_bytes - 2) << 4) | (dist >> 8))
                chunk_data.append(dist & 0xFF)

            curr_pos += num_bytes

        chunk_num_bits += 1

        if chunk_num_bits == 8:
            output.append(chunk_bits)
            output += chunk_data

            chunk_bits = 0
            chunk_num_bits = 0
            chunk_data = bytearray()

    if chunk_num_bits > 0:
        output.append(chunk_bits)
        output += chunk_data

    output_size = len(output)
    output_padding_amount = ((output_size + 15) // 16) * 16 - output_size
    for i in range(output_padding_amount):
        output.append(0)

    return output


def main(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('input', help='input file')
    parser.add_argument('output', help='output file')
    parser.add_argument('-d', '--decompress', help='decompress file, otherwise compress it', action='store_true', default=False)
    args = parser.parse_args()

    input_data = read_file(args.input)

    if args.decompress:
        output_data = yaz0_decompress(input_data)
    else:
        output_data = yaz0_compress(input_data)

    write_file(args.output, output_data)


if __name__ == "__main__":
    main(sys.argv[1:])