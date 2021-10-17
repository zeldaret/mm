.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel effChangeOverlayInfo
/* 000308 0x80A4C960 */ .word	0x00000470
/* 000309 0x80A4C964 */ .word	0x00000050
/* 000310 0x80A4C968 */ .word	0x00000010
/* 000311 0x80A4C96C */ .word	0x00000000
/* 000312 0x80A4C970 */ .word	0x0000000E
glabel effChangeOverlayRelocations
/* 000313 0x80A4C974 */ .word	0x45000018
/* 000314 0x80A4C978 */ .word	0x46000020
/* 000315 0x80A4C97C */ .word	0x4500001C
/* 000316 0x80A4C980 */ .word	0x46000024
/* 000317 0x80A4C984 */ .word	0x44000034
/* 000318 0x80A4C988 */ .word	0x45000094
/* 000319 0x80A4C98C */ .word	0x46000098
/* 000320 0x80A4C990 */ .word	0x450000F4
/* 000321 0x80A4C994 */ .word	0x460000FC
/* 000322 0x80A4C998 */ .word	0x45000254
/* 000323 0x80A4C99C */ .word	0x46000258
/* 000324 0x80A4C9A0 */ .word	0x82000010
/* 000325 0x80A4C9A4 */ .word	0x82000014
/* 000326 0x80A4C9A8 */ .word	0x82000018
glabel effChangeOverlayInfoOffset
/* 000327 0x80A4C9AC */ .word	0x00000050
