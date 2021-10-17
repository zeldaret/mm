.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Makekinsuta_InitVars
/* 000244 0x8099FE10 */ .word	0x00F90700
/* 000245 0x8099FE14 */ .word	0x00000010
/* 000246 0x8099FE18 */ .word	0x00010000
/* 000247 0x8099FE1C */ .word	0x00000148
/* 000248 0x8099FE20 */ .word	ObjMakekinsuta_Init
/* 000249 0x8099FE24 */ .word	ObjMakekinsuta_Destroy
/* 000250 0x8099FE28 */ .word	ObjMakekinsuta_Update
/* 000251 0x8099FE2C */ .word	0x00000000
glabel D_8099FE30
/* 000252 0x8099FE30 */ .word	0xB0FC0001
/* 000253 0x8099FE34 */ .word	0xB1000001
/* 000254 0x8099FE38 */ .word	0x31040001
glabel D_8099FE3C
/* 000255 0x8099FE3C */ .word	0x00000000
/* 000256 0x8099FE40 */ .word	0x3F800000
/* 000257 0x8099FE44 */ .word	0x00000000
/* 000258 0x8099FE48 */ .word	0x00000000
/* 000259 0x8099FE4C */ .word	0x00000000
