#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023-2024 ZeldaRET
# SPDX-License-Identifier: MIT

# Program to generate compressed yar (Yaz0 ARchive) files.
#
# The program expects an .o elf file and outputs a raw yar binary file and a
# "symbols" elf.
#
# A yar file consists of multiple Yaz0 files compressed individually. The
# archive begins with a header of non-fixed size, which describes the
# location of each individual Yaz0 block within the archive itself. This
# header is followed by each Yaz0 file.
#
# The first word (a 4 byte group) of the header indicates the size in bytes of
# the header itself (also describes the offset of the first Yaz0 block). The
# rest of the header consists of words describing the offsets of each Yaz0
# block relative to the end of the header, because the first Yaz0
# block is omitted from the offsets in the header.
#
# Each Yaz0 block is 0xFF-padded to a multiple of 0x10 in size.
#
# The entire archive is 0-padded to a multiple of 0x10 in size.
#
# The program works by compressing each .data symbol in the input elf file as
# its own Yaz0 compressed file, appending them in order for the generated
# archive. Other elf sections are ignored for the resulting yar file.
#
# The program also outputs an elf file that's identical to the elf input,
# but with its .data section zero'ed out completely. This "symbols" elf can be
# used for referencing each symbol as the whole file were completely
# uncompressed.

from __future__ import annotations

import argparse
import dataclasses
from pathlib import Path
import struct
import crunch64

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection


def write_word_as_bytes(buff: bytearray, offset: int, word: int):
    struct.pack_into(f">I", buff, offset, word)


@dataclasses.dataclass
class Symbol:
    name: str
    offset: int
    size: int


def get_data_from_elf(elf_path: Path) -> tuple[bytearray, list[Symbol], int]:
    uncompressed_data = bytearray()
    symbol_list: list[Symbol] = []
    data_offset = -1

    with elf_path.open("rb") as elfFile:
        elf = ELFFile(elfFile)
        for section in elf.iter_sections():
            if section.name == ".data":
                assert len(uncompressed_data) == 0
                uncompressed_data.extend(section.data())
                assert len(uncompressed_data) == section["sh_size"]
                data_offset = section["sh_offset"]
            elif section.name == ".symtab":
                assert isinstance(section, SymbolTableSection)
                for sym in section.iter_symbols():
                    if sym["st_shndx"] == "SHN_UNDEF":
                        continue
                    if sym["st_info"]["type"] != "STT_OBJECT":
                        continue
                    symbol_list.append(
                        Symbol(sym.name, sym["st_value"], sym["st_size"])
                    )
    return uncompressed_data, symbol_list, data_offset


def align_16(val: int) -> int:
    return (val + 0xF) & ~0xF


def create_archive(
    uncompressed_data: bytearray, symbol_list: list[Symbol]
) -> bytearray:
    archive = bytearray()

    first_entry_offset = (len(symbol_list) + 1) * 4

    # Fill with zeroes until the compressed data start
    archive.extend([0] * first_entry_offset)

    write_word_as_bytes(archive, 0, first_entry_offset)

    offset = first_entry_offset

    i = 0
    for sym in symbol_list:
        uncompressed_size = sym.size
        uncompressed_size_aligned = align_16(uncompressed_size)

        input_buf = uncompressed_data[sym.offset : sym.offset + uncompressed_size]
        # Make sure to pad each entry to a 0x10 boundary
        if uncompressed_size_aligned > uncompressed_size:
            input_buf.extend([0x00] * (uncompressed_size_aligned - uncompressed_size))

        compressed = bytearray(crunch64.yaz0.compress(input_buf))
        compressed_size = len(compressed)

        # Pad to 0x10
        compressed_size_aligned = align_16(compressed_size)
        if compressed_size_aligned > compressed_size:
            compressed.extend([0xFF] * (compressed_size_aligned - compressed_size))

        archive.extend(compressed)

        if i > 0:
            write_word_as_bytes(archive, i * 4, offset - first_entry_offset)

        i += 1
        offset += len(compressed)

    write_word_as_bytes(archive, i * 4, offset - first_entry_offset)

    archive_len = len(archive)
    archive_len_aligned = align_16(archive_len)
    if archive_len_aligned > archive_len:
        archive.extend([0x00] * (archive_len_aligned - archive_len))

    return archive


def main():
    parser = argparse.ArgumentParser(
        description="Program to generate compressed yar (Yaz0 ARchive) files from a built C file. Said file must only contain data symbols that do not reference other symbols (i.e. textures)."
    )
    parser.add_argument("in_file", help="Path to built .o file")
    parser.add_argument(
        "out_bin", help="Output path for the generated compressed yar binary"
    )
    parser.add_argument("out_sym", help="Output path for the generated syms elf file")

    args = parser.parse_args()

    in_path = Path(args.in_file)
    out_bin_path = Path(args.out_bin)
    out_sym_path = Path(args.out_sym)

    # Delete output files if they already exist
    out_bin_path.unlink(missing_ok=True)
    out_sym_path.unlink(missing_ok=True)

    elf_bytes = bytearray(in_path.read_bytes())

    uncompressed_data, symbol_list, data_offset = get_data_from_elf(in_path)
    assert len(uncompressed_data) > 0
    assert len(symbol_list) > 0
    assert data_offset > 0

    archive = create_archive(uncompressed_data, symbol_list)

    # Write the compressed archive file as a raw binary
    out_bin_path.write_bytes(archive)

    # Zero out data
    for i in range(data_offset, data_offset + len(uncompressed_data)):
        elf_bytes[i] = 0

    out_sym_path.write_bytes(elf_bytes)


if __name__ == "__main__":
    main()
