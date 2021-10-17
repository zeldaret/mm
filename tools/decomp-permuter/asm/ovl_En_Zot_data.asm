.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Zot_InitVars
/* 003260 0x80B998C0 */ .word	0x02280400
/* 003261 0x80B998C4 */ .word	0x00000019
/* 003262 0x80B998C8 */ .word	0x00D00000
/* 003263 0x80B998CC */ .word	0x000002FC
/* 003264 0x80B998D0 */ .word	EnZot_Init
/* 003265 0x80B998D4 */ .word	EnZot_Destroy
/* 003266 0x80B998D8 */ .word	EnZot_Update
/* 003267 0x80B998DC */ .word	EnZot_Draw
glabel D_80B998E0
/* 003268 0x80B998E0 */ .word	0x0A001139
/* 003269 0x80B998E4 */ .word	0x10010000
/* 003270 0x80B998E8 */ .word	0x00000000
/* 003271 0x80B998EC */ .word	0x00000000
/* 003272 0x80B998F0 */ .word	0x00000000
/* 003273 0x80B998F4 */ .word	0xF7CFFFFF
/* 003274 0x80B998F8 */ .word	0x00000000
/* 003275 0x80B998FC */ .word	0x00010100
/* 003276 0x80B99900 */ .word	0x001E0028
/* 003277 0x80B99904 */ .word	0x00000000
/* 003278 0x80B99908 */ .word	0x00000000
glabel D_80B9990C
/* 003279 0x80B9990C */ .word	0x0600DE20
/* 003280 0x80B99910 */ .word	0x06002898
/* 003281 0x80B99914 */ .word	0x0600F4E8
/* 003282 0x80B99918 */ .word	0x0600E400
/* 003283 0x80B9991C */ .word	0x0600FDF0
/* 003284 0x80B99920 */ .word	0x06010B18
/* 003285 0x80B99924 */ .word	0x06011424
/* 003286 0x80B99928 */ .word	0x0600EDF0
/* 003287 0x80B9992C */ .word	0x0600DF54
/* 003288 0x80B99930 */ .word	0x0600DF54
glabel D_80B99934
/* 003289 0x80B99934 */ .word	0x43C80000
/* 003290 0x80B99938 */ .word	0x00000000
/* 003291 0x80B9993C */ .word	0x00000000
glabel D_80B99940
/* 003292 0x80B99940 */ .word	0x060050A0
/* 003293 0x80B99944 */ .word	0x060058A0
/* 003294 0x80B99948 */ .word	0x060060A0
/* 003295 0x80B9994C */ .word	0x00000000
