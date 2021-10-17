.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgCtowerRotOverlayInfo
/* 000324 0x808E2580 */ .word	0x000004D0
/* 000325 0x808E2584 */ .word	0x00000030
/* 000326 0x808E2588 */ .word	0x00000010
/* 000327 0x808E258C */ .word	0x00000000
/* 000328 0x808E2590 */ .word	0x0000001A
glabel bgCtowerRotOverlayRelocations
/* 000329 0x808E2594 */ .word	0x45000014
/* 000330 0x808E2598 */ .word	0x46000018
/* 000331 0x808E259C */ .word	0x45000054
/* 000332 0x808E25A0 */ .word	0x46000058
/* 000333 0x808E25A4 */ .word	0x45000120
/* 000334 0x808E25A8 */ .word	0x46000128
/* 000335 0x808E25AC */ .word	0x450000D4
/* 000336 0x808E25B0 */ .word	0x460000D8
/* 000337 0x808E25B4 */ .word	0x450001B4
/* 000338 0x808E25B8 */ .word	0x460001B8
/* 000339 0x808E25BC */ .word	0x4500021C
/* 000340 0x808E25C0 */ .word	0x46000224
/* 000341 0x808E25C4 */ .word	0x45000284
/* 000342 0x808E25C8 */ .word	0x46000288
/* 000343 0x808E25CC */ .word	0x450002EC
/* 000344 0x808E25D0 */ .word	0x460002F0
/* 000345 0x808E25D4 */ .word	0x450003B8
/* 000346 0x808E25D8 */ .word	0x460003BC
/* 000347 0x808E25DC */ .word	0x4500041C
/* 000348 0x808E25E0 */ .word	0x46000420
/* 000349 0x808E25E4 */ .word	0x4500047C
/* 000350 0x808E25E8 */ .word	0x46000494
/* 000351 0x808E25EC */ .word	0x82000010
/* 000352 0x808E25F0 */ .word	0x82000014
/* 000353 0x808E25F4 */ .word	0x82000018
/* 000354 0x808E25F8 */ .word	0x8200001C
glabel bgCtowerRotOverlayInfoOffset
/* 000355 0x808E25FC */ .word	0x00000080
