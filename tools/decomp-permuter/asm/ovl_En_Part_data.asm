.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Part_InitVars
/* 000348 0x808658E0 */ .word	0x00030700
/* 000349 0x808658E4 */ .word	0x00000010
/* 000350 0x808658E8 */ .word	0x00010000
/* 000351 0x808658EC */ .word	0x00000154
/* 000352 0x808658F0 */ .word	EnPart_Init
/* 000353 0x808658F4 */ .word	EnPart_Destroy
/* 000354 0x808658F8 */ .word	EnPart_Update
/* 000355 0x808658FC */ .word	EnPart_Draw
glabel D_80865900
/* 000356 0x80865900 */ .word	0x00000000
/* 000357 0x80865904 */ .word	0x00000000
/* 000358 0x80865908 */ .word	0x00000000
glabel D_8086590C
/* 000359 0x8086590C */ .word	func_80865390
/* 000360 0x80865910 */ .word	func_808654C4
/* 000361 0x80865914 */ .word	0x00000000
/* 000362 0x80865918 */ .word	0x00000000
/* 000363 0x8086591C */ .word	0x00000000
