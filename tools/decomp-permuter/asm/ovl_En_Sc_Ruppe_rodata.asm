.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enScRuppeOverlayInfo
/* 000352 0x80BD6E90 */ .word	0x000004E0
/* 000353 0x80BD6E94 */ .word	0x00000080
/* 000354 0x80BD6E98 */ .word	0x00000020
/* 000355 0x80BD6E9C */ .word	0x00000000
/* 000356 0x80BD6EA0 */ .word	0x0000001A
glabel enScRuppeOverlayRelocations
/* 000357 0x80BD6EA4 */ .word	0x45000084
/* 000358 0x80BD6EA8 */ .word	0x4600008C
/* 000359 0x80BD6EAC */ .word	0x450001BC
/* 000360 0x80BD6EB0 */ .word	0x460001D0
/* 000361 0x80BD6EB4 */ .word	0x450001D8
/* 000362 0x80BD6EB8 */ .word	0x460001DC
/* 000363 0x80BD6EBC */ .word	0x4400022C
/* 000364 0x80BD6EC0 */ .word	0x45000284
/* 000365 0x80BD6EC4 */ .word	0x4600029C
/* 000366 0x80BD6EC8 */ .word	0x450002FC
/* 000367 0x80BD6ECC */ .word	0x46000304
/* 000368 0x80BD6ED0 */ .word	0x45000344
/* 000369 0x80BD6ED4 */ .word	0x46000354
/* 000370 0x80BD6ED8 */ .word	0x440003F0
/* 000371 0x80BD6EDC */ .word	0x45000488
/* 000372 0x80BD6EE0 */ .word	0x460004A0
/* 000373 0x80BD6EE4 */ .word	0x82000010
/* 000374 0x80BD6EE8 */ .word	0x82000014
/* 000375 0x80BD6EEC */ .word	0x82000018
/* 000376 0x80BD6EF0 */ .word	0x8200001C
/* 000377 0x80BD6EF4 */ .word	0xC2000000
/* 000378 0x80BD6EF8 */ .word	0xC2000004
/* 000379 0x80BD6EFC */ .word	0xC2000008
/* 000380 0x80BD6F00 */ .word	0xC200000C
/* 000381 0x80BD6F04 */ .word	0xC2000010
/* 000382 0x80BD6F08 */ .word	0xC2000014
glabel enScRuppeOverlayInfoOffset
/* 000383 0x80BD6F0C */ .word	0x00000080
