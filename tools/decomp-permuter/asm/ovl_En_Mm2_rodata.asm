.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enMm2OverlayInfo
/* 000692 0x809A2B00 */ .word	0x00000220
/* 000693 0x809A2B04 */ .word	0x000008B0
/* 000694 0x809A2B08 */ .word	0x00000000
/* 000695 0x809A2B0C */ .word	0x00000000
/* 000696 0x809A2B10 */ .word	0x00000012
glabel enMm2OverlayRelocations
/* 000697 0x809A2B14 */ .word	0x45000024
/* 000698 0x809A2B18 */ .word	0x46000028
/* 000699 0x809A2B1C */ .word	0x450000A0
/* 000700 0x809A2B20 */ .word	0x460000A4
/* 000701 0x809A2B24 */ .word	0x450000B0
/* 000702 0x809A2B28 */ .word	0x460000B4
/* 000703 0x809A2B2C */ .word	0x45000104
/* 000704 0x809A2B30 */ .word	0x46000108
/* 000705 0x809A2B34 */ .word	0x450001EC
/* 000706 0x809A2B38 */ .word	0x460001F0
/* 000707 0x809A2B3C */ .word	0x82000010
/* 000708 0x809A2B40 */ .word	0x82000014
/* 000709 0x809A2B44 */ .word	0x82000018
/* 000710 0x809A2B48 */ .word	0x8200001C
/* 000711 0x809A2B4C */ .word	0x820007CC
/* 000712 0x809A2B50 */ .word	0x8200080C
/* 000713 0x809A2B54 */ .word	0x82000844
/* 000714 0x809A2B58 */ .word	0x82000884
glabel enMm2OverlayInfoOffset
/* 000715 0x809A2B5C */ .word	0x00000060
