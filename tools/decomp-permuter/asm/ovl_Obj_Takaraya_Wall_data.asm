.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Takaraya_Wall_InitVars
/* 001040 0x80ADA280 */ .word	0x01BB0100
/* 001041 0x80ADA284 */ .word	0x00000030
/* 001042 0x80ADA288 */ .word	0x01B40000
/* 001043 0x80ADA28C */ .word	0x000001E0
/* 001044 0x80ADA290 */ .word	ObjTakarayaWall_Init
/* 001045 0x80ADA294 */ .word	ObjTakarayaWall_Destroy
/* 001046 0x80ADA298 */ .word	ObjTakarayaWall_Update
/* 001047 0x80ADA29C */ .word	ObjTakarayaWall_Draw
glabel D_80ADA2A0
/* 001048 0x80ADA2A0 */ .word	0x0A000039
/* 001049 0x80ADA2A4 */ .word	0x20010000
/* 001050 0x80ADA2A8 */ .word	0x00000000
/* 001051 0x80ADA2AC */ .word	0x00000000
/* 001052 0x80ADA2B0 */ .word	0x00000000
/* 001053 0x80ADA2B4 */ .word	0x00000000
/* 001054 0x80ADA2B8 */ .word	0x00000000
/* 001055 0x80ADA2BC */ .word	0x00000100
/* 001056 0x80ADA2C0 */ .word	0x00280078
/* 001057 0x80ADA2C4 */ .word	0x00000000
/* 001058 0x80ADA2C8 */ .word	0x00000000
glabel D_80ADA2CC
/* 001059 0x80ADA2CC */ .word	0x48580064
