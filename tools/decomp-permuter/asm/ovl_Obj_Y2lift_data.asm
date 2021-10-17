.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Y2lift_InitVars
/* 000180 0x80B9A920 */ .word	0x022A0100
/* 000181 0x80B9A924 */ .word	0x00000010
/* 000182 0x80B9A928 */ .word	0x020E0000
/* 000183 0x80B9A92C */ .word	0x00000160
/* 000184 0x80B9A930 */ .word	ObjY2lift_Init
/* 000185 0x80B9A934 */ .word	ObjY2lift_Destroy
/* 000186 0x80B9A938 */ .word	ObjY2lift_Update
/* 000187 0x80B9A93C */ .word	ObjY2lift_Draw
glabel D_80B9A940
/* 000188 0x80B9A940 */ .word	0xC8580064
/* 000189 0x80B9A944 */ .word	0xB0FC0FA0
/* 000190 0x80B9A948 */ .word	0xB1000320
/* 000191 0x80B9A94C */ .word	0x31040320
