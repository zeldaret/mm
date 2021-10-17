.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objMoonStoneOverlayInfo
/* 000328 0x80C06A30 */ .word	0x00000500
/* 000329 0x80C06A34 */ .word	0x00000020
/* 000330 0x80C06A38 */ .word	0x00000000
/* 000331 0x80C06A3C */ .word	0x00000000
/* 000332 0x80C06A40 */ .word	0x00000013
glabel objMoonStoneOverlayRelocations
/* 000333 0x80C06A44 */ .word	0x44000074
/* 000334 0x80C06A48 */ .word	0x440000E0
/* 000335 0x80C06A4C */ .word	0x4500011C
/* 000336 0x80C06A50 */ .word	0x46000120
/* 000337 0x80C06A54 */ .word	0x440001A0
/* 000338 0x80C06A58 */ .word	0x450001E8
/* 000339 0x80C06A5C */ .word	0x460001EC
/* 000340 0x80C06A60 */ .word	0x44000214
/* 000341 0x80C06A64 */ .word	0x45000234
/* 000342 0x80C06A68 */ .word	0x46000238
/* 000343 0x80C06A6C */ .word	0x45000284
/* 000344 0x80C06A70 */ .word	0x46000288
/* 000345 0x80C06A74 */ .word	0x440002F4
/* 000346 0x80C06A78 */ .word	0x4500034C
/* 000347 0x80C06A7C */ .word	0x46000350
/* 000348 0x80C06A80 */ .word	0x82000010
/* 000349 0x80C06A84 */ .word	0x82000014
/* 000350 0x80C06A88 */ .word	0x82000018
/* 000351 0x80C06A8C */ .word	0x8200001C
/* 000352 0x80C06A90 */ .word	0x00000000
/* 000353 0x80C06A94 */ .word	0x00000000
/* 000354 0x80C06A98 */ .word	0x00000000
glabel objMoonStoneOverlayInfoOffset
/* 000355 0x80C06A9C */ .word	0x00000070
