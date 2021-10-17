.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel __osSiAccessQueueEnabled
/* 024436 0x80097E30 */ .word	0x00000000
/* 024437 0x80097E34 */ .word	0x00000000
/* 024438 0x80097E38 */ .word	0x00000000
/* 024439 0x80097E3C */ .word	0x00000000
