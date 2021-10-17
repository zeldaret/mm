.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enOkarinaEffectOverlayInfo
/* 000136 0x8096B2C0 */ .word	0x000001F0
/* 000137 0x8096B2C4 */ .word	0x00000020
/* 000138 0x8096B2C8 */ .word	0x00000010
/* 000139 0x8096B2CC */ .word	0x00000000
/* 000140 0x8096B2D0 */ .word	0x0000000E
glabel enOkarinaEffectOverlayRelocations
/* 000141 0x8096B2D4 */ .word	0x45000044
/* 000142 0x8096B2D8 */ .word	0x46000048
/* 000143 0x8096B2DC */ .word	0x4400004C
/* 000144 0x8096B2E0 */ .word	0x4500008C
/* 000145 0x8096B2E4 */ .word	0x46000090
/* 000146 0x8096B2E8 */ .word	0x450000B4
/* 000147 0x8096B2EC */ .word	0x460000B8
/* 000148 0x8096B2F0 */ .word	0x440000BC
/* 000149 0x8096B2F4 */ .word	0x45000138
/* 000150 0x8096B2F8 */ .word	0x46000148
/* 000151 0x8096B2FC */ .word	0x44000144
/* 000152 0x8096B300 */ .word	0x82000010
/* 000153 0x8096B304 */ .word	0x82000014
/* 000154 0x8096B308 */ .word	0x82000018
glabel enOkarinaEffectOverlayInfoOffset
/* 000155 0x8096B30C */ .word	0x00000050
