.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Demo_InitVars
/* 000220 0x80983890 */ .word	0x00D80600
/* 000221 0x80983894 */ .word	0x00000010
/* 000222 0x80983898 */ .word	0x00010000
/* 000223 0x8098389C */ .word	0x00000154
/* 000224 0x809838A0 */ .word	ObjDemo_Init
/* 000225 0x809838A4 */ .word	func_800BDFB0
/* 000226 0x809838A8 */ .word	ObjDemo_Update
/* 000227 0x809838AC */ .word	0x00000000
