.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Hakaisi_InitVars
/* 001284 0x80B15590 */ .word	0x01E30600
/* 001285 0x80B15594 */ .word	0x00000029
/* 001286 0x80B15598 */ .word	0x01C20000
/* 001287 0x80B1559C */ .word	0x000001A0
/* 001288 0x80B155A0 */ .word	ObjHakaisi_Init
/* 001289 0x80B155A4 */ .word	ObjHakaisi_Destroy
/* 001290 0x80B155A8 */ .word	ObjHakaisi_Update
/* 001291 0x80B155AC */ .word	ObjHakaisi_Draw
glabel D_80B155B0
/* 001292 0x80B155B0 */ .word	0x00000000
/* 001293 0x80B155B4 */ .word	0x41C80000
/* 001294 0x80B155B8 */ .word	0x41F00000
glabel D_80B155BC
/* 001295 0x80B155BC */ .word	0x00000000
/* 001296 0x80B155C0 */ .word	0x42820000
/* 001297 0x80B155C4 */ .word	0x41000000
/* 001298 0x80B155C8 */ .word	0x00000000
/* 001299 0x80B155CC */ .word	0x420C0000
/* 001300 0x80B155D0 */ .word	0x41000000
/* 001301 0x80B155D4 */ .word	0x00000000
/* 001302 0x80B155D8 */ .word	0x41700000
/* 001303 0x80B155DC */ .word	0x41000000
glabel D_80B155E0
/* 001304 0x80B155E0 */ .word	0x00000000
/* 001305 0x80B155E4 */ .word	0x00000000
/* 001306 0x80B155E8 */ .word	0x00000000
glabel D_80B155EC
/* 001307 0x80B155EC */ .word	0x00000000
/* 001308 0x80B155F0 */ .word	0x00000000
/* 001309 0x80B155F4 */ .word	0x00000000
glabel D_80B155F8
/* 001310 0x80B155F8 */ .word	0xAA825AFF
glabel D_80B155FC
/* 001311 0x80B155FC */ .word	0x643C1400
glabel D_80B15600
/* 001312 0x80B15600 */ .word	0x3F800000
/* 001313 0x80B15604 */ .word	0x00000000
/* 001314 0x80B15608 */ .word	0x00000000
/* 001315 0x80B1560C */ .word	0x00000000
