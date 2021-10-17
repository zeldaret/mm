.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Keikoku_Spr_InitVars
/* 000084 0x808C3BA0 */ .word	0x003F0600
/* 000085 0x808C3BA4 */ .word	0x00000000
/* 000086 0x808C3BA8 */ .word	0x017E0000
/* 000087 0x808C3BAC */ .word	0x00000144
/* 000088 0x808C3BB0 */ .word	BgKeikokuSpr_Init
/* 000089 0x808C3BB4 */ .word	BgKeikokuSpr_Destroy
/* 000090 0x808C3BB8 */ .word	BgKeikokuSpr_Update
/* 000091 0x808C3BBC */ .word	BgKeikokuSpr_Draw
glabel D_808C3BC0
/* 000092 0x808C3BC0 */ .word	0xB0FC0BB8
/* 000093 0x808C3BC4 */ .word	0xB10000C8
/* 000094 0x808C3BC8 */ .word	0xB1040190
/* 000095 0x808C3BCC */ .word	0x48580014
