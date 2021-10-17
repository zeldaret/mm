.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Hana_InitVars
/* 000032 0x8095FB90 */ .word	0x00B10600
/* 000033 0x8095FB94 */ .word	0x00000000
/* 000034 0x8095FB98 */ .word	0x01BA0000
/* 000035 0x8095FB9C */ .word	0x00000144
/* 000036 0x8095FBA0 */ .word	ObjHana_Init
/* 000037 0x8095FBA4 */ .word	ObjHana_Destroy
/* 000038 0x8095FBA8 */ .word	ObjHana_Update
/* 000039 0x8095FBAC */ .word	ObjHana_Draw
glabel D_8095FBB0
/* 000040 0x8095FBB0 */ .word	0xC858000A
/* 000041 0x8095FBB4 */ .word	0xB0FC0384
/* 000042 0x8095FBB8 */ .word	0xB1000028
/* 000043 0x8095FBBC */ .word	0x31040028
