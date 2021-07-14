#!/usr/bin/env python3
#
#   Convert time values such as 0x1AAA to their clock time, i.e. 2,30
#   The time is output with a comma for easy copy-pasting into a macro
#

import sys

def convert(time):
    seconds = round(((24 * 60 * 60) / 0x10000) * time)

    hours = int(seconds // 3600)
    minutes = int((seconds - 3600 * hours) // 60)
    seconds = int(seconds - (3600 * hours + 60 * minutes))

    # Since multiple values are mapped to the same clock time, check that it
    # still matches once converted. If it doesn't match as it is, print a warning.
    macro_val = round((hours * 3600 + minutes * 60 + seconds) * (0x10000 / (24 * 60 * 60)))

    print(f"{hours},{minutes:02},{seconds:02} -> 0x{macro_val:04X}")
    print(f"CLOCK_TIME({hours}, {minutes})")
    assert time == macro_val, "Warning: Result does not match as-is"

if __name__ == "__main__":
    time = sys.argv[1]
    time = int(time, 16 if time.startswith("0x") else 10)
    convert(time)
