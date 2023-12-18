#!/usr/bin/env python3
#
#   message_data_static text encoder
#

import argparse, ast, re
import sys

CHARMAP = {
    '\n' : 0x11,

    '[B0]' : 0xB0,
    '[B1]' : 0xB1,
    '[B2]' : 0xB2,
    '[B3]' : 0xB3,
    '[B4]' : 0xB4,
    '[B5]' : 0xB5,
    '[B6]' : 0xB6,
    '[B7]' : 0xB7,
    '[B8]' : 0xB8,
    '[B9]' : 0xB9,
    '[BA]' : 0xBA,
    '[BB]' : 0xBB,
}

def convert_charmap():
    charmap = { repr(k)[1:-1] : chr(v) for k,v in CHARMAP.items() }

    return charmap

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

def convert_text(text, charmap):
    def cvt_str(m):
        string = m.group(0)

        for orig,char in charmap.items():
            string = string.replace(orig, char)

        return string

    # Naive string matcher, assumes single line strings and no comments, handles escaped quotations
    string_regex = re.compile(r'"((?:[^\\"\n]|\\.)*)"')

    # Collapse escaped newlines
    text = text.replace("\\\n", "")
    # Encode according to charmap
    text = re.sub(string_regex, cvt_str, text)

    return text

def main():
    parser = argparse.ArgumentParser(description="Encode message_data_static text headers")
    parser.add_argument("input", help="path to file to be encoded")
    parser.add_argument("output", help="encoded file")
    args = parser.parse_args()

    charmap = convert_charmap()

    text = ""
    with open(args.input, "r") as infile:
        text = infile.read()

    text = remove_comments(text)
    text = convert_text(text, charmap)

    with open(args.output, "w", encoding="raw_unicode_escape") as outfile:
        outfile.write(text)

if __name__ == "__main__":
    main()
