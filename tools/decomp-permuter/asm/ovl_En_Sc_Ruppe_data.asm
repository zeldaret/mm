.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Sc_Ruppe_InitVars
/* 000312 0x80BD6DF0 */ .word	0x025A0400
/* 000313 0x80BD6DF4 */ .word	0x00000030
/* 000314 0x80BD6DF8 */ .word	0x00010000
/* 000315 0x80BD6DFC */ .word	0x00000198
/* 000316 0x80BD6E00 */ .word	EnScRuppe_Init
/* 000317 0x80BD6E04 */ .word	EnScRuppe_Destroy
/* 000318 0x80BD6E08 */ .word	EnScRuppe_Update
/* 000319 0x80BD6E0C */ .word	EnScRuppe_Draw
glabel D_80BD6E10
/* 000320 0x80BD6E10 */ .word	0x04061FC0
glabel D_80BD6E14
/* 000321 0x80BD6E14 */ .word	0x00010000
/* 000322 0x80BD6E18 */ .word	0x04061FE0
/* 000323 0x80BD6E1C */ .word	0x00050000
/* 000324 0x80BD6E20 */ .word	0x04062000
/* 000325 0x80BD6E24 */ .word	0x00140000
/* 000326 0x80BD6E28 */ .word	0x04062040
/* 000327 0x80BD6E2C */ .word	0x00C80000
/* 000328 0x80BD6E30 */ .word	0x04062020
/* 000329 0x80BD6E34 */ .word	0x00320000
/* 000330 0x80BD6E38 */ .word	0x04062060
/* 000331 0x80BD6E3C */ .word	0x000A0000
glabel D_80BD6E40
/* 000332 0x80BD6E40 */ .word	0x0A00000D
/* 000333 0x80BD6E44 */ .word	0x20010000
/* 000334 0x80BD6E48 */ .word	0x04000000
/* 000335 0x80BD6E4C */ .word	0x00000000
/* 000336 0x80BD6E50 */ .word	0x00000000
/* 000337 0x80BD6E54 */ .word	0x00000000
/* 000338 0x80BD6E58 */ .word	0x00000000
/* 000339 0x80BD6E5C */ .word	0x00000100
/* 000340 0x80BD6E60 */ .word	0x000A001E
/* 000341 0x80BD6E64 */ .word	0x00000000
/* 000342 0x80BD6E68 */ .word	0x00000000
/* 000343 0x80BD6E6C */ .word	0x00000000
