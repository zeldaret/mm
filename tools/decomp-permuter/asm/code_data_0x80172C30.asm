.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D14F0
/* 306828 0x801D14F0 */ .word	0x0000000A
/* 306829 0x801D14F4 */ .word	0x00000000
/* 306830 0x801D14F8 */ .word	0x00000000
/* 306831 0x801D14FC */ .word	0x00000000
