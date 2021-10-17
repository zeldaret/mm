.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Kepn_Koya_InitVars
/* 000064 0x80C07C20 */ .word	0x02870600
/* 000065 0x80C07C24 */ .word	0x00000000
/* 000066 0x80C07C28 */ .word	0x02560000
/* 000067 0x80C07C2C */ .word	0x00000160
/* 000068 0x80C07C30 */ .word	ObjKepnKoya_Init
/* 000069 0x80C07C34 */ .word	ObjKepnKoya_Destroy
/* 000070 0x80C07C38 */ .word	ObjKepnKoya_Update
/* 000071 0x80C07C3C */ .word	ObjKepnKoya_Draw
glabel D_80C07C40
/* 000072 0x80C07C40 */ .word	0xB10004B0
/* 000073 0x80C07C44 */ .word	0x31040384
/* 000074 0x80C07C48 */ .word	0x00000000
/* 000075 0x80C07C4C */ .word	0x00000000
