.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Bu_InitVars
/* 000080 0x809ACED0 */ .word	0x01110500
/* 000081 0x809ACED4 */ .word	0x00000001
/* 000082 0x809ACED8 */ .word	0x00010000
/* 000083 0x809ACEDC */ .word	0x00000190
/* 000084 0x809ACEE0 */ .word	EnBu_Init
/* 000085 0x809ACEE4 */ .word	EnBu_Destroy
/* 000086 0x809ACEE8 */ .word	EnBu_Update
/* 000087 0x809ACEEC */ .word	EnBu_Draw
