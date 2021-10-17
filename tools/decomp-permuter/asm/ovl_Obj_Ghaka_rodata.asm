.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objGhakaOverlayInfo
/* 000460 0x80B3C990 */ .word	0x000006E0
/* 000461 0x80B3C994 */ .word	0x00000040
/* 000462 0x80B3C998 */ .word	0x00000010
/* 000463 0x80B3C99C */ .word	0x00000000
/* 000464 0x80B3C9A0 */ .word	0x0000001C
glabel objGhakaOverlayRelocations
/* 000465 0x80B3C9A4 */ .word	0x45000008
/* 000466 0x80B3C9A8 */ .word	0x46000018
/* 000467 0x80B3C9AC */ .word	0x4500003C
/* 000468 0x80B3C9B0 */ .word	0x46000040
/* 000469 0x80B3C9B4 */ .word	0x45000050
/* 000470 0x80B3C9B8 */ .word	0x46000054
/* 000471 0x80B3C9BC */ .word	0x45000094
/* 000472 0x80B3C9C0 */ .word	0x46000098
/* 000473 0x80B3C9C4 */ .word	0x450000EC
/* 000474 0x80B3C9C8 */ .word	0x460000F0
/* 000475 0x80B3C9CC */ .word	0x4400018C
/* 000476 0x80B3C9D0 */ .word	0x44000248
/* 000477 0x80B3C9D4 */ .word	0x440002D8
/* 000478 0x80B3C9D8 */ .word	0x440003A8
/* 000479 0x80B3C9DC */ .word	0x44000444
/* 000480 0x80B3C9E0 */ .word	0x44000460
/* 000481 0x80B3C9E4 */ .word	0x45000468
/* 000482 0x80B3C9E8 */ .word	0x4600046C
/* 000483 0x80B3C9EC */ .word	0x45000408
/* 000484 0x80B3C9F0 */ .word	0x46000414
/* 000485 0x80B3C9F4 */ .word	0x450004AC
/* 000486 0x80B3C9F8 */ .word	0x460004B4
/* 000487 0x80B3C9FC */ .word	0x44000554
/* 000488 0x80B3CA00 */ .word	0x4400055C
/* 000489 0x80B3CA04 */ .word	0x82000010
/* 000490 0x80B3CA08 */ .word	0x82000014
/* 000491 0x80B3CA0C */ .word	0x82000018
/* 000492 0x80B3CA10 */ .word	0x8200001C
/* 000493 0x80B3CA14 */ .word	0x00000000
/* 000494 0x80B3CA18 */ .word	0x00000000
glabel objGhakaOverlayInfoOffset
/* 000495 0x80B3CA1C */ .word	0x00000090
