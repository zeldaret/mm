.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E01E0
/* 321992 0x801E01E0 */ .word	0x38C90FDB
/* 321993 0x801E01E4 */ .word	0x00000000
/* 321994 0x801E01E8 */ .word	0x00000000
/* 321995 0x801E01EC */ .word	0x00000000
