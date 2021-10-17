.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D0C80
/* 306288 0x801D0C80 */ .word	0xE7000000
/* 306289 0x801D0C84 */ .word	0x00000000
/* 306290 0x801D0C88 */ .word	0xD7000002
/* 306291 0x801D0C8C */ .word	0x80008000
/* 306292 0x801D0C90 */ .word	0xD9000000
/* 306293 0x801D0C94 */ .word	0x00000000
/* 306294 0x801D0C98 */ .word	0xFCFFFFFF
/* 306295 0x801D0C9C */ .word	0xFFFCF87C
/* 306296 0x801D0CA0 */ .word	0xEF882C30
/* 306297 0x801D0CA4 */ .word	0x00552048
/* 306298 0x801D0CA8 */ .word	0xDF000000
/* 306299 0x801D0CAC */ .word	0x00000000
glabel D_801D0CB0
/* 306300 0x801D0CB0 */ .word	0xE7000000
/* 306301 0x801D0CB4 */ .word	0x00000000
/* 306302 0x801D0CB8 */ .word	0xD9C0F9FA
/* 306303 0x801D0CBC */ .word	0x00000000
/* 306304 0x801D0CC0 */ .word	0xEF802C50
/* 306305 0x801D0CC4 */ .word	0x00504340
/* 306306 0x801D0CC8 */ .word	0xFCFFFFFF
/* 306307 0x801D0CCC */ .word	0xFFFDF6FB
/* 306308 0x801D0CD0 */ .word	0xDF000000
/* 306309 0x801D0CD4 */ .word	0x00000000
glabel D_801D0CD8
/* 306310 0x801D0CD8 */ .word	func_8016482C
/* 306311 0x801D0CDC */ .word	func_80164858
/* 306312 0x801D0CE0 */ .word	func_80164864
/* 306313 0x801D0CE4 */ .word	func_801649F4
/* 306314 0x801D0CE8 */ .word	func_801647D0
/* 306315 0x801D0CEC */ .word	func_80164A98
/* 306316 0x801D0CF0 */ .word	func_80164A8C
/* 306317 0x801D0CF4 */ .word	0x00000000
/* 306318 0x801D0CF8 */ .word	func_80164A80
/* 306319 0x801D0CFC */ .word	0x00000000
