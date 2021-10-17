.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DC0D0
/* 317828 0x801DC0D0 */ .word	0x453B8000
glabel D_801DC0D4
/* 317829 0x801DC0D4 */ .word	0x453B8000
/* 317830 0x801DC0D8 */ .word	0x00000000
/* 317831 0x801DC0DC */ .word	0x00000000
