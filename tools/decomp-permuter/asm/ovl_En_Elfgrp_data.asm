.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Elfgrp_InitVars
/* 001288 0x80A3AAD0 */ .word	0x01530600
/* 001289 0x80A3AAD4 */ .word	0x00000010
/* 001290 0x80A3AAD8 */ .word	0x00010000
/* 001291 0x80A3AADC */ .word	0x00000150
/* 001292 0x80A3AAE0 */ .word	EnElfgrp_Init
/* 001293 0x80A3AAE4 */ .word	EnElfgrp_Destroy
/* 001294 0x80A3AAE8 */ .word	EnElfgrp_Update
/* 001295 0x80A3AAEC */ .word	0x00000000
