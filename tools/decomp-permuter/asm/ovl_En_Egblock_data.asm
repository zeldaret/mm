.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Egblock_InitVars
/* 000552 0x80ABB040 */ .word	0x019F0600
/* 000553 0x80ABB044 */ .word	0x08000000
/* 000554 0x80ABB048 */ .word	0x018D0000
/* 000555 0x80ABB04C */ .word	0x00000DB4
/* 000556 0x80ABB050 */ .word	EnEgblock_Init
/* 000557 0x80ABB054 */ .word	EnEgblock_Destroy
/* 000558 0x80ABB058 */ .word	EnEgblock_Update
/* 000559 0x80ABB05C */ .word	EnEgblock_Draw
