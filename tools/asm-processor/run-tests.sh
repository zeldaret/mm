#!/usr/bin/env bash
for A in tests/*.c; do
    OBJDUMPFLAGS=$(grep '^// OBJDUMP-FLAGS: ' "$A" | sed 's#^// OBJDUMP-FLAGS: ##')
    if [[ -z "$OBJDUMPFLAGS" ]]; then
        OBJDUMPFLAGS="-s"
    fi
    ./compile.sh "$A" && mips-linux-gnu-objdump $OBJDUMPFLAGS "${A%.c}.o" | diff - "${A%.c}.objdump" || echo FAIL "$A"
done
