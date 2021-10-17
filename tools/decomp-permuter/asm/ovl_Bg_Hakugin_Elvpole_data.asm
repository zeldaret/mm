.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Hakugin_Elvpole_InitVars
/* 000264 0x80ABDC50 */ .word	0x01A30100
/* 000265 0x80ABDC54 */ .word	0x00000010
/* 000266 0x80ABDC58 */ .word	0x01900000
/* 000267 0x80ABDC5C */ .word	0x00000168
/* 000268 0x80ABDC60 */ .word	BgHakuginElvpole_Init
/* 000269 0x80ABDC64 */ .word	BgHakuginElvpole_Destroy
/* 000270 0x80ABDC68 */ .word	BgHakuginElvpole_Update
/* 000271 0x80ABDC6C */ .word	BgHakuginElvpole_Draw
