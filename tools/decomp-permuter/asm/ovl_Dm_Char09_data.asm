.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Char09_InitVars
/* 000544 0x80AB2690 */ .word	0x019B0700
/* 000545 0x80AB2694 */ .word	0x00000030
/* 000546 0x80AB2698 */ .word	0x01EB0000
/* 000547 0x80AB269C */ .word	0x00000230
/* 000548 0x80AB26A0 */ .word	DmChar09_Init
/* 000549 0x80AB26A4 */ .word	DmChar09_Destroy
/* 000550 0x80AB26A8 */ .word	DmChar09_Update
/* 000551 0x80AB26AC */ .word	DmChar09_Draw
glabel D_80AB26B0
/* 000552 0x80AB26B0 */ .word	0x0600005C
/* 000553 0x80AB26B4 */ .word	0x3F800000
/* 000554 0x80AB26B8 */ .word	0x00000000
/* 000555 0x80AB26BC */ .word	0xBF800000
/* 000556 0x80AB26C0 */ .word	0x00000000
/* 000557 0x80AB26C4 */ .word	0x00000000
/* 000558 0x80AB26C8 */ .word	0x00000000
/* 000559 0x80AB26CC */ .word	0x00000000
