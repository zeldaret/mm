.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objWindOverlayInfo
/* 000452 0x80B245E0 */ .word	0x00000590
/* 000453 0x80B245E4 */ .word	0x00000170
/* 000454 0x80B245E8 */ .word	0x00000010
/* 000455 0x80B245EC */ .word	0x00000000
/* 000456 0x80B245F0 */ .word	0x0000000C
glabel objWindOverlayRelocations
/* 000457 0x80B245F4 */ .word	0x45000014
/* 000458 0x80B245F8 */ .word	0x46000018
/* 000459 0x80B245FC */ .word	0x45000098
/* 000460 0x80B24600 */ .word	0x460000AC
/* 000461 0x80B24604 */ .word	0x450000A0
/* 000462 0x80B24608 */ .word	0x460000A4
/* 000463 0x80B2460C */ .word	0x4500035C
/* 000464 0x80B24610 */ .word	0x46000378
/* 000465 0x80B24614 */ .word	0x82000010
/* 000466 0x80B24618 */ .word	0x82000014
/* 000467 0x80B2461C */ .word	0x82000018
/* 000468 0x80B24620 */ .word	0x8200001C
/* 000469 0x80B24624 */ .word	0x00000000
/* 000470 0x80B24628 */ .word	0x00000000
glabel objWindOverlayInfoOffset
/* 000471 0x80B2462C */ .word	0x00000050
