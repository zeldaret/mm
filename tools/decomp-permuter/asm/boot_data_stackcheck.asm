.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel sStackInfoListStart
/* 023288 0x80096C40 */ .word	0x00000000
glabel sStackInfoListEnd
/* 023289 0x80096C44 */ .word	0x00000000
/* 023290 0x80096C48 */ .word	0x00000000
/* 023291 0x80096C4C */ .word	0x00000000
