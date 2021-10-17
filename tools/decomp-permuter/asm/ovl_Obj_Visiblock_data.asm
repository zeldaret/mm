.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Visiblock_InitVars
/* 000048 0x80ADEB30 */ .word	0x01C00100
/* 000049 0x80ADEB34 */ .word	0x00000080
/* 000050 0x80ADEB38 */ .word	0x01A80000
/* 000051 0x80ADEB3C */ .word	0x00000160
/* 000052 0x80ADEB40 */ .word	ObjVisiblock_Init
/* 000053 0x80ADEB44 */ .word	ObjVisiblock_Destroy
/* 000054 0x80ADEB48 */ .word	func_800BDFB0
/* 000055 0x80ADEB4C */ .word	ObjVisiblock_Draw
glabel D_80ADEB50
/* 000056 0x80ADEB50 */ .word	0xB0FC0FA0
/* 000057 0x80ADEB54 */ .word	0xB10000C8
/* 000058 0x80ADEB58 */ .word	0xB1040096
/* 000059 0x80ADEB5C */ .word	0x48580064
