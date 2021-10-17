.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DC0B0
/* 317820 0x801DC0B0 */ .word	0x477FFE00
glabel D_801DC0B4
/* 317821 0x801DC0B4 */ .word	0x3CA3D70A
/* 317822 0x801DC0B8 */ .word	0x00000000
/* 317823 0x801DC0BC */ .word	0x00000000
