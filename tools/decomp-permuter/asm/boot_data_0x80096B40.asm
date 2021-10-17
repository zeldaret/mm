.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel gCartHandle
/* 023224 0x80096B40 */ .word	0x00000000
/* 023225 0x80096B44 */ .word	0x00000000
/* 023226 0x80096B48 */ .word	0x00000000
/* 023227 0x80096B4C */ .word	0x00000000
