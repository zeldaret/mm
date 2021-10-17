.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Tree_InitVars
/* 000296 0x80B9A550 */ .word	0x02290600
/* 000297 0x80B9A554 */ .word	0x02000000
/* 000298 0x80B9A558 */ .word	0x020D0000
/* 000299 0x80B9A55C */ .word	0x000001B8
/* 000300 0x80B9A560 */ .word	ObjTree_Init
/* 000301 0x80B9A564 */ .word	ObjTree_Destroy
/* 000302 0x80B9A568 */ .word	ObjTree_Update
/* 000303 0x80B9A56C */ .word	ObjTree_Draw
glabel D_80B9A570
/* 000304 0x80B9A570 */ .word	0x0D000939
/* 000305 0x80B9A574 */ .word	0x10010000
/* 000306 0x80B9A578 */ .word	0x01000000
/* 000307 0x80B9A57C */ .word	0x00000000
/* 000308 0x80B9A580 */ .word	0x00000000
/* 000309 0x80B9A584 */ .word	0x0100020A
/* 000310 0x80B9A588 */ .word	0x00000000
/* 000311 0x80B9A58C */ .word	0x00010100
/* 000312 0x80B9A590 */ .word	0x001C0078
/* 000313 0x80B9A594 */ .word	0x00000000
/* 000314 0x80B9A598 */ .word	0x00000000
glabel D_80B9A59C
/* 000315 0x80B9A59C */ .word	0x00F00000
/* 000316 0x80B9A5A0 */ .word	0x0000F210
/* 000317 0x80B9A5A4 */ .word	0xF2F1F100
/* 000318 0x80B9A5A8 */ .word	0x0000F110
/* 000319 0x80B9A5AC */ .word	0x00000000
/* 000320 0x80B9A5B0 */ .word	0x0000F000
/* 000321 0x80B9A5B4 */ .word	0xF1000000
/* 000322 0x80B9A5B8 */ .word	0x00000000
glabel D_80B9A5BC
/* 000323 0x80B9A5BC */ .word	0x08000000
/* 000324 0x80B9A5C0 */ .word	0x00000000
/* 000325 0x80B9A5C4 */ .word	0xFE000000
/* 000326 0x80B9A5C8 */ .word	0x00000000
/* 000327 0x80B9A5CC */ .word	0x00000000
