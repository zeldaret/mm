.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objTokeiTurretOverlayInfo
/* 000136 0x80B91EE0 */ .word	0x000001E0
/* 000137 0x80B91EE4 */ .word	0x00000030
/* 000138 0x80B91EE8 */ .word	0x00000010
/* 000139 0x80B91EEC */ .word	0x00000000
/* 000140 0x80B91EF0 */ .word	0x00000008
glabel objTokeiTurretOverlayRelocations
/* 000141 0x80B91EF4 */ .word	0x45000014
/* 000142 0x80B91EF8 */ .word	0x46000018
/* 000143 0x80B91EFC */ .word	0x450000A0
/* 000144 0x80B91F00 */ .word	0x460000A4
/* 000145 0x80B91F04 */ .word	0x82000010
/* 000146 0x80B91F08 */ .word	0x82000014
/* 000147 0x80B91F0C */ .word	0x82000018
/* 000148 0x80B91F10 */ .word	0x8200001C
/* 000149 0x80B91F14 */ .word	0x00000000
/* 000150 0x80B91F18 */ .word	0x00000000
glabel objTokeiTurretOverlayInfoOffset
/* 000151 0x80B91F1C */ .word	0x00000040
