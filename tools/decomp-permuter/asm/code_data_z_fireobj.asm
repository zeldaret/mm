.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel fireObjCollisionInit
/* 286596 0x801BD8D0 */ .word	0x0A000900
/* 286597 0x801BD8D4 */ .word	0x00010000
/* 286598 0x801BD8D8 */ .word	0x04000000
/* 286599 0x801BD8DC */ .word	0x00000000
/* 286600 0x801BD8E0 */ .word	0x00000000
/* 286601 0x801BD8E4 */ .word	0x00000820
/* 286602 0x801BD8E8 */ .word	0x00000000
/* 286603 0x801BD8EC */ .word	0x00010000
/* 286604 0x801BD8F0 */ .word	0x00120043
/* 286605 0x801BD8F4 */ .word	0x00000000
/* 286606 0x801BD8F8 */ .word	0x00000000
glabel D_801BD8FC
/* 286607 0x801BD8FC */ .word	0xFFFF00FF
/* 286608 0x801BD900 */ .word	0x80FF0000
/* 286609 0x801BD904 */ .word	0x00C88080
/* 286610 0x801BD908 */ .word	0x007F7F00
/* 286611 0x801BD90C */ .word	0x00000000
