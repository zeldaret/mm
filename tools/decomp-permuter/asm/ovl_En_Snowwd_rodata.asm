.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enSnowwdOverlayInfo
/* 000296 0x80AF7AE0 */ .word	0x00000430
/* 000297 0x80AF7AE4 */ .word	0x00000070
/* 000298 0x80AF7AE8 */ .word	0x00000000
/* 000299 0x80AF7AEC */ .word	0x00000000
/* 000300 0x80AF7AF0 */ .word	0x00000010
glabel enSnowwdOverlayRelocations
/* 000301 0x80AF7AF4 */ .word	0x45000034
/* 000302 0x80AF7AF8 */ .word	0x4600004C
/* 000303 0x80AF7AFC */ .word	0x45000068
/* 000304 0x80AF7B00 */ .word	0x4600006C
/* 000305 0x80AF7B04 */ .word	0x450002F8
/* 000306 0x80AF7B08 */ .word	0x46000320
/* 000307 0x80AF7B0C */ .word	0x450002FC
/* 000308 0x80AF7B10 */ .word	0x4600031C
/* 000309 0x80AF7B14 */ .word	0x450002E4
/* 000310 0x80AF7B18 */ .word	0x460002F4
/* 000311 0x80AF7B1C */ .word	0x450002E8
/* 000312 0x80AF7B20 */ .word	0x460002F0
/* 000313 0x80AF7B24 */ .word	0x82000010
/* 000314 0x80AF7B28 */ .word	0x82000014
/* 000315 0x80AF7B2C */ .word	0x82000018
/* 000316 0x80AF7B30 */ .word	0x8200001C
/* 000317 0x80AF7B34 */ .word	0x00000000
/* 000318 0x80AF7B38 */ .word	0x00000000
glabel enSnowwdOverlayInfoOffset
/* 000319 0x80AF7B3C */ .word	0x00000060
