.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enZl4OverlayInfo
/* 000260 0x809A1FC0 */ .word	0x000003B0
/* 000261 0x809A1FC4 */ .word	0x00000050
/* 000262 0x809A1FC8 */ .word	0x00000010
/* 000263 0x809A1FCC */ .word	0x00000000
/* 000264 0x809A1FD0 */ .word	0x00000015
glabel enZl4OverlayRelocations
/* 000265 0x809A1FD4 */ .word	0x450000BC
/* 000266 0x809A1FD8 */ .word	0x460000C0
/* 000267 0x809A1FDC */ .word	0x45000108
/* 000268 0x809A1FE0 */ .word	0x4600010C
/* 000269 0x809A1FE4 */ .word	0x44000114
/* 000270 0x809A1FE8 */ .word	0x4500012C
/* 000271 0x809A1FEC */ .word	0x46000130
/* 000272 0x809A1FF0 */ .word	0x450001C4
/* 000273 0x809A1FF4 */ .word	0x460001C8
/* 000274 0x809A1FF8 */ .word	0x4400030C
/* 000275 0x809A1FFC */ .word	0x44000348
/* 000276 0x809A2000 */ .word	0x45000364
/* 000277 0x809A2004 */ .word	0x46000378
/* 000278 0x809A2008 */ .word	0x45000368
/* 000279 0x809A200C */ .word	0x46000374
/* 000280 0x809A2010 */ .word	0x4500036C
/* 000281 0x809A2014 */ .word	0x46000370
/* 000282 0x809A2018 */ .word	0x82000010
/* 000283 0x809A201C */ .word	0x82000014
/* 000284 0x809A2020 */ .word	0x82000018
/* 000285 0x809A2024 */ .word	0x8200001C
/* 000286 0x809A2028 */ .word	0x00000000
glabel enZl4OverlayInfoOffset
/* 000287 0x809A202C */ .word	0x00000070
