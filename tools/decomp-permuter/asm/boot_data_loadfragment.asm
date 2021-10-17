.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80096C20
/* 023280 0x80096C20 */ .word	0x00000002
/* 023281 0x80096C24 */ .word	0x00000000
/* 023282 0x80096C28 */ .word	0x00000000
/* 023283 0x80096C2C */ .word	0x00000000
