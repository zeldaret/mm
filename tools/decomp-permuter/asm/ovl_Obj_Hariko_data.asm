.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Hariko_InitVars
/* 000164 0x80B66CB0 */ .word	0x020A0600
/* 000165 0x80B66CB4 */ .word	0x02000020
/* 000166 0x80B66CB8 */ .word	0x01F20000
/* 000167 0x80B66CBC */ .word	0x00000158
/* 000168 0x80B66CC0 */ .word	ObjHariko_Init
/* 000169 0x80B66CC4 */ .word	ObjHariko_Destroy
/* 000170 0x80B66CC8 */ .word	ObjHariko_Update
/* 000171 0x80B66CCC */ .word	ObjHariko_Draw
