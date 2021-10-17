.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ikninside_InitVars
/* 000348 0x80C07680 */ .word	0x02850100
/* 000349 0x80C07684 */ .word	0x00000010
/* 000350 0x80C07688 */ .word	0x02360000
/* 000351 0x80C0768C */ .word	0x000001B0
/* 000352 0x80C07690 */ .word	BgIkninside_Init
/* 000353 0x80C07694 */ .word	BgIkninside_Destroy
/* 000354 0x80C07698 */ .word	BgIkninside_Update
/* 000355 0x80C0769C */ .word	BgIkninside_Draw
glabel D_80C076A0
/* 000356 0x80C076A0 */ .word	0x0600A748
/* 000357 0x80C076A4 */ .word	0x0600A5A8
glabel D_80C076A8
/* 000358 0x80C076A8 */ .word	0x0A000909
/* 000359 0x80C076AC */ .word	0x10010000
/* 000360 0x80C076B0 */ .word	0x00000000
/* 000361 0x80C076B4 */ .word	0x00000000
/* 000362 0x80C076B8 */ .word	0x00000000
/* 000363 0x80C076BC */ .word	0x80000008
/* 000364 0x80C076C0 */ .word	0x00000000
/* 000365 0x80C076C4 */ .word	0x00010000
/* 000366 0x80C076C8 */ .word	0x00200020
/* 000367 0x80C076CC */ .word	0x00000000
/* 000368 0x80C076D0 */ .word	0x00000000
glabel D_80C076D4
/* 000369 0x80C076D4 */ .word	0x00000000
/* 000370 0x80C076D8 */ .word	0xBF800000
/* 000371 0x80C076DC */ .word	0x00000000
