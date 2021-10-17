.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD780
/* 319280 0x801DD780 */ .word	0x3F333333
/* 319281 0x801DD784 */ .word	0x00000000
/* 319282 0x801DD788 */ .word	0x00000000
/* 319283 0x801DD78C */ .word	0x00000000
