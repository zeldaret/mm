.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Object_Kankyo_InitVars
/* 002344 0x808DE320 */ .word	0x00510700
/* 002345 0x808DE324 */ .word	0x02000030
/* 002346 0x808DE328 */ .word	0x00010000
/* 002347 0x808DE32C */ .word	0x00001154
/* 002348 0x808DE330 */ .word	ObjectKankyo_Init
/* 002349 0x808DE334 */ .word	ObjectKankyo_Destroy
/* 002350 0x808DE338 */ .word	ObjectKankyo_Update
/* 002351 0x808DE33C */ .word	ObjectKankyo_Draw
glabel D_808DE340
/* 002352 0x808DE340 */ .word	0x00000000
/* 002353 0x808DE344 */ .word	0x00000000
/* 002354 0x808DE348 */ .word	0x00000000
/* 002355 0x808DE34C */ .word	0x00000000
