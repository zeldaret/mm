.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Mbar_Chair_InitVars
/* 000052 0x80B7EA00 */ .word	0x02170100
/* 000053 0x80B7EA04 */ .word	0x00000000
/* 000054 0x80B7EA08 */ .word	0x02020000
/* 000055 0x80B7EA0C */ .word	0x0000015C
/* 000056 0x80B7EA10 */ .word	BgMbarChair_Init
/* 000057 0x80B7EA14 */ .word	BgMbarChair_Destroy
/* 000058 0x80B7EA18 */ .word	BgMbarChair_Update
/* 000059 0x80B7EA1C */ .word	BgMbarChair_Draw
glabel bgMbarChairInitVars
/* 000060 0x80B7EA20 */ .word	0xB0FC07D0
/* 000061 0x80B7EA24 */ .word	0xB100003C
/* 000062 0x80B7EA28 */ .word	0xB1040050
/* 000063 0x80B7EA2C */ .word	0x48580064
