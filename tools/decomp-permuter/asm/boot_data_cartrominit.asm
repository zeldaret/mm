.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_800980D0
/* 024604 0x800980D0 */ .word	0x00000001
/* 024605 0x800980D4 */ .word	0x00000000
/* 024606 0x800980D8 */ .word	0x00000000
/* 024607 0x800980DC */ .word	0x00000000
