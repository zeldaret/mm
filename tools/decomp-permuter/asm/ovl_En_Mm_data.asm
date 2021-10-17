.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Mm_InitVars
/* 000476 0x80966320 */ .word	0x00B90700
/* 000477 0x80966324 */ .word	0x00000010
/* 000478 0x80966328 */ .word	0x00010000
/* 000479 0x8096632C */ .word	0x00000198
/* 000480 0x80966330 */ .word	EnMm_Init
/* 000481 0x80966334 */ .word	EnMm_Destroy
/* 000482 0x80966338 */ .word	EnMm_Update
/* 000483 0x8096633C */ .word	EnMm_Draw
glabel D_80966340
/* 000484 0x80966340 */ .word	0x09000039
/* 000485 0x80966344 */ .word	0x20010000
/* 000486 0x80966348 */ .word	0x02000000
/* 000487 0x8096634C */ .word	0x00100000
/* 000488 0x80966350 */ .word	0x00000000
/* 000489 0x80966354 */ .word	0x01000202
/* 000490 0x80966358 */ .word	0x00000000
/* 000491 0x8096635C */ .word	0x00000100
/* 000492 0x80966360 */ .word	0x0006001E
/* 000493 0x80966364 */ .word	0x00000000
/* 000494 0x80966368 */ .word	0x00000000
glabel D_8096636C
/* 000495 0x8096636C */ .word	0xB874FB50
/* 000496 0x80966370 */ .word	0x4858010E
/* 000497 0x80966374 */ .word	0x00000000
/* 000498 0x80966378 */ .word	0x00000000
/* 000499 0x8096637C */ .word	0x00000000
