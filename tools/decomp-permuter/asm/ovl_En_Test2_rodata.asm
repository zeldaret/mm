.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTest2OverlayInfo
/* 000252 0x80A3E780 */ .word	0x00000300
/* 000253 0x80A3E784 */ .word	0x000000F0
/* 000254 0x80A3E788 */ .word	0x00000000
/* 000255 0x80A3E78C */ .word	0x00000000
/* 000256 0x80A3E790 */ .word	0x00000012
glabel enTest2OverlayRelocations
/* 000257 0x80A3E794 */ .word	0x4500000C
/* 000258 0x80A3E798 */ .word	0x46000010
/* 000259 0x80A3E79C */ .word	0x45000078
/* 000260 0x80A3E7A0 */ .word	0x46000090
/* 000261 0x80A3E7A4 */ .word	0x450000C4
/* 000262 0x80A3E7A8 */ .word	0x460000D8
/* 000263 0x80A3E7AC */ .word	0x450000C8
/* 000264 0x80A3E7B0 */ .word	0x460000DC
/* 000265 0x80A3E7B4 */ .word	0x45000120
/* 000266 0x80A3E7B8 */ .word	0x46000130
/* 000267 0x80A3E7BC */ .word	0x450001B0
/* 000268 0x80A3E7C0 */ .word	0x460001C8
/* 000269 0x80A3E7C4 */ .word	0x45000278
/* 000270 0x80A3E7C8 */ .word	0x4600029C
/* 000271 0x80A3E7CC */ .word	0x450002C0
/* 000272 0x80A3E7D0 */ .word	0x460002DC
/* 000273 0x80A3E7D4 */ .word	0x82000010
/* 000274 0x80A3E7D8 */ .word	0x82000018
glabel enTest2OverlayInfoOffset
/* 000275 0x80A3E7DC */ .word	0x00000060
