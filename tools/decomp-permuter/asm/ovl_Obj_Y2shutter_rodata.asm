.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objY2shutterOverlayInfo
/* 000336 0x80B9AEC0 */ .word	0x000004D0
/* 000337 0x80B9AEC4 */ .word	0x00000070
/* 000338 0x80B9AEC8 */ .word	0x00000000
/* 000339 0x80B9AECC */ .word	0x00000000
/* 000340 0x80B9AED0 */ .word	0x0000001C
glabel objY2shutterOverlayRelocations
/* 000341 0x80B9AED4 */ .word	0x45000010
/* 000342 0x80B9AED8 */ .word	0x46000014
/* 000343 0x80B9AEDC */ .word	0x45000028
/* 000344 0x80B9AEE0 */ .word	0x46000030
/* 000345 0x80B9AEE4 */ .word	0x4500011C
/* 000346 0x80B9AEE8 */ .word	0x46000128
/* 000347 0x80B9AEEC */ .word	0x45000130
/* 000348 0x80B9AEF0 */ .word	0x4600013C
/* 000349 0x80B9AEF4 */ .word	0x45000230
/* 000350 0x80B9AEF8 */ .word	0x46000234
/* 000351 0x80B9AEFC */ .word	0x44000240
/* 000352 0x80B9AF00 */ .word	0x45000268
/* 000353 0x80B9AF04 */ .word	0x4600026C
/* 000354 0x80B9AF08 */ .word	0x44000278
/* 000355 0x80B9AF0C */ .word	0x45000288
/* 000356 0x80B9AF10 */ .word	0x4600028C
/* 000357 0x80B9AF14 */ .word	0x45000300
/* 000358 0x80B9AF18 */ .word	0x46000310
/* 000359 0x80B9AF1C */ .word	0x450002EC
/* 000360 0x80B9AF20 */ .word	0x4600033C
/* 000361 0x80B9AF24 */ .word	0x450003C0
/* 000362 0x80B9AF28 */ .word	0x460003D0
/* 000363 0x80B9AF2C */ .word	0x45000494
/* 000364 0x80B9AF30 */ .word	0x46000498
/* 000365 0x80B9AF34 */ .word	0x82000010
/* 000366 0x80B9AF38 */ .word	0x82000014
/* 000367 0x80B9AF3C */ .word	0x82000018
/* 000368 0x80B9AF40 */ .word	0x8200001C
/* 000369 0x80B9AF44 */ .word	0x00000000
/* 000370 0x80B9AF48 */ .word	0x00000000
glabel objY2shutterOverlayInfoOffset
/* 000371 0x80B9AF4C */ .word	0x00000090
