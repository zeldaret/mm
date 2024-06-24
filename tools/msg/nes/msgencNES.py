#!/usr/bin/env python3
#
#   message_data_static text encoder
#

import argparse
import re
import sys

CHAR_REGEX = r'(?P<chr>\\n|\[.*?\])'

# From https://stackoverflow.com/questions/241327/remove-c-and-c-comments-using-python
def remove_comments(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s

    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def parse_char(m):
    CHARMAP = {
        '\\n' : 0x11,

        '[A]' : 0xB0,
        '[B]' : 0xB1,
        '[C]' : 0xB2,
        '[L]' : 0xB3,
        '[R]' : 0xB4,
        '[Z]' : 0xB5,
        '[C-Up]' : 0xB6,
        '[C-Down]' : 0xB7,
        '[C-Left]' : 0xB8,
        '[C-Right]' : 0xB9,
        '▼' : 0xBA,
        '[Control-Pad]' : 0xBB,
    }
    return f'{chr(CHARMAP[m.group(0)])}'

def cvt_str(m):
    if m.group('chr'):
        return parse_char(m)
    else:
        print(f"Error Unknown match {m}", file=sys.stderr)
        return m.group(0) # Just return the string back

def encode(text):
    string_regex = re.compile(f'{CHAR_REGEX}')

    # Collapse escaped newlines
    text = text.replace("\\\n", "")

    # Encode
    text = re.sub(string_regex, cvt_str, text)

    return text

def main(infile, outfile):
    text = ""
    with open(infile, "r") as f:
        text = f.read()

    text = remove_comments(text)
    text = encode(text)

    if outfile is None:
        sys.stdout.reconfigure(encoding='raw_unicode_escape')
        sys.stdout.write(text)
    else:
        with open(outfile, "w", encoding="raw_unicode_escape") as f:
            f.write(text)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Encode message_data_static text headers")
    parser.add_argument("infile", help="path to file to be encoded")
    parser.add_argument("-o", "--outfile", help="encoded file. None for stdout")
    args = parser.parse_args()

    main(args.infile, args.outfile)
