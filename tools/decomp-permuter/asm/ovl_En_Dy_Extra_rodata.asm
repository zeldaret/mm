.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDyExtraOverlayInfo
/* 000316 0x80A617A0 */ .word	0x00000470
/* 000317 0x80A617A4 */ .word	0x00000070
/* 000318 0x80A617A8 */ .word	0x00000010
/* 000319 0x80A617AC */ .word	0x00000000
/* 000320 0x80A617B0 */ .word	0x00000016
glabel enDyExtraOverlayRelocations
/* 000321 0x80A617B4 */ .word	0x45000010
/* 000322 0x80A617B8 */ .word	0x46000014
/* 000323 0x80A617BC */ .word	0x45000028
/* 000324 0x80A617C0 */ .word	0x46000030
/* 000325 0x80A617C4 */ .word	0x45000044
/* 000326 0x80A617C8 */ .word	0x46000054
/* 000327 0x80A617CC */ .word	0x45000060
/* 000328 0x80A617D0 */ .word	0x46000068
/* 000329 0x80A617D4 */ .word	0x450000EC
/* 000330 0x80A617D8 */ .word	0x460000F8
/* 000331 0x80A617DC */ .word	0x4500014C
/* 000332 0x80A617E0 */ .word	0x46000158
/* 000333 0x80A617E4 */ .word	0x4500025C
/* 000334 0x80A617E8 */ .word	0x46000260
/* 000335 0x80A617EC */ .word	0x450003AC
/* 000336 0x80A617F0 */ .word	0x460003B0
/* 000337 0x80A617F4 */ .word	0x450003EC
/* 000338 0x80A617F8 */ .word	0x46000400
/* 000339 0x80A617FC */ .word	0x82000010
/* 000340 0x80A61800 */ .word	0x82000014
/* 000341 0x80A61804 */ .word	0x82000018
/* 000342 0x80A61808 */ .word	0x8200001C
glabel enDyExtraOverlayInfoOffset
/* 000343 0x80A6180C */ .word	0x00000070
