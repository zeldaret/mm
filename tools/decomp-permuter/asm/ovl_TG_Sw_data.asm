.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel TG_Sw_InitVars
/* 000240 0x80B1A320 */ .word	0x01E70600
/* 000241 0x80B1A324 */ .word	0x00000010
/* 000242 0x80B1A328 */ .word	0x00010000
/* 000243 0x80B1A32C */ .word	0x00000148
/* 000244 0x80B1A330 */ .word	TGSw_Init
/* 000245 0x80B1A334 */ .word	TGSw_Destroy
/* 000246 0x80B1A338 */ .word	TGSw_Update
/* 000247 0x80B1A33C */ .word	TGSw_Draw
