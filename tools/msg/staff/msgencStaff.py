#!/usr/bin/env python3
#
#   message_data_static text encoder
#

import argparse, ast, re
import sys

CHARMAP = {
    '\n' : 0x1,
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

def main(infile, outfile):
    charmap = convert_charmap()

    text = ""
    with open(infile, "r") as f:
        text = f.read()

    text = remove_comments(text)
    text = convert_text(text, charmap)

    if outfile is None:
        sys.stdout.reconfigure(encoding="raw_unicode_escape")
        sys.stdout.write(text)
    else:
        with open(outfile, "w", encoding="raw_unicode_escape") as f:
            f.write(text)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Encode staff_message_data_static text headers")
    parser.add_argument("infile", help="path to file to be encoded")
    parser.add_argument("-o", "--outfile", help="encoded file. None for stdout")
    args = parser.parse_args()

    main(args.infile, args.outfile)
