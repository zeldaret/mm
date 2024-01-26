#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 ZeldaRET
# SPDX-License-Identifier: CC0-1.0

from __future__ import annotations

import argparse
import dataclasses
import hashlib
import io
import struct
import sys

from pathlib import Path
from typing import Callable

import crunch64
import ipl3checksum
import zlib

def decompress_zlib(data: bytes) -> bytes:
    decomp = zlib.decompressobj(-zlib.MAX_WBITS)
    output = bytearray()
    output.extend(decomp.decompress(data))
    while decomp.unconsumed_tail:
        output.extend(decomp.decompress(decomp.unconsumed_tail))
    output.extend(decomp.flush())
    return bytes(output)


def decompress(data: bytes, is_zlib_compressed: bool) -> bytes:
    if is_zlib_compressed:
        return decompress_zlib(data)
    return crunch64.yaz0.decompress(data)


@dataclasses.dataclass
class VersionInfo:
    md5sum: str
    file_table_offset: int
    fixes: Callable[[bytearray], bytearray] | None

VERSIONS = {
    "us": VersionInfo("f46493eaa0628827dbd6ad3ecd8d65d6", 0x1A500, None)
}


def round_up(n, shift):
    mod = 1 << shift
    return (n + mod - 1) >> shift << shift


def as_word_list(b) -> list[int]:
    return [i[0] for i in struct.iter_unpack(">I", b)]


def read_dmadata_entry(file_content: bytearray, addr: int) -> list[int]:
    return as_word_list(file_content[addr : addr + 0x10])


def read_dmadata(file_content: bytearray, start) -> list[list[int]]:
    dmadata = []
    addr = start
    entry = read_dmadata_entry(file_content, addr)
    i = 0
    while any([e != 0 for e in entry]):
        dmadata.append(entry)
        addr += 0x10
        i += 1
        entry = read_dmadata_entry(file_content, addr)
    return dmadata


def update_crc(decompressed: io.BytesIO) -> io.BytesIO:
    print("Recalculating crc...")
    calculated_checksum = ipl3checksum.CICKind.CIC_X105.calculateChecksum(
        bytes(decompressed.getbuffer())
    )
    new_crc = struct.pack(f">II", calculated_checksum[0], calculated_checksum[1])

    decompressed.seek(0x10)
    decompressed.write(new_crc)
    return decompressed


def decompress_rom(
    file_content: bytearray, dmadata_addr: int, dmadata: list[list[int]], use_zlib: bool
) -> bytearray:
    rom_segments = {}  # vrom start : data s.t. len(data) == vrom_end - vrom_start
    new_dmadata = bytearray()  # new dmadata: {vrom start , vrom end , vrom start , 0}

    decompressed = io.BytesIO(b"")

    for v_start, v_end, p_start, p_end in dmadata:
        if p_start == 0xFFFFFFFF and p_end == 0xFFFFFFFF:
            new_dmadata.extend(struct.pack(">IIII", v_start, v_end, p_start, p_end))
            continue
        if p_end == 0:  # uncompressed
            rom_segments.update(
                {v_start: file_content[p_start : p_start + v_end - v_start]}
            )
        else:  # compressed
            rom_segments.update(
                {
                    v_start: decompress(
                        file_content[p_start:p_end], use_zlib
                    )
                }
            )
        new_dmadata.extend(struct.pack(">IIII", v_start, v_end, v_start, 0))

    # write rom segments to vaddrs
    for vrom_st, data in rom_segments.items():
        decompressed.seek(vrom_st)
        decompressed.write(data)
    # write new dmadata
    decompressed.seek(dmadata_addr)
    decompressed.write(new_dmadata)
    # pad to size
    padding_end = round_up(dmadata[-1][1], 17)
    decompressed.seek(padding_end - 1)
    decompressed.write(bytearray([0]))
    # re-calculate crc
    return bytearray(update_crc(decompressed).getbuffer())


def get_str_hash(byte_array):
    return str(hashlib.md5(byte_array).hexdigest())


def check_existing_rom(rom_path: Path, correct_str_hash: str):
    # If the baserom exists and is correct, we don't need to change anything
    if rom_path.exists():
        if get_str_hash(rom_path.read_bytes()) == correct_str_hash:
            return True
    return False


