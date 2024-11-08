# libu64

This document explains the reasoning behind organizing the libu64 files.

See Ocarina of Time's document on libu64: https://github.com/zeldaret/oot/blob/main/docs/libu64.md (note: the MM repo is itself referenced by that document)

The same libu64 files from OoT exist in MM.

Additionally MM has `loadfragment.c`, a (unused) near-copy of the libu64 file `loadfragment2.c`, and `loadfragment.c` is in the middle of libu64 files and requires `-O2`. So that file is also taken as part of libu64.
