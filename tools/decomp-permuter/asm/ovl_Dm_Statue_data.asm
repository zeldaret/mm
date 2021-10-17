.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Statue_InitVars
/* 000036 0x80A4CA40 */ .word	0x01610700
/* 000037 0x80A4CA44 */ .word	0x04000030
/* 000038 0x80A4CA48 */ .word	0x026C0000
/* 000039 0x80A4CA4C */ .word	0x00000194
/* 000040 0x80A4CA50 */ .word	DmStatue_Init
/* 000041 0x80A4CA54 */ .word	DmStatue_Destroy
/* 000042 0x80A4CA58 */ .word	DmStatue_Update
/* 000043 0x80A4CA5C */ .word	DmStatue_Draw
