.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097D7F0
/* 000248 0x8097D7F0 */ .word	0x00000017
/* 000249 0x8097D7F4 */ .word	func_8097D410
/* 000250 0x8097D7F8 */ .word	0x00000000
/* 000251 0x8097D7FC */ .word	0x00000000
glabel D_8097D800
/* 000252 0x8097D800 */ .word	0x461C4000
glabel D_8097D804
/* 000253 0x8097D804 */ .word	0x40490FDB
/* 000254 0x8097D808 */ .word	0x00000000
/* 000255 0x8097D80C */ .word	0x00000000
glabel effectSsKFireOverlayInfo
/* 000256 0x8097D810 */ .word	0x000003E0
/* 000257 0x8097D814 */ .word	0x00000010
/* 000258 0x8097D818 */ .word	0x00000010
/* 000259 0x8097D81C */ .word	0x00000000
/* 000260 0x8097D820 */ .word	0x00000009
glabel effectSsKFireOverlayRelocations
/* 000261 0x8097D824 */ .word	0x45000098
/* 000262 0x8097D828 */ .word	0x460000A0
/* 000263 0x8097D82C */ .word	0x4500009C
/* 000264 0x8097D830 */ .word	0x460000A8
/* 000265 0x8097D834 */ .word	0x450000E0
/* 000266 0x8097D838 */ .word	0x460000E4
/* 000267 0x8097D83C */ .word	0x450002C4
/* 000268 0x8097D840 */ .word	0x460002DC
/* 000269 0x8097D844 */ .word	0x82000004
/* 000270 0x8097D848 */ .word	0x00000000
glabel effectSsKFireOverlayInfoOffset
/* 000271 0x8097D84C */ .word	0x00000040
