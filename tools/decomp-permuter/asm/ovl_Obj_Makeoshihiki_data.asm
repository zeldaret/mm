.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Makeoshihiki_InitVars
/* 000184 0x80972630 */ .word	0x00CB0600
/* 000185 0x80972634 */ .word	0x00000010
/* 000186 0x80972638 */ .word	0x00010000
/* 000187 0x8097263C */ .word	0x0000014C
/* 000188 0x80972640 */ .word	ObjMakeoshihiki_Init
/* 000189 0x80972644 */ .word	func_800BDFB0
/* 000190 0x80972648 */ .word	ObjMakeoshihiki_Update
/* 000191 0x8097264C */ .word	0x00000000
