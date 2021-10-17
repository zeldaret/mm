.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objWturnOverlayInfo
/* 000296 0x808A7DD0 */ .word	0x00000470
/* 000297 0x808A7DD4 */ .word	0x00000030
/* 000298 0x808A7DD8 */ .word	0x00000000
/* 000299 0x808A7DDC */ .word	0x00000000
/* 000300 0x808A7DE0 */ .word	0x00000010
glabel objWturnOverlayRelocations
/* 000301 0x808A7DE4 */ .word	0x4400000C
/* 000302 0x808A7DE8 */ .word	0x45000024
/* 000303 0x808A7DEC */ .word	0x46000028
/* 000304 0x808A7DF0 */ .word	0x440000D8
/* 000305 0x808A7DF4 */ .word	0x45000110
/* 000306 0x808A7DF8 */ .word	0x46000114
/* 000307 0x808A7DFC */ .word	0x44000154
/* 000308 0x808A7E00 */ .word	0x45000250
/* 000309 0x808A7E04 */ .word	0x46000254
/* 000310 0x808A7E08 */ .word	0x4400029C
/* 000311 0x808A7E0C */ .word	0x45000328
/* 000312 0x808A7E10 */ .word	0x4600032C
/* 000313 0x808A7E14 */ .word	0x45000390
/* 000314 0x808A7E18 */ .word	0x46000394
/* 000315 0x808A7E1C */ .word	0x82000010
/* 000316 0x808A7E20 */ .word	0x82000018
/* 000317 0x808A7E24 */ .word	0x00000000
/* 000318 0x808A7E28 */ .word	0x00000000
glabel objWturnOverlayInfoOffset
/* 000319 0x808A7E2C */ .word	0x00000060
