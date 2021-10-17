.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Yado_InitVars
/* 000136 0x80C16400 */ .word	0x02940100
/* 000137 0x80C16404 */ .word	0x00000030
/* 000138 0x80C16408 */ .word	0x026E0000
/* 000139 0x80C1640C */ .word	0x00000148
/* 000140 0x80C16410 */ .word	ObjYado_Init
/* 000141 0x80C16414 */ .word	ObjYado_Destroy
/* 000142 0x80C16418 */ .word	ObjYado_Update
/* 000143 0x80C1641C */ .word	ObjYado_Draw
glabel D_80C16420
/* 000144 0x80C16420 */ .word	0x48580064
/* 000145 0x80C16424 */ .word	0x00000000
/* 000146 0x80C16428 */ .word	0x00000000
/* 000147 0x80C1642C */ .word	0x00000000
glabel objYadoOverlayInfo
/* 000148 0x80C16430 */ .word	0x00000220
/* 000149 0x80C16434 */ .word	0x00000030
/* 000150 0x80C16438 */ .word	0x00000000
/* 000151 0x80C1643C */ .word	0x00000010
/* 000152 0x80C16440 */ .word	0x0000000A
glabel objYadoOverlayRelocations
/* 000153 0x80C16444 */ .word	0x45000010
/* 000154 0x80C16448 */ .word	0x46000014
/* 000155 0x80C1644C */ .word	0x45000038
/* 000156 0x80C16450 */ .word	0x4600003C
/* 000157 0x80C16454 */ .word	0x450001D0
/* 000158 0x80C16458 */ .word	0x460001D4
/* 000159 0x80C1645C */ .word	0x82000010
/* 000160 0x80C16460 */ .word	0x82000014
/* 000161 0x80C16464 */ .word	0x82000018
/* 000162 0x80C16468 */ .word	0x8200001C
glabel objYadoOverlayInfoOffset
/* 000163 0x80C1646C */ .word	0x00000040
