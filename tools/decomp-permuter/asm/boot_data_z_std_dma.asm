.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel sDmaMgrDmaBuffSize
/* 023228 0x80096B50 */ .word	0x00002000
/* 023229 0x80096B54 */ .word	0x00000000
/* 023230 0x80096B58 */ .word	0x00000000
/* 023231 0x80096B5C */ .word	0x00000000