def word_swap(file_content: bytearray) -> bytearray:
    words = str(int(len(file_content) / 4))
    little_byte_format = "<" + words + "I"
    big_byte_format = ">" + words + "I"
    tmp = struct.unpack_from(little_byte_format, file_content, 0)
    struct.pack_into(big_byte_format, file_content, 0, *tmp)
    return file_content


def byte_swap(file_content: bytearray) -> bytearray:
    halfwords = str(int(len(file_content) / 2))
    little_byte_format = "<" + halfwords + "H"
    big_byte_format = ">" + halfwords + "H"
    tmp = struct.unpack_from(little_byte_format, file_content, 0)
    struct.pack_into(big_byte_format, file_content, 0, *tmp)
    return file_content


def pad_rom(file_content: bytearray, dmadata: list[list[int]]) -> bytearray:
    padding_start = round_up(dmadata[-1][1], 12)
    padding_end = round_up(padding_start, 17)
    print(f"Padding from {padding_start:X} to {padding_end:X}...")
    for i in range(padding_start, padding_end):
        file_content[i] = 0xFF
    return file_content

# Determine if we have a ROM file
ROM_FILE_EXTENSIONS = ["z64", "n64", "v64"]

def find_baserom(version: str) -> Path | None:
    for rom_file_ext_lower in ROM_FILE_EXTENSIONS:
        for rom_file_ext in (rom_file_ext_lower, rom_file_ext_lower.upper()):
            rom_file_name_candidate =  Path(f"baserom.{rom_file_ext}")
            if rom_file_name_candidate.exists():
                return rom_file_name_candidate
    return None


def main():
    description = "Convert a rom that uses dmadata to an uncompressed one."

    parser = argparse.ArgumentParser(description=description)
    parser.add_argument("version", help="Version of the game to decompress.", choices=list(VERSIONS.keys()))

    args = parser.parse_args()

    version = args.version

    uncompressed_path = Path(f"baserom-decompressed.z64")

    version_info = VERSIONS[version]

    if check_existing_rom(uncompressed_path, version_info.md5sum):
        print("Found valid baserom - exiting early")
        return

    rom_file_name = find_baserom(version)

    if rom_file_name is None:
        path_list = [
            f"baserom.{rom_file_ext}" for rom_file_ext in ROM_FILE_EXTENSIONS
        ]
        print(f"Error: Could not find {','.join(path_list)}.", file=sys.stderr)
        exit(1)

    # Read in the original ROM
    print(f"File '{rom_file_name}' found.")

    file_content = bytearray(rom_file_name.read_bytes())

    # Check if ROM needs to be byte/word swapped
    # Little-endian
    if file_content[0] == 0x40:
        # Word Swap ROM
        print("ROM needs to be word swapped...")
        file_content = word_swap(file_content)
        print("Word swapping done.")

    # Byte-swapped
    elif file_content[0] == 0x37:
        # Byte Swap ROM
        print("ROM needs to be byte swapped...")
        file_content = byte_swap(file_content)
        print("Byte swapping done.")

    if version_info.fixes is not None:
        file_content = version_info.fixess(file_content, version)

    dmadata = read_dmadata(file_content, version_info.file_table_offset)
    # Decompress
    if any(
        [
            b != 0
            for b in file_content[
                version_info.file_table_offset + 0x9C : version_info.file_table_offset + 0x9C + 0x4
            ]
        ]
    ):
        print("Decompressing rom...")
        file_content = decompress_rom(file_content, version_info.file_table_offset, dmadata, version in {"ique-cn", "ique-zh"})

    file_content = pad_rom(file_content, dmadata)

    # Check to see if the ROM is a "vanilla" ROM
    str_hash = get_str_hash(file_content)
    if str_hash != version_info.md5sum:
        print(
            f"Error: Expected a hash of {version_info.md5sum} but got {str_hash}. The baserom has probably been tampered, find a new one", file=sys.stderr
        )
        exit(1)

    # Write out our new ROM
    print(f"Writing new ROM {uncompressed_path}.")
    uncompressed_path.write_bytes(file_content)

    print("Done!")


if __name__ == "__main__":
    main()
