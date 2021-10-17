.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Opstage_InitVars
/* 000240 0x80A9FD10 */ .word	0x01900700
/* 000241 0x80A9FD14 */ .word	0x00000030
/* 000242 0x80A9FD18 */ .word	0x01690000
/* 000243 0x80A9FD1C */ .word	0x000001B0
/* 000244 0x80A9FD20 */ .word	DmOpstage_Init
/* 000245 0x80A9FD24 */ .word	DmOpstage_Destroy
/* 000246 0x80A9FD28 */ .word	DmOpstage_Update
/* 000247 0x80A9FD2C */ .word	DmOpstage_Draw
glabel D_80A9FD30
/* 000248 0x80A9FD30 */ .word	0x3100012C
/* 000249 0x80A9FD34 */ .word	0x00000000
/* 000250 0x80A9FD38 */ .word	0x00000000
/* 000251 0x80A9FD3C */ .word	0x00000000
