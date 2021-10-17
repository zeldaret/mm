.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Ravine_InitVars
/* 000092 0x80A2E910 */ .word	0x01480700
/* 000093 0x80A2E914 */ .word	0x00000030
/* 000094 0x80A2E918 */ .word	0x01690000
/* 000095 0x80A2E91C */ .word	0x0000014C
/* 000096 0x80A2E920 */ .word	DmRavine_Init
/* 000097 0x80A2E924 */ .word	DmRavine_Destroy
/* 000098 0x80A2E928 */ .word	DmRavine_Update
/* 000099 0x80A2E92C */ .word	DmRavine_Draw
