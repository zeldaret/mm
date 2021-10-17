.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Onpuman_InitVars
/* 000324 0x80B12370 */ .word	0x01DF0400
/* 000325 0x80B12374 */ .word	0x00000009
/* 000326 0x80B12378 */ .word	0x00010000
/* 000327 0x80B1237C */ .word	0x000002AC
/* 000328 0x80B12380 */ .word	EnOnpuman_Init
/* 000329 0x80B12384 */ .word	EnOnpuman_Destroy
/* 000330 0x80B12388 */ .word	EnOnpuman_Update
/* 000331 0x80B1238C */ .word	0x00000000
glabel D_80B12390
/* 000332 0x80B12390 */ .word	0x0A000939
/* 000333 0x80B12394 */ .word	0x10010000
/* 000334 0x80B12398 */ .word	0x00000000
/* 000335 0x80B1239C */ .word	0x00000000
/* 000336 0x80B123A0 */ .word	0x00000000
/* 000337 0x80B123A4 */ .word	0x00000000
/* 000338 0x80B123A8 */ .word	0x00000000
/* 000339 0x80B123AC */ .word	0x00010100
/* 000340 0x80B123B0 */ .word	0x001E0028
/* 000341 0x80B123B4 */ .word	0x00000000
/* 000342 0x80B123B8 */ .word	0x00000000
/* 000343 0x80B123BC */ .word	0x00000000
