.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ruppecrow_InitVars
/* 001484 0x80BE3990 */ .word	0x02660500
/* 001485 0x80BE3994 */ .word	0x00004030
/* 001486 0x80BE3998 */ .word	0x00060000
/* 001487 0x80BE399C */ .word	0x00000304
/* 001488 0x80BE39A0 */ .word	EnRuppecrow_Init
/* 001489 0x80BE39A4 */ .word	EnRuppecrow_Destroy
/* 001490 0x80BE39A8 */ .word	EnRuppecrow_Update
/* 001491 0x80BE39AC */ .word	EnRuppecrow_Draw
glabel D_80BE39B0
/* 001492 0x80BE39B0 */ .word	0x00000000
/* 001493 0x80BE39B4 */ .word	0xF7CFFFFF
/* 001494 0x80BE39B8 */ .word	0x00000000
/* 001495 0x80BE39BC */ .word	0xF7CFFFFF
/* 001496 0x80BE39C0 */ .word	0x00000000
/* 001497 0x80BE39C4 */ .word	0x00010100
/* 001498 0x80BE39C8 */ .word	0x01000000
/* 001499 0x80BE39CC */ .word	0x00000000
/* 001500 0x80BE39D0 */ .word	0x00140064
glabel D_80BE39D4
/* 001501 0x80BE39D4 */ .word	0x03000939
/* 001502 0x80BE39D8 */ .word	0x10000000
/* 001503 0x80BE39DC */ .word	0x00000001
glabel D_80BE39E0
/* 001504 0x80BE39E0 */ .word	D_80BE39B0
glabel D_80BE39E4
/* 001505 0x80BE39E4 */ .word	0x0100000F
/* 001506 0x80BE39E8 */ .word	0x001E1E00
glabel D_80BE39EC
/* 001507 0x80BE39EC */ .word	0x10010101
/* 001508 0x80BE39F0 */ .word	0x01010001
/* 001509 0x80BE39F4 */ .word	0x01010122
/* 001510 0x80BE39F8 */ .word	0x32420101
/* 001511 0x80BE39FC */ .word	0x01021000
/* 001512 0x80BE3A00 */ .word	0x00000101
/* 001513 0x80BE3A04 */ .word	0x01000000
/* 001514 0x80BE3A08 */ .word	0x00000001
glabel D_80BE3A0C
/* 001515 0x80BE3A0C */ .word	0xB874FE0C
/* 001516 0x80BE3A10 */ .word	0x305407D0
/* 001517 0x80BE3A14 */ .word	0x00000000
/* 001518 0x80BE3A18 */ .word	0x00000000
/* 001519 0x80BE3A1C */ .word	0x00000000
