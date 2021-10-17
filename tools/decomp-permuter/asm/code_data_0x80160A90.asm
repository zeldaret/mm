.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Player_InitVars
/* 306212 0x801D0B50 */ .word	0x00000200
/* 306213 0x801D0B54 */ .word	0x86200039
/* 306214 0x801D0B58 */ .word	0x00010000
/* 306215 0x801D0B5C */ .word	0x00000D78
/* 306216 0x801D0B60 */ .word	func_80160AF8
/* 306217 0x801D0B64 */ .word	func_80160B40
/* 306218 0x801D0B68 */ .word	func_80160B80
/* 306219 0x801D0B6C */ .word	func_80160BC0
