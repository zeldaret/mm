.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Boyo_InitVars
/* 000272 0x809A6150 */ .word	0x01060600
/* 000273 0x809A6154 */ .word	0x00000010
/* 000274 0x809A6158 */ .word	0x014F0000
/* 000275 0x809A615C */ .word	0x000001B0
/* 000276 0x809A6160 */ .word	ObjBoyo_Init
/* 000277 0x809A6164 */ .word	ObjBoyo_Destroy
/* 000278 0x809A6168 */ .word	ObjBoyo_Update
/* 000279 0x809A616C */ .word	ObjBoyo_Draw
glabel D_809A6170
/* 000280 0x809A6170 */ .word	0x0A000D39
/* 000281 0x809A6174 */ .word	0x20010000
/* 000282 0x809A6178 */ .word	0x00000000
/* 000283 0x809A617C */ .word	0x00000000
/* 000284 0x809A6180 */ .word	0x00000000
/* 000285 0x809A6184 */ .word	0x01CBFFBE
/* 000286 0x809A6188 */ .word	0x00000000
/* 000287 0x809A618C */ .word	0x00010100
/* 000288 0x809A6190 */ .word	0x003C008C
/* 000289 0x809A6194 */ .word	0x00000000
/* 000290 0x809A6198 */ .word	0x00000000
glabel D_809A619C
/* 000291 0x809A619C */ .word	0xB0FC0FA0
/* 000292 0x809A61A0 */ .word	0xB100012C
/* 000293 0x809A61A4 */ .word	0xB104012C
/* 000294 0x809A61A8 */ .word	0x48580064
/* 000295 0x809A61AC */ .word	0x00000000
glabel D_809A61B0
/* 000296 0x809A61B0 */ .word	func_809A5DC0
glabel D_809A61B4
/* 000297 0x809A61B4 */ .word	0x021D0000
/* 000298 0x809A61B8 */ .word	func_809A5DE0
/* 000299 0x809A61BC */ .word	0x00090000
/* 000300 0x809A61C0 */ .word	func_809A5E14
/* 000301 0x809A61C4 */ .word	0x00000000
/* 000302 0x809A61C8 */ .word	0x00000000
/* 000303 0x809A61CC */ .word	0x00000000
