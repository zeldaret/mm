.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgHakaCurtainOverlayInfo
/* 000244 0x80B6DFB0 */ .word	0x000003A0
/* 000245 0x80B6DFB4 */ .word	0x00000030
/* 000246 0x80B6DFB8 */ .word	0x00000000
/* 000247 0x80B6DFBC */ .word	0x00000000
/* 000248 0x80B6DFC0 */ .word	0x00000016
glabel bgHakaCurtainOverlayRelocations
/* 000249 0x80B6DFC4 */ .word	0x45000014
/* 000250 0x80B6DFC8 */ .word	0x46000018
/* 000251 0x80B6DFCC */ .word	0x44000058
/* 000252 0x80B6DFD0 */ .word	0x44000068
/* 000253 0x80B6DFD4 */ .word	0x450000B8
/* 000254 0x80B6DFD8 */ .word	0x460000BC
/* 000255 0x80B6DFDC */ .word	0x440000F4
/* 000256 0x80B6DFE0 */ .word	0x4500010C
/* 000257 0x80B6DFE4 */ .word	0x46000110
/* 000258 0x80B6DFE8 */ .word	0x44000154
/* 000259 0x80B6DFEC */ .word	0x4500017C
/* 000260 0x80B6DFF0 */ .word	0x46000180
/* 000261 0x80B6DFF4 */ .word	0x450001A4
/* 000262 0x80B6DFF8 */ .word	0x460001A8
/* 000263 0x80B6DFFC */ .word	0x44000278
/* 000264 0x80B6E000 */ .word	0x450002AC
/* 000265 0x80B6E004 */ .word	0x460002B0
/* 000266 0x80B6E008 */ .word	0x44000334
/* 000267 0x80B6E00C */ .word	0x82000010
/* 000268 0x80B6E010 */ .word	0x82000014
/* 000269 0x80B6E014 */ .word	0x82000018
/* 000270 0x80B6E018 */ .word	0x8200001C
glabel bgHakaCurtainOverlayInfoOffset
/* 000271 0x80B6E01C */ .word	0x00000070
