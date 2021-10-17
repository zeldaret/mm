.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Swprize_InitVars
/* 000284 0x80C257D0 */ .word	0x02AE0600
/* 000285 0x80C257D4 */ .word	0x00000010
/* 000286 0x80C257D8 */ .word	0x00010000
/* 000287 0x80C257DC */ .word	0x0000014C
/* 000288 0x80C257E0 */ .word	ObjSwprize_Init
/* 000289 0x80C257E4 */ .word	ObjSwprize_Destroy
/* 000290 0x80C257E8 */ .word	ObjSwprize_Update
/* 000291 0x80C257EC */ .word	0x00000000
glabel D_80C257F0
/* 000292 0x80C257F0 */ .word	0x00020014
glabel D_80C257F4
/* 000293 0x80C257F4 */ .word	0x00010008
glabel D_80C257F8
/* 000294 0x80C257F8 */ .word	0xF7780000
/* 000295 0x80C257FC */ .word	0x08880000
