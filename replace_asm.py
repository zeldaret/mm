#!/usr/bin/env python3

from pathlib import Path

replacements = Path("asm_replacements.txt").read_text().splitlines()

i = 0
while i < len(replacements):
    while not replacements[i] or replacements[i].startswith("#") or replacements[i].startswith("//"):
        i += 1
        if i >= len(replacements):
            break

    if i >= len(replacements):
        break
    file = replacements[i]
    i += 1

    file_path = Path(f"./{file}")
    fd = file_path.read_text()

    line = replacements[i]
    while line and line.startswith(" "):
        replace_line, replace_text = line.split(":")
        replace_text = replace_text.strip()
        replace_line = replace_line.strip()

        line_pos = fd.find(f"\n/* {replace_line}")
        if line_pos >= 0:
            line_pos = fd.find("*/", line_pos) + 4
            
            fd = fd[:line_pos] + replace_text + fd[fd.find("\n", line_pos):] 
        
        i += 1
        if i >= len(replacements):
            break
        line = replacements[i]

    file_path.write_text(fd)
