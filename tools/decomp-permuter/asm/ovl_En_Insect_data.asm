.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8091BD60
/* 001328 0x8091BD60 */ .word	0x00000000
glabel En_Insect_InitVars
/* 001329 0x8091BD64 */ .word	0x00160700
/* 001330 0x8091BD68 */ .word	0x00000000
/* 001331 0x8091BD6C */ .word	0x00010000
/* 001332 0x8091BD70 */ .word	0x00000318
/* 001333 0x8091BD74 */ .word	EnInsect_Init
/* 001334 0x8091BD78 */ .word	EnInsect_Destroy
/* 001335 0x8091BD7C */ .word	EnInsect_Update
/* 001336 0x8091BD80 */ .word	EnInsect_Draw
glabel D_8091BD84
/* 001337 0x8091BD84 */ .word	0x00000000
/* 001338 0x8091BD88 */ .word	0x00000000
/* 001339 0x8091BD8C */ .word	0x00000000
/* 001340 0x8091BD90 */ .word	0xF7CFFFFF
/* 001341 0x8091BD94 */ .word	0x00000000
/* 001342 0x8091BD98 */ .word	0x00000100
/* 001343 0x8091BD9C */ .word	0x00000000
/* 001344 0x8091BDA0 */ .word	0x00000000
/* 001345 0x8091BDA4 */ .word	0x00050064
glabel D_8091BDA8
/* 001346 0x8091BDA8 */ .word	0x0A000019
/* 001347 0x8091BDAC */ .word	0x10000000
/* 001348 0x8091BDB0 */ .word	0x00000001
/* 001349 0x8091BDB4 */ .word	D_8091BD84
glabel D_8091BDB8
/* 001350 0x8091BDB8 */ .word	0x00000005
glabel D_8091BDBC
/* 001351 0x8091BDBC */ .word	0xC858000A
/* 001352 0x8091BDC0 */ .word	0xB0FC02BC
/* 001353 0x8091BDC4 */ .word	0xB1000014
/* 001354 0x8091BDC8 */ .word	0x3104001E
glabel D_8091BDCC
/* 001355 0x8091BDCC */ .word	0x00000000
/* 001356 0x8091BDD0 */ .word	0x00000000
/* 001357 0x8091BDD4 */ .word	0x00000000
/* 001358 0x8091BDD8 */ .word	0x00000000
/* 001359 0x8091BDDC */ .word	0x00000000
