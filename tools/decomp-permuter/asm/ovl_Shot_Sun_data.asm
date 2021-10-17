.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Shot_Sun_InitVars
/* 000336 0x80973B80 */ .word	0x00D00600
/* 000337 0x80973B84 */ .word	0x00000009
/* 000338 0x80973B88 */ .word	0x00010000
/* 000339 0x80973B8C */ .word	0x000001A0
/* 000340 0x80973B90 */ .word	ShotSun_Init
/* 000341 0x80973B94 */ .word	ShotSun_Destroy
/* 000342 0x80973B98 */ .word	ShotSun_Update
/* 000343 0x80973B9C */ .word	0x00000000
glabel D_80973BA0
/* 000344 0x80973BA0 */ .word	0x0A000939
/* 000345 0x80973BA4 */ .word	0x10010000
/* 000346 0x80973BA8 */ .word	0x00000000
/* 000347 0x80973BAC */ .word	0x00000000
/* 000348 0x80973BB0 */ .word	0x00000000
/* 000349 0x80973BB4 */ .word	0x00000020
/* 000350 0x80973BB8 */ .word	0x00000000
/* 000351 0x80973BBC */ .word	0x00010100
/* 000352 0x80973BC0 */ .word	0x001E003C
/* 000353 0x80973BC4 */ .word	0x00000000
/* 000354 0x80973BC8 */ .word	0x00000000
/* 000355 0x80973BCC */ .word	0x00000000
