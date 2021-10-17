.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D0D00
/* 306320 0x801D0D00 */ .word	0xE7000000
/* 306321 0x801D0D04 */ .word	0x00000000
/* 306322 0x801D0D08 */ .word	0xEF002CF0
/* 306323 0x801D0D0C */ .word	0x0342524D
/* 306324 0x801D0D10 */ .word	0xFA0000FF
/* 306325 0x801D0D14 */ .word	0x00000001
/* 306326 0x801D0D18 */ .word	0xF9000000
/* 306327 0x801D0D1C */ .word	0x00000001
/* 306328 0x801D0D20 */ .word	0xDF000000
/* 306329 0x801D0D24 */ .word	0x00000000
glabel D_801D0D28
/* 306330 0x801D0D28 */ .word	func_80164B40
/* 306331 0x801D0D2C */ .word	func_80164B94
/* 306332 0x801D0D30 */ .word	func_80164BA0
/* 306333 0x801D0D34 */ .word	func_80165044
/* 306334 0x801D0D38 */ .word	func_80164AF0
/* 306335 0x801D0D3C */ .word	func_80164BE0
/* 306336 0x801D0D40 */ .word	func_80164BD4
/* 306337 0x801D0D44 */ .word	0x00000000
/* 306338 0x801D0D48 */ .word	func_80165198
/* 306339 0x801D0D4C */ .word	0x00000000
