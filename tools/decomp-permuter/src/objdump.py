#!/usr/bin/env python3
from dataclasses import dataclass, field
import os
import re
import string
import subprocess
import sys
from typing import List, Match, Pattern, Set, Tuple

# Ignore registers, for cleaner output. (We don't do this right now, but it can
# be useful for debugging.)
ign_regs = False

# Don't include branch targets in the output. Assuming our input is semantically
# equivalent skipping it shouldn't be an issue, and it makes insertions have too
# large effect.
ign_branch_targets = True

# Skip branch-likely delay slots. (They aren't interesting on IDO.)
skip_bl_delay_slots = True

skip_lines = 1
re_int = re.compile(r"[0-9]+")
re_int_full = re.compile(r"\b[0-9]+\b")


@dataclass
class ArchSettings:
    objdump: List[str]
    re_comment: Pattern[str]
    re_reg: Pattern[str]
    re_sprel: Pattern[str]
    re_includes_sp: Pattern[str]
    branch_instructions: Set[str]
    forbidden: Set[str] = field(default_factory=lambda: set(string.ascii_letters + "_"))
    branch_likely_instructions: Set[str] = field(default_factory=set)


MIPS_BRANCH_LIKELY_INSTRUCTIONS = {
    "beql",
    "bnel",
    "beqzl",
    "bnezl",
    "bgezl",
    "bgtzl",
    "blezl",
    "bltzl",
    "bc1tl",
    "bc1fl",
}
MIPS_BRANCH_INSTRUCTIONS = {
    "b",
    "j",
    "beq",
    "bne",
    "beqz",
    "bnez",
    "bgez",
    "bgtz",
    "blez",
    "bltz",
    "bc1t",
    "bc1f",
}.union(MIPS_BRANCH_LIKELY_INSTRUCTIONS)

MIPS_SETTINGS: ArchSettings = ArchSettings(
    re_comment=re.compile(r"<.*?>"),
    re_reg=re.compile(
        r"\$?\b(a[0-3]|t[0-9]|s[0-8]|at|v[01]|f[12]?[0-9]|f3[01]|k[01]|fp|ra)\b"  # leave out $zero
    ),
    re_sprel=re.compile(r"(?<=,)([0-9]+|0x[0-9a-f]+)\((sp|s8)\)"),
    re_includes_sp=re.compile(r"\b(sp|s8)\b"),
    objdump=["mips-linux-gnu-objdump", "-drz", "-m", "mips:4300"],
    branch_likely_instructions=MIPS_BRANCH_LIKELY_INSTRUCTIONS,
    branch_instructions=MIPS_BRANCH_INSTRUCTIONS,
)


def get_arch(o_file: str) -> ArchSettings:
    # https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html
    with open(o_file, "rb") as f:
        f.seek(18)
        arch_magic = f.read(2)
    if arch_magic == b"\0\x08":
        return MIPS_SETTINGS
    # TODO: support PPC ("\0\x14"), ARM ("0\x28")
    raise Exception("Bad ELF")


def parse_relocated_line(line: str) -> Tuple[str, str, str]:
    try:
        ind2 = line.rindex(",")
    except ValueError:
        ind2 = line.rindex("\t")
    before = line[: ind2 + 1]
    after = line[ind2 + 1 :]
    ind2 = after.find("(")
    if ind2 == -1:
        imm, after = after, ""
    else:
        imm, after = after[:ind2], after[ind2:]
    if imm == "0x0":
        imm = "0"
    return before, imm, after


def simplify_objdump(
    input_lines: List[str], arch: ArchSettings, *, stack_differences: bool
) -> List[str]:
    output_lines: List[str] = []
    nops = 0
    skip_next = False
    for index, row in enumerate(input_lines):
        if index < skip_lines:
            continue
        row = row.rstrip()
        if ">:" in row or not row:
            continue
        if "R_MIPS_" in row:
            prev = output_lines[-1]
            if prev == "<skipped>":
                continue
            before, imm, after = parse_relocated_line(prev)
            repl = row.split()[-1]
            # As part of ignoring branch targets, we ignore relocations for j
            # instructions. The target is already lost anyway.
            if imm == "<target>":
                assert ign_branch_targets
                continue
            # Sometimes s8 is used as a non-framepointer, but we've already lost
            # the immediate value by pretending it is one. This isn't too bad,
            # since it's rare and applies consistently. But we do need to handle it
            # here to avoid a crash, by pretending that lost imms are zero for
            # relocations.
            if imm != "0" and imm != "imm" and imm != "addr":
                repl += "+" + imm if int(imm, 0) > 0 else imm
            if any(
                reloc in row
                for reloc in ["R_MIPS_LO16", "R_MIPS_LITERAL", "R_MIPS_GPREL16"]
            ):
                repl = f"%lo({repl})"
            elif "R_MIPS_HI16" in row:
                # Ideally we'd pair up R_MIPS_LO16 and R_MIPS_HI16 to generate a
                # correct addend for each, but objdump doesn't give us the order of
                # the relocations, so we can't find the right LO16. :(
                repl = f"%hi({repl})"
            else:
                assert "R_MIPS_26" in row, f"unknown relocation type '{row}'"
            output_lines[-1] = before + repl + after
            continue
        row = re.sub(arch.re_comment, "", row)
        row = row.rstrip()
        row = "\t".join(row.split("\t")[2:])  # [20:]
        if not row:
            continue
        if skip_next:
            skip_next = False
            row = "<skipped>"
        if ign_regs:
            row = re.sub(arch.re_reg, "<reg>", row)
        row_parts = row.split("\t")
        if len(row_parts) == 1:
            row_parts.append("")
        mnemonic, instr_args = row_parts
        if not stack_differences:
            if mnemonic == "addiu" and arch.re_includes_sp.search(instr_args):
                row = re.sub(re_int_full, "imm", row)
        if mnemonic in arch.branch_instructions:
            if ign_branch_targets:
                instr_parts = instr_args.split(",")
                instr_parts[-1] = "<target>"
                instr_args = ",".join(instr_parts)
                row = f"{mnemonic}\t{instr_args}"
            # The last part is in hex, so skip the dec->hex conversion
        else:

            def fn(pat: Match[str]) -> str:
                full = pat.group(0)
                if len(full) <= 1:
                    return full
                start, end = pat.span()
                if start and row[start - 1] in arch.forbidden:
                    return full
                if end < len(row) and row[end] in arch.forbidden:
                    return full
                return hex(int(full))

            row = re.sub(re_int, fn, row)
        if mnemonic in arch.branch_likely_instructions and skip_bl_delay_slots:
            skip_next = True
        if not stack_differences:
            row = re.sub(arch.re_sprel, "addr(sp)", row)
        # row = row.replace(',', ', ')
        if row == "nop":
            # strip trailing nops; padding is irrelevant to us
            nops += 1
        else:
            for _ in range(nops):
                output_lines.append("nop")
            nops = 0
            output_lines.append(row)
    return output_lines


def objdump(
    o_filename: str, arch: ArchSettings, *, stack_differences: bool = False
) -> List[str]:
    output = subprocess.check_output(arch.objdump + [o_filename])
    lines = output.decode("utf-8").splitlines()
    return simplify_objdump(lines, arch, stack_differences=stack_differences)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} file.o", file=sys.stderr)
        sys.exit(1)

    if not os.path.isfile(sys.argv[1]):
        print(f"Source file {sys.argv[1]} is not readable.", file=sys.stderr)
        sys.exit(1)

    lines = objdump(sys.argv[1], MIPS_SETTINGS)
    for row in lines:
        print(row)
