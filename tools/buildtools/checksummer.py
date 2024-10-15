#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import ipl3checksum
from pathlib import Path
import struct
from typing import BinaryIO


def round_up(n: int, shift: int) -> int:
    mod = 1 << shift
    return (n + mod - 1) >> shift << shift


def pad_rom(f: BinaryIO, rom_len: int):
    fill_00 = round_up(rom_len, 12)
    fill_FF = round_up(fill_00, 17)

    f.seek(rom_len)

    if fill_00 > rom_len:
        f.write(b"\0" * (fill_00 - rom_len))
    if fill_FF > fill_00:
        f.write(b"\xFF" * (fill_FF - fill_00))


def update_checksum(f: BinaryIO, detect: bool):
    rom_bytes = f.read(0x101000)
    assert len(rom_bytes) == 0x101000, "Small ROM?"

    # Detect CIC
    if detect:
        cicKind = ipl3checksum.detectCIC(rom_bytes)
        if cicKind is None:
            print("Not able to detect CIC, defaulting to 6105")
            cicKind = ipl3checksum.CICKind.CIC_X105
    else:
        cicKind = ipl3checksum.CICKind.CIC_X105

    # Calculate checksum
    calculatedChecksum = cicKind.calculateChecksum(rom_bytes)
    assert calculatedChecksum is not None, "Not able to calculate checksum"

    # Write checksum
    checksum_bytes = struct.pack(f">II", calculatedChecksum[0], calculatedChecksum[1])
    f.seek(0x10)
    f.write(checksum_bytes)


def checksummer_main():
    description = "Pads a rom in-place and updates its header checksum"
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("rom", help="input rom filename")
    parser.add_argument(
        "-d",
        "--detect",
        action="store_true",
        help="Try to detect the IPL3 binary on the ROM instead of assuming the 6105 is being used. If not able to detect the IPL3 binary then this program will default to 6105",
    )

    args = parser.parse_args()

    rom_path = Path(args.rom)
    detect: bool = args.detect

    rom_len = rom_path.stat().st_size

    with rom_path.open("rb+") as f:
        update_checksum(f, detect)
        pad_rom(f, rom_len)


if __name__ == "__main__":
    checksummer_main()
