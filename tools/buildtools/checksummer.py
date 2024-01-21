#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import ipl3checksum
from pathlib import Path
import struct


def round_up(n: int, shift: int) -> int:
    mod = 1 << shift
    return (n + mod - 1) >> shift << shift


def pad_rom(rom_bytes: bytearray):
    rom_len = len(rom_bytes)
    fill_00 = round_up(rom_len, 12)
    fill_FF = round_up(fill_00, 17)

    rom_bytes.extend([0x00] * (fill_00 - rom_len))
    rom_bytes.extend([0xFF] * (fill_FF - fill_00))


def update_checksum(rom_bytes: bytearray, detect: bool):
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
    struct.pack_into(
        f">II", rom_bytes, 0x10, calculatedChecksum[0], calculatedChecksum[1]
    )


def checksummer_main():
    description = "Pads a rom and updates its header checksum"
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="input rom filename")
    parser.add_argument("out_rom", help="output rom filename")
    parser.add_argument(
        "-d",
        "--detect",
        action="store_true",
        help="Try to detect the IPL3 binary on the ROM instead of assuming the 6105 is being used. If not able to detect the IPL3 binary then this program will default to 6105",
    )

    args = parser.parse_args()

    in_path = Path(args.in_rom)
    out_path = Path(args.out_rom)
    detect: bool = args.detect

    rom_bytes = bytearray(in_path.read_bytes())

    update_checksum(rom_bytes, detect)
    pad_rom(rom_bytes)

    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_bytes(rom_bytes)


if __name__ == "__main__":
    checksummer_main()
