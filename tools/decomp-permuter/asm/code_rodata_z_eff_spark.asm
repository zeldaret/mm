.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DC0C0
/* 317824 0x801DC0C0 */ .word	0x3C03126F
glabel D_801DC0C4
/* 317825 0x801DC0C4 */ .word	0x477FFE00
glabel D_801DC0C8
/* 317826 0x801DC0C8 */ .word	0x466A6000
glabel D_801DC0CC
/* 317827 0x801DC0CC */ .word	0x46EA6000
