.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel randSeed
/* 023860 0x80097530 */ .word	0x00000001
/* 023861 0x80097534 */ .word	0x00000000
/* 023862 0x80097538 */ .word	0x00000000
/* 023863 0x8009753C */ .word	0x00000000
