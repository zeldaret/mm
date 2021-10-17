.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Snowwd_InitVars
/* 000268 0x80AF7A70 */ .word	0x01D40600
/* 000269 0x80AF7A74 */ .word	0x00000000
/* 000270 0x80AF7A78 */ .word	0x01B70000
/* 000271 0x80AF7A7C */ .word	0x00000198
/* 000272 0x80AF7A80 */ .word	EnSnowwd_Init
/* 000273 0x80AF7A84 */ .word	EnSnowwd_Destroy
/* 000274 0x80AF7A88 */ .word	EnSnowwd_Update
/* 000275 0x80AF7A8C */ .word	EnSnowwd_Draw
glabel D_80AF7A90
/* 000276 0x80AF7A90 */ .word	0x0D000D39
/* 000277 0x80AF7A94 */ .word	0x10010000
/* 000278 0x80AF7A98 */ .word	0x05000000
/* 000279 0x80AF7A9C */ .word	0x00000000
/* 000280 0x80AF7AA0 */ .word	0x00000000
/* 000281 0x80AF7AA4 */ .word	0x0100020A
/* 000282 0x80AF7AA8 */ .word	0x00000000
/* 000283 0x80AF7AAC */ .word	0x00010100
/* 000284 0x80AF7AB0 */ .word	0x0012003C
/* 000285 0x80AF7AB4 */ .word	0x00000000
/* 000286 0x80AF7AB8 */ .word	0x00000000
glabel D_80AF7ABC
/* 000287 0x80AF7ABC */ .word	0x00000000
/* 000288 0x80AF7AC0 */ .word	0x00000000
/* 000289 0x80AF7AC4 */ .word	0x00000000
glabel D_80AF7AC8
/* 000290 0x80AF7AC8 */ .word	0x00000000
/* 000291 0x80AF7ACC */ .word	0xC0800000
/* 000292 0x80AF7AD0 */ .word	0x00000000
glabel D_80AF7AD4
/* 000293 0x80AF7AD4 */ .word	0xFFFFFFFF
glabel D_80AF7AD8
/* 000294 0x80AF7AD8 */ .word	0xC8C8DC00
/* 000295 0x80AF7ADC */ .word	0x00000000
