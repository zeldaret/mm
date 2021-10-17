.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Gamelupy_InitVars
/* 000348 0x80AF6CD0 */ .word	0x01D20600
/* 000349 0x80AF6CD4 */ .word	0x00000010
/* 000350 0x80AF6CD8 */ .word	0x00010000
/* 000351 0x80AF6CDC */ .word	0x000001A4
/* 000352 0x80AF6CE0 */ .word	EnGamelupy_Init
/* 000353 0x80AF6CE4 */ .word	EnGamelupy_Destroy
/* 000354 0x80AF6CE8 */ .word	EnGamelupy_Update
/* 000355 0x80AF6CEC */ .word	EnGamelupy_Draw
glabel D_80AF6CF0
/* 000356 0x80AF6CF0 */ .word	0x0A00000D
/* 000357 0x80AF6CF4 */ .word	0x20010000
/* 000358 0x80AF6CF8 */ .word	0x04000000
/* 000359 0x80AF6CFC */ .word	0x00000000
/* 000360 0x80AF6D00 */ .word	0x00000000
/* 000361 0x80AF6D04 */ .word	0x00000000
/* 000362 0x80AF6D08 */ .word	0x00000000
/* 000363 0x80AF6D0C */ .word	0x00000100
/* 000364 0x80AF6D10 */ .word	0x000A001E
/* 000365 0x80AF6D14 */ .word	0x00000000
/* 000366 0x80AF6D18 */ .word	0x00000000
glabel D_80AF6D1C
/* 000367 0x80AF6D1C */ .word	0x04061FC0
/* 000368 0x80AF6D20 */ .word	0x04061FE0
/* 000369 0x80AF6D24 */ .word	0x04062000
/* 000370 0x80AF6D28 */ .word	0x04062040
/* 000371 0x80AF6D2C */ .word	0x04062020
glabel D_80AF6D30
/* 000372 0x80AF6D30 */ .word	0xFFFFFFFF
glabel D_80AF6D34
/* 000373 0x80AF6D34 */ .word	0x64C800FF
/* 000374 0x80AF6D38 */ .word	0x00000000
/* 000375 0x80AF6D3C */ .word	0x00000000
