.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E01F0
/* 321996 0x801E01F0 */ .word	0x4622F983
glabel D_801E01F4
/* 321997 0x801E01F4 */ .word	0x38000100
glabel D_801E01F8
/* 321998 0x801E01F8 */ .word	0x38000100
/* 321999 0x801E01FC */ .word	0x00000000
