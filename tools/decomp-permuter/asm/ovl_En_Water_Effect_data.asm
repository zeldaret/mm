.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Water_Effect_InitVars
/* 002556 0x80A5AF90 */ .word	0x01700900
/* 002557 0x80A5AF94 */ .word	0x00000035
/* 002558 0x80A5AF98 */ .word	0x01820000
/* 002559 0x80A5AF9C */ .word	0x00000E3C
/* 002560 0x80A5AFA0 */ .word	EnWaterEffect_Init
/* 002561 0x80A5AFA4 */ .word	EnWaterEffect_Destroy
/* 002562 0x80A5AFA8 */ .word	EnWaterEffect_Update
/* 002563 0x80A5AFAC */ .word	EnWaterEffect_Draw
glabel D_80A5AFB0
/* 002564 0x80A5AFB0 */ .word	0x00000000
/* 002565 0x80A5AFB4 */ .word	0x00000000
/* 002566 0x80A5AFB8 */ .word	0x00000000
glabel D_80A5AFBC
/* 002567 0x80A5AFBC */ .word	0x00000000
/* 002568 0x80A5AFC0 */ .word	0xBF800000
/* 002569 0x80A5AFC4 */ .word	0x00000000
/* 002570 0x80A5AFC8 */ .word	0x00000000
/* 002571 0x80A5AFCC */ .word	0x00000000
