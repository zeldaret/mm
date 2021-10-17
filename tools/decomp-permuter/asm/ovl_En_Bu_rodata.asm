.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBuOverlayInfo
/* 000092 0x809ACF00 */ .word	0x00000140
/* 000093 0x809ACF04 */ .word	0x00000020
/* 000094 0x809ACF08 */ .word	0x00000010
/* 000095 0x809ACF0C */ .word	0x00000000
/* 000096 0x809ACF10 */ .word	0x00000008
glabel enBuOverlayRelocations
/* 000097 0x809ACF14 */ .word	0x45000004
/* 000098 0x809ACF18 */ .word	0x46000008
/* 000099 0x809ACF1C */ .word	0x450000C8
/* 000100 0x809ACF20 */ .word	0x460000CC
/* 000101 0x809ACF24 */ .word	0x82000010
/* 000102 0x809ACF28 */ .word	0x82000014
/* 000103 0x809ACF2C */ .word	0x82000018
/* 000104 0x809ACF30 */ .word	0x8200001C
/* 000105 0x809ACF34 */ .word	0x00000000
/* 000106 0x809ACF38 */ .word	0x00000000
glabel enBuOverlayInfoOffset
/* 000107 0x809ACF3C */ .word	0x00000040
