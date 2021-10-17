.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Paper_InitVars
/* 000540 0x80C1FC40 */ .word	0x02A40700
/* 000541 0x80C1FC44 */ .word	0x02100010
/* 000542 0x80C1FC48 */ .word	0x01850000
/* 000543 0x80C1FC4C */ .word	0x00000D88
/* 000544 0x80C1FC50 */ .word	EnPaper_Init
/* 000545 0x80C1FC54 */ .word	EnPaper_Destroy
/* 000546 0x80C1FC58 */ .word	EnPaper_Update
/* 000547 0x80C1FC5C */ .word	EnPaper_Draw
glabel D_80C1FC60
/* 000548 0x80C1FC60 */ .word	0x00000000
/* 000549 0x80C1FC64 */ .word	0x00000000
/* 000550 0x80C1FC68 */ .word	0x3F800000
/* 000551 0x80C1FC6C */ .word	0x00000000
