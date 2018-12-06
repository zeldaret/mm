#!/bin/bash

MIPS_BINUTILS="mips-linux-gnu-"

OBJDUMP="${MIPS_BINUTILS}objdump -D -z -mmips -EB -j .text -j .data -j .rodata"

FORMATTER="sed '/^0/!s/.*://'"

$OBJDUMP build/src/test.o | sed '1,6d; /^0/!s/.*://' > test.dump
$OBJDUMP $1 | sed '1,6d; /^0/!s/.*://' > comp.dump
diff -y test.dump comp.dump > diff.dump
rm test.dump comp.dump