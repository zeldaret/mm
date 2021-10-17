.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ladder_InitVars
/* 000268 0x80A4DE20 */ .word	0x01630600
/* 000269 0x80A4DE24 */ .word	0x00000010
/* 000270 0x80A4DE28 */ .word	0x01790000
/* 000271 0x80A4DE2C */ .word	0x00000164
/* 000272 0x80A4DE30 */ .word	BgLadder_Init
/* 000273 0x80A4DE34 */ .word	BgLadder_Destroy
/* 000274 0x80A4DE38 */ .word	BgLadder_Update
/* 000275 0x80A4DE3C */ .word	BgLadder_Draw
glabel D_80A4DE40
/* 000276 0x80A4DE40 */ .word	0x48580064
glabel D_80A4DE44
/* 000277 0x80A4DE44 */ .word	0x060000A0
/* 000278 0x80A4DE48 */ .word	0x060002D0
/* 000279 0x80A4DE4C */ .word	0x06000500
/* 000280 0x80A4DE50 */ .word	0x06000730
/* 000281 0x80A4DE54 */ .word	0x00000000
/* 000282 0x80A4DE58 */ .word	0x00000000
/* 000283 0x80A4DE5C */ .word	0x00000000
