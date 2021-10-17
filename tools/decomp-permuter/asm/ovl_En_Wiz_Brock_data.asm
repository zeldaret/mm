.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80A495B0
/* 000372 0x80A495B0 */ .word	0x00000000
glabel En_Wiz_Brock_InitVars
/* 000373 0x80A495B4 */ .word	0x015E0600
/* 000374 0x80A495B8 */ .word	0x08000010
/* 000375 0x80A495BC */ .word	0x01780000
/* 000376 0x80A495C0 */ .word	0x000001B0
/* 000377 0x80A495C4 */ .word	EnWizBrock_Init
/* 000378 0x80A495C8 */ .word	EnWizBrock_Destroy
/* 000379 0x80A495CC */ .word	EnWizBrock_Update
/* 000380 0x80A495D0 */ .word	EnWizBrock_Draw
/* 000381 0x80A495D4 */ .word	0x00000000
/* 000382 0x80A495D8 */ .word	0x00000000
/* 000383 0x80A495DC */ .word	0x00000000
