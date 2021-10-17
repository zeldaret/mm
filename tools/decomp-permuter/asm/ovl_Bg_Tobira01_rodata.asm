.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgTobira01OverlayInfo
/* 000256 0x80B12830 */ .word	0x000003D0
/* 000257 0x80B12834 */ .word	0x00000020
/* 000258 0x80B12838 */ .word	0x00000010
/* 000259 0x80B1283C */ .word	0x00000000
/* 000260 0x80B12840 */ .word	0x00000008
glabel bgTobira01OverlayRelocations
/* 000261 0x80B12844 */ .word	0x450001C0
/* 000262 0x80B12848 */ .word	0x460001C4
/* 000263 0x80B1284C */ .word	0x450002B8
/* 000264 0x80B12850 */ .word	0x460002BC
/* 000265 0x80B12854 */ .word	0x82000010
/* 000266 0x80B12858 */ .word	0x82000014
/* 000267 0x80B1285C */ .word	0x82000018
/* 000268 0x80B12860 */ .word	0x8200001C
/* 000269 0x80B12864 */ .word	0x00000000
/* 000270 0x80B12868 */ .word	0x00000000
glabel bgTobira01OverlayInfoOffset
/* 000271 0x80B1286C */ .word	0x00000040
