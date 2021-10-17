.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Yasi_InitVars
/* 000160 0x80BB4D70 */ .word	0x023C0600
/* 000161 0x80BB4D74 */ .word	0x00000000
/* 000162 0x80BB4D78 */ .word	0x02180000
/* 000163 0x80BB4D7C */ .word	0x0000015C
/* 000164 0x80BB4D80 */ .word	ObjYasi_Init
/* 000165 0x80BB4D84 */ .word	ObjYasi_Destroy
/* 000166 0x80BB4D88 */ .word	ObjYasi_Update
/* 000167 0x80BB4D8C */ .word	ObjYasi_Draw
glabel D_80BB4D90
/* 000168 0x80BB4D90 */ .word	0xC8580064
/* 000169 0x80BB4D94 */ .word	0xB0FC0FA0
/* 000170 0x80BB4D98 */ .word	0xB1000190
/* 000171 0x80BB4D9C */ .word	0x31040320
