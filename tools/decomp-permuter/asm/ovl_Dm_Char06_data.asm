.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Char06_InitVars
/* 000184 0x80AAE960 */ .word	0x01980700
/* 000185 0x80AAE964 */ .word	0x00000030
/* 000186 0x80AAE968 */ .word	0x01E60000
/* 000187 0x80AAE96C */ .word	0x000002A4
/* 000188 0x80AAE970 */ .word	DmChar06_Init
/* 000189 0x80AAE974 */ .word	DmChar06_Destroy
/* 000190 0x80AAE978 */ .word	DmChar06_Update
/* 000191 0x80AAE97C */ .word	DmChar06_Draw
