.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Y2shutter_InitVars
/* 000308 0x80B9AE50 */ .word	0x022B0100
/* 000309 0x80B9AE54 */ .word	0x00000010
/* 000310 0x80B9AE58 */ .word	0x020E0000
/* 000311 0x80B9AE5C */ .word	0x00000160
/* 000312 0x80B9AE60 */ .word	ObjY2shutter_Init
/* 000313 0x80B9AE64 */ .word	ObjY2shutter_Destroy
/* 000314 0x80B9AE68 */ .word	ObjY2shutter_Update
/* 000315 0x80B9AE6C */ .word	ObjY2shutter_Draw
glabel D_80B9AE70
/* 000316 0x80B9AE70 */ .word	0x060032A0
/* 000317 0x80B9AE74 */ .word	0x060035B0
/* 000318 0x80B9AE78 */ .word	0x42F00000
/* 000319 0x80B9AE7C */ .word	0x41A00000
/* 000320 0x80B9AE80 */ .word	0x40400000
/* 000321 0x80B9AE84 */ .word	0xC1A00000
/* 000322 0x80B9AE88 */ .word	0x40400000
glabel D_80B9AE8C
/* 000323 0x80B9AE8C */ .byte	0x04
glabel D_80B9AE8D
/* 000323 0x80B9AE8C */ .byte	0x08
glabel D_80B9AE8E
/* 000323 0x80B9AE8C */ .short	0xA000
/* 000324 0x80B9AE90 */ .word	0x06005720
/* 000325 0x80B9AE94 */ .word	0x06005EC8
/* 000326 0x80B9AE98 */ .word	0x43160000
/* 000327 0x80B9AE9C */ .word	0x3F800000
/* 000328 0x80B9AEA0 */ .word	0x3D23D70A
/* 000329 0x80B9AEA4 */ .word	0xBF800000
/* 000330 0x80B9AEA8 */ .word	0x3D23D70A
/* 000331 0x80B9AEAC */ .short	0x060C
glabel D_80B9AEAE
/* 000331 0x80B9AEAC */ .short	0xA000
glabel D_80B9AEB0
/* 000332 0x80B9AEB0 */ .word	0xC8580064
/* 000333 0x80B9AEB4 */ .word	0xB0FC0FA0
/* 000334 0x80B9AEB8 */ .word	0xB1000320
/* 000335 0x80B9AEBC */ .word	0x31040320
