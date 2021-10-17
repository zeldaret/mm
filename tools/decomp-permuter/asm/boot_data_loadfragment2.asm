.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80096C30
/* 023284 0x80096C30 */ .word	0x00000002
/* 023285 0x80096C34 */ .word	0x00000000
/* 023286 0x80096C38 */ .word	0x00000000
/* 023287 0x80096C3C */ .word	0x00000000
