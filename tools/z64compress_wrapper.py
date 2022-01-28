#!/usr/bin/env python3
#
#   z64compress wrapper for decomp projects
#     https://github.com/z64me/z64compress
#   Arguments: <rom in> <rom out> <elf> <spec> [--cache [cache directory]] [--threads [num threads]] [--mb [target rom size]] [--matching]
#   Example Makefile usage:
#     python3 tools/z64compress_wrapper.py --matching --threads $(shell nproc) $< $@ $(ELF) build/$(SPEC)
#

import argparse, itertools, subprocess, sys

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

# Args from command line
parser = argparse.ArgumentParser(description="Compress rom produced by the OoT and MM Decomp projects")

parser.add_argument("in_rom", help="uncompressed input rom filename")
parser.add_argument("out_rom", help="compressed output rom filename")
parser.add_argument("elf", help="path to the uncompressed rom elf file")
parser.add_argument("spec", help="path to processed spec file")
parser.add_argument("--cache", help="cache directory")
parser.add_argument("--threads", help="number of threads to run compression on, 0 disables multithreading")
parser.add_argument("--mb", help="compressed rom size in MB, default is the smallest multiple of 8mb fitting the whole rom")
parser.add_argument("--matching", help="matching compression, forfeits some useful optimizations", action="store_true")
parser.add_argument("--stderr", help="z64compress will write its output messages to stderr instead of stdout", action="store_true")

args = parser.parse_args()

IN_ROM = args.in_rom
OUT_ROM = args.out_rom

elf_path = args.elf

CACHE_DIR = args.cache
N_THREADS = int(args.threads or 0)
MB = args.mb
MATCHING = args.matching
STDOUT = not args.stderr

# Get segments to compress

spec = ""
with open(args.spec, "r") as infile:
    spec = infile.read()

def ranges(i):
    for _, b in itertools.groupby(enumerate(i), lambda pair: pair[1] - pair[0]):
        b = list(b)
        yield b[0][1], b[-1][1]

compress_segments = []

shift = 0
for i,segment in enumerate(spec.split("beginseg\n")[1:],0):
    directives = segment.split("endseg")[0].split("\n")

    for directive in directives:
        directive = directive.strip()
        if directive.startswith("flags") and "NOLOAD" in directive:
            shift += 1
        elif directive.startswith("compress"):
            compress_segments.append(i - shift)

compress_segments = list(ranges(compress_segments))
COMPRESS_INDICES = ",".join([f"{start}-{end}" if start != end else f"{start}" for start,end in compress_segments])

# Find dmadata

def get_dmadata_start_len():
    dmadata_start = -1
    dmadata_end = -1

    with open(elf_path, "rb") as elf_file:
        elf = ELFFile(elf_file)

        for section in elf.iter_sections():
            if not isinstance(section, SymbolTableSection):
                continue

            for sym in section.iter_symbols():
                if sym.name == "_dmadataSegmentRomStart":
                    dmadata_start = sym['st_value']
                elif sym.name == "_dmadataSegmentRomEnd":
                    dmadata_end = sym['st_value']
                if dmadata_start != -1 and dmadata_end != -1:
                    break

        assert dmadata_start != -1, "_dmadataSegmentRomStart symbol not found in supplied ELF"
        assert dmadata_end != -1, "_dmadataSegmentRomEnd symbol not found in supplied ELF"

    return dmadata_start, (dmadata_end - dmadata_start)//0x10

DMADATA_ADDR, DMADATA_COUNT = get_dmadata_start_len()

# Run

cmd = f"./tools/z64compress/z64compress \
--in {IN_ROM} \
--out {OUT_ROM}\
{' --matching' if MATCHING else ''}\
{f' --mb {MB}' if MB is not None else ''} \
--codec yaz\
{f' --cache {CACHE_DIR}' if CACHE_DIR is not None else ''} \
--dma 0x{DMADATA_ADDR:X},{DMADATA_COUNT} \
--compress {COMPRESS_INDICES}\
{f' --threads {N_THREADS}' if N_THREADS > 0 else ''}\
{f' --only-stdout' if STDOUT else ''}"

print(cmd)
try:
    subprocess.check_call(cmd, shell=True)
except subprocess.CalledProcessError as e:
    # Return the same error code for the wrapper if z64compress fails
    sys.exit(e.returncode)
