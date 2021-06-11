#!/usr/bin/env bash
for A in tests/*.c; do
    ./compile.sh "$A" && mips-linux-gnu-objdump -s "${A%.c}.o" | diff - "${A%.c}.objdump" || echo FAIL "$A"
done
