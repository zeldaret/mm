.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Eff_Change_InitVars
/* 000284 0x80A4C900 */ .word	0x01600700
/* 000285 0x80A4C904 */ .word	0x00000010
/* 000286 0x80A4C908 */ .word	0x00010000
/* 000287 0x80A4C90C */ .word	0x000001CC
/* 000288 0x80A4C910 */ .word	EffChange_Init
/* 000289 0x80A4C914 */ .word	EffChange_Destroy
/* 000290 0x80A4C918 */ .word	EffChange_Update
/* 000291 0x80A4C91C */ .word	0x00000000
glabel D_80A4C920
/* 000292 0x80A4C920 */ .word	0xFFFFAA00
/* 000293 0x80A4C924 */ .word	0x6400FFFF
/* 000294 0x80A4C928 */ .word	0xAAC80000
/* 000295 0x80A4C92C */ .word	0xAAFFFF00
/* 000296 0x80A4C930 */ .word	0x64FFFFFF
/* 000297 0x80A4C934 */ .word	0xAAC89600
/* 000298 0x80A4C938 */ .word	0xFFFFAA00
/* 000299 0x80A4C93C */ .word	0x6400FFFF
/* 000300 0x80A4C940 */ .word	0xAA006400
/* 000301 0x80A4C944 */ .word	0xFFFFAA00
/* 000302 0x80A4C948 */ .word	0x6400FFFF
/* 000303 0x80A4C94C */ .word	0xAA006400
