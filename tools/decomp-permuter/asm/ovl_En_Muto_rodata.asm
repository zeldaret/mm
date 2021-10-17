.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enMutoOverlayInfo
/* 000600 0x80BE8460 */ .word	0x000008F0
/* 000601 0x80BE8464 */ .word	0x00000070
/* 000602 0x80BE8468 */ .word	0x00000000
/* 000603 0x80BE846C */ .word	0x00000000
/* 000604 0x80BE8470 */ .word	0x0000001B
glabel enMutoOverlayRelocations
/* 000605 0x80BE8474 */ .word	0x45000130
/* 000606 0x80BE8478 */ .word	0x4600013C
/* 000607 0x80BE847C */ .word	0x4400014C
/* 000608 0x80BE8480 */ .word	0x450001A8
/* 000609 0x80BE8484 */ .word	0x460001B8
/* 000610 0x80BE8488 */ .word	0x450001DC
/* 000611 0x80BE848C */ .word	0x460001F0
/* 000612 0x80BE8490 */ .word	0x450001C4
/* 000613 0x80BE8494 */ .word	0x460001E4
/* 000614 0x80BE8498 */ .word	0x440002C0
/* 000615 0x80BE849C */ .word	0x450002CC
/* 000616 0x80BE84A0 */ .word	0x460002D0
/* 000617 0x80BE84A4 */ .word	0x450002FC
/* 000618 0x80BE84A8 */ .word	0x4600030C
/* 000619 0x80BE84AC */ .word	0x440003A8
/* 000620 0x80BE84B0 */ .word	0x4400045C
/* 000621 0x80BE84B4 */ .word	0x450004C8
/* 000622 0x80BE84B8 */ .word	0x460004D0
/* 000623 0x80BE84BC */ .word	0x44000598
/* 000624 0x80BE84C0 */ .word	0x4400068C
/* 000625 0x80BE84C4 */ .word	0x440006CC
/* 000626 0x80BE84C8 */ .word	0x450008B0
/* 000627 0x80BE84CC */ .word	0x460008B4
/* 000628 0x80BE84D0 */ .word	0x82000010
/* 000629 0x80BE84D4 */ .word	0x82000014
/* 000630 0x80BE84D8 */ .word	0x82000018
/* 000631 0x80BE84DC */ .word	0x8200001C
/* 000632 0x80BE84E0 */ .word	0x00000000
/* 000633 0x80BE84E4 */ .word	0x00000000
/* 000634 0x80BE84E8 */ .word	0x00000000
glabel enMutoOverlayInfoOffset
/* 000635 0x80BE84EC */ .word	0x00000090
