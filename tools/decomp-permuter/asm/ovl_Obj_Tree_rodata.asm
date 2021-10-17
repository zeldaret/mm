.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objTreeOverlayInfo
/* 000332 0x80B9A5E0 */ .word	0x000004A0
/* 000333 0x80B9A5E4 */ .word	0x00000080
/* 000334 0x80B9A5E8 */ .word	0x00000010
/* 000335 0x80B9A5EC */ .word	0x00000000
/* 000336 0x80B9A5F0 */ .word	0x00000014
glabel objTreeOverlayRelocations
/* 000337 0x80B9A5F4 */ .word	0x4500009C
/* 000338 0x80B9A5F8 */ .word	0x460000A4
/* 000339 0x80B9A5FC */ .word	0x450000B4
/* 000340 0x80B9A600 */ .word	0x460000C0
/* 000341 0x80B9A604 */ .word	0x450000B8
/* 000342 0x80B9A608 */ .word	0x460000BC
/* 000343 0x80B9A60C */ .word	0x440000F0
/* 000344 0x80B9A610 */ .word	0x4500015C
/* 000345 0x80B9A614 */ .word	0x46000160
/* 000346 0x80B9A618 */ .word	0x4500018C
/* 000347 0x80B9A61C */ .word	0x46000190
/* 000348 0x80B9A620 */ .word	0x450001B0
/* 000349 0x80B9A624 */ .word	0x460001B4
/* 000350 0x80B9A628 */ .word	0x440001F8
/* 000351 0x80B9A62C */ .word	0x44000320
/* 000352 0x80B9A630 */ .word	0x4400035C
/* 000353 0x80B9A634 */ .word	0x82000010
/* 000354 0x80B9A638 */ .word	0x82000014
/* 000355 0x80B9A63C */ .word	0x82000018
/* 000356 0x80B9A640 */ .word	0x8200001C
/* 000357 0x80B9A644 */ .word	0x00000000
/* 000358 0x80B9A648 */ .word	0x00000000
glabel objTreeOverlayInfoOffset
/* 000359 0x80B9A64C */ .word	0x00000070
