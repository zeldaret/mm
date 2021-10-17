.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objLightblockOverlayInfo
/* 000380 0x80AF3F00 */ .word	0x00000570
/* 000381 0x80AF3F04 */ .word	0x00000080
/* 000382 0x80AF3F08 */ .word	0x00000000
/* 000383 0x80AF3F0C */ .word	0x00000000
/* 000384 0x80AF3F10 */ .word	0x00000016
glabel objLightblockOverlayRelocations
/* 000385 0x80AF3F14 */ .word	0x45000010
/* 000386 0x80AF3F18 */ .word	0x46000014
/* 000387 0x80AF3F1C */ .word	0x45000088
/* 000388 0x80AF3F20 */ .word	0x4600008C
/* 000389 0x80AF3F24 */ .word	0x45000098
/* 000390 0x80AF3F28 */ .word	0x460000A0
/* 000391 0x80AF3F2C */ .word	0x45000110
/* 000392 0x80AF3F30 */ .word	0x46000114
/* 000393 0x80AF3F34 */ .word	0x44000154
/* 000394 0x80AF3F38 */ .word	0x450001B8
/* 000395 0x80AF3F3C */ .word	0x460001BC
/* 000396 0x80AF3F40 */ .word	0x4400024C
/* 000397 0x80AF3F44 */ .word	0x4500027C
/* 000398 0x80AF3F48 */ .word	0x46000280
/* 000399 0x80AF3F4C */ .word	0x440002D4
/* 000400 0x80AF3F50 */ .word	0x440002DC
/* 000401 0x80AF3F54 */ .word	0x45000308
/* 000402 0x80AF3F58 */ .word	0x46000310
/* 000403 0x80AF3F5C */ .word	0x82000010
/* 000404 0x80AF3F60 */ .word	0x82000014
/* 000405 0x80AF3F64 */ .word	0x82000018
/* 000406 0x80AF3F68 */ .word	0x8200001C
glabel objLightblockOverlayInfoOffset
/* 000407 0x80AF3F6C */ .word	0x00000070
