.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel dmChar07OverlayInfo
/* 000404 0x80AAF010 */ .word	0x00000630
/* 000405 0x80AAF014 */ .word	0x00000020
/* 000406 0x80AAF018 */ .word	0x00000000
/* 000407 0x80AAF01C */ .word	0x00000000
/* 000408 0x80AAF020 */ .word	0x00000007
glabel dmChar07OverlayRelocations
/* 000409 0x80AAF024 */ .word	0x450000A0
/* 000410 0x80AAF028 */ .word	0x460000A4
/* 000411 0x80AAF02C */ .word	0x440000A8
/* 000412 0x80AAF030 */ .word	0x82000010
/* 000413 0x80AAF034 */ .word	0x82000014
/* 000414 0x80AAF038 */ .word	0x82000018
/* 000415 0x80AAF03C */ .word	0x8200001C
/* 000416 0x80AAF040 */ .word	0x00000000
/* 000417 0x80AAF044 */ .word	0x00000000
/* 000418 0x80AAF048 */ .word	0x00000000
glabel dmChar07OverlayInfoOffset
/* 000419 0x80AAF04C */ .word	0x00000040
