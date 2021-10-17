.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Tokei_Turret_InitVars
/* 000120 0x80B91EA0 */ .word	0x02210100
/* 000121 0x80B91EA4 */ .word	0x00000000
/* 000122 0x80B91EA8 */ .word	0x02050000
/* 000123 0x80B91EAC */ .word	0x0000015C
/* 000124 0x80B91EB0 */ .word	ObjTokeiTurret_Init
/* 000125 0x80B91EB4 */ .word	ObjTokeiTurret_Destroy
/* 000126 0x80B91EB8 */ .word	ObjTokeiTurret_Update
/* 000127 0x80B91EBC */ .word	ObjTokeiTurret_Draw
glabel D_80B91EC0
/* 000128 0x80B91EC0 */ .word	0xB0FC04B0
/* 000129 0x80B91EC4 */ .word	0x48580064
/* 000130 0x80B91EC8 */ .word	0x00000000
/* 000131 0x80B91ECC */ .word	0x00000000
