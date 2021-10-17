.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Warpstone_InitVars
/* 000444 0x80B93200 */ .word	0x02230700
/* 000445 0x80B93204 */ .word	0x00000009
/* 000446 0x80B93208 */ .word	0x01700000
/* 000447 0x80B9320C */ .word	0x000001B0
/* 000448 0x80B93210 */ .word	ObjWarpstone_Init
/* 000449 0x80B93214 */ .word	ObjWarpstone_Destroy
/* 000450 0x80B93218 */ .word	ObjWarpstone_Update
/* 000451 0x80B9321C */ .word	ObjWarpstone_Draw
glabel D_80B93220
/* 000452 0x80B93220 */ .word	0x09000D39
/* 000453 0x80B93224 */ .word	0x20010000
/* 000454 0x80B93228 */ .word	0x02000000
/* 000455 0x80B9322C */ .word	0x00100000
/* 000456 0x80B93230 */ .word	0x00000000
/* 000457 0x80B93234 */ .word	0x01000202
/* 000458 0x80B93238 */ .word	0x00000000
/* 000459 0x80B9323C */ .word	0x00050100
/* 000460 0x80B93240 */ .word	0x0014003C
/* 000461 0x80B93244 */ .word	0x00000000
/* 000462 0x80B93248 */ .word	0x00000000
glabel D_80B9324C
/* 000463 0x80B9324C */ .word	0x001F0001
glabel D_80B93250
/* 000464 0x80B93250 */ .word	0x060001D0
/* 000465 0x80B93254 */ .word	0x06003770
/* 000466 0x80B93258 */ .word	0x00000000
/* 000467 0x80B9325C */ .word	0x00000000
