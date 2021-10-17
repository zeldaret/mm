.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DFCC0
/* 321664 0x801DFCC0 */ .word	0x2E2E2F67
/* 321665 0x801DFCC4 */ .word	0x616D652E
/* 321666 0x801DFCC8 */ .word	0x63000000
glabel D_801DFCCC
/* 321667 0x801DFCCC */ .word	0x2E2E2F67
/* 321668 0x801DFCD0 */ .word	0x616D652E
/* 321669 0x801DFCD4 */ .word	0x63000000
/* 321670 0x801DFCD8 */ .word	0x00000000
/* 321671 0x801DFCDC */ .word	0x00000000
