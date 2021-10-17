.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Fu_Kaiten_InitVars
/* 000140 0x80ACB630 */ .word	0x01AE0100
/* 000141 0x80ACB634 */ .word	0x00000030
/* 000142 0x80ACB638 */ .word	0x01A00000
/* 000143 0x80ACB63C */ .word	0x00000170
/* 000144 0x80ACB640 */ .word	BgFuKaiten_Init
/* 000145 0x80ACB644 */ .word	BgFuKaiten_Destroy
/* 000146 0x80ACB648 */ .word	BgFuKaiten_Update
/* 000147 0x80ACB64C */ .word	BgFuKaiten_Draw
