.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800990B0
/* 025620 0x800990B0 */ .word	0x52657365
/* 025621 0x800990B4 */ .word	0x74000000
/* 025622 0x800990B8 */ .word	0x00000000
/* 025623 0x800990BC */ .word	0x00000000
