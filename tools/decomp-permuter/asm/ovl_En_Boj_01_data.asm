.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Boj_01_InitVars
/* 000016 0x809C3DC0 */ .word	0x01180400
/* 000017 0x809C3DC4 */ .word	0x00000019
/* 000018 0x809C3DC8 */ .word	0x00010000
/* 000019 0x809C3DCC */ .word	0x00000314
/* 000020 0x809C3DD0 */ .word	EnBoj01_Init
/* 000021 0x809C3DD4 */ .word	EnBoj01_Destroy
/* 000022 0x809C3DD8 */ .word	EnBoj01_Update
/* 000023 0x809C3DDC */ .word	EnBoj01_Draw
