.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgLbfshotOverlayInfo
/* 000060 0x80C18210 */ .word	0x000000C0
/* 000061 0x80C18214 */ .word	0x00000030
/* 000062 0x80C18218 */ .word	0x00000000
/* 000063 0x80C1821C */ .word	0x00000000
/* 000064 0x80C18220 */ .word	0x00000005
glabel bgLbfshotOverlayRelocations
/* 000065 0x80C18224 */ .word	0x45000010
/* 000066 0x80C18228 */ .word	0x46000014
/* 000067 0x80C1822C */ .word	0x82000010
/* 000068 0x80C18230 */ .word	0x82000014
/* 000069 0x80C18234 */ .word	0x8200001C
/* 000070 0x80C18238 */ .word	0x00000000
glabel bgLbfshotOverlayInfoOffset
/* 000071 0x80C1823C */ .word	0x00000030
