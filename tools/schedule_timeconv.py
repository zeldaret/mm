#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

# Convert time values such as 0x1AA9 to their schedule clock time, i.e. 8,30

from __future__ import annotations

import sys

def u16(x: int|float) -> int:
    return int(x) & 0xFFFF

def SCHEDULE_CONVERT_TIME(time: int|float) -> int:
    return u16(time - 0x10000 // 360 * 90)

def SCHEDULE_UNCONVERT_TIME(time: int) -> int:
    return time + 0x10000 // 360 * 90

time = sys.argv[1]
time = int(time, 0)

minutes = round(((24 * 60) / 0x10000) * SCHEDULE_UNCONVERT_TIME(time))

hours = int(minutes // 60)
minutes = round(minutes - 60 * hours)

# Since multiple values are mapped to the same clock time, check that it
# still matches once converted. If it doesn't match as it is, print a warning.
macro_val = SCHEDULE_CONVERT_TIME((hours * 60.0 + minutes) * ((0x10000 // 60) / 24.0))

print(f"{hours},{minutes:02} -> 0x{macro_val:04X}")
print(f"SCHEDULE_TIME({hours}, {minutes})")
if time != macro_val:
    print("Warning: Result does not match as-is")
