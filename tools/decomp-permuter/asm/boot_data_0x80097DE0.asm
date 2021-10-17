.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097DE0
/* 024416 0x80097DE0 */ .word	0x00000000
glabel D_80097DE4
/* 024417 0x80097DE4 */ .word	0x00000000
/* 024418 0x80097DE8 */ .word	0x00000000
/* 024419 0x80097DEC */ .word	0x00000000
/* 024420 0x80097DF0 */ .word	0x00000000
/* 024421 0x80097DF4 */ .word	0x00000000
/* 024422 0x80097DF8 */ .word	0x00000000
/* 024423 0x80097DFC */ .word	0x00000000
/* 024424 0x80097E00 */ .word	0x00000000
/* 024425 0x80097E04 */ .word	0x00000000
glabel D_80097E08
/* 024426 0x80097E08 */ .word	0x00000000
/* 024427 0x80097E0C */ .word	0x00000000
