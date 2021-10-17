.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDs2nOverlayInfo
/* 000300 0x80AE1B00 */ .word	0x00000460
/* 000301 0x80AE1B04 */ .word	0x00000050
/* 000302 0x80AE1B08 */ .word	0x00000000
/* 000303 0x80AE1B0C */ .word	0x00000000
/* 000304 0x80AE1B10 */ .word	0x00000014
glabel enDs2nOverlayRelocations
/* 000305 0x80AE1B14 */ .word	0x45000018
/* 000306 0x80AE1B18 */ .word	0x4600001C
/* 000307 0x80AE1B1C */ .word	0x45000034
/* 000308 0x80AE1B20 */ .word	0x46000038
/* 000309 0x80AE1B24 */ .word	0x44000168
/* 000310 0x80AE1B28 */ .word	0x44000208
/* 000311 0x80AE1B2C */ .word	0x45000274
/* 000312 0x80AE1B30 */ .word	0x46000278
/* 000313 0x80AE1B34 */ .word	0x450003AC
/* 000314 0x80AE1B38 */ .word	0x460003BC
/* 000315 0x80AE1B3C */ .word	0x450003F0
/* 000316 0x80AE1B40 */ .word	0x46000404
/* 000317 0x80AE1B44 */ .word	0x4500040C
/* 000318 0x80AE1B48 */ .word	0x46000410
/* 000319 0x80AE1B4C */ .word	0x45000424
/* 000320 0x80AE1B50 */ .word	0x46000428
/* 000321 0x80AE1B54 */ .word	0x82000010
/* 000322 0x80AE1B58 */ .word	0x82000014
/* 000323 0x80AE1B5C */ .word	0x82000018
/* 000324 0x80AE1B60 */ .word	0x8200001C
/* 000325 0x80AE1B64 */ .word	0x00000000
/* 000326 0x80AE1B68 */ .word	0x00000000
glabel enDs2nOverlayInfoOffset
/* 000327 0x80AE1B6C */ .word	0x00000070
