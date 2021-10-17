.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801C5C50
/* 295012 0x801C5C50 */ .word	func_801323D0
/* 295013 0x801C5C54 */ .word	func_80132428
/* 295014 0x801C5C58 */ .word	func_80132494
/* 295015 0x801C5C5C */ .word	func_801326B8
/* 295016 0x801C5C60 */ .word	func_801328F0
/* 295017 0x801C5C64 */ .word	func_80132920
/* 295018 0x801C5C68 */ .word	func_80132938
/* 295019 0x801C5C6C */ .word	func_80132954
/* 295020 0x801C5C70 */ .word	func_8013296C
/* 295021 0x801C5C74 */ .word	func_80132A18
/* 295022 0x801C5C78 */ .word	func_80132A3C
/* 295023 0x801C5C7C */ .word	func_80132A80
/* 295024 0x801C5C80 */ .word	func_80132AD8
/* 295025 0x801C5C84 */ .word	func_80132B24
/* 295026 0x801C5C88 */ .word	func_80132B84
/* 295027 0x801C5C8C */ .word	func_80132D70
/* 295028 0x801C5C90 */ .word	func_80132E9C
/* 295029 0x801C5C94 */ .word	func_80132FDC
/* 295030 0x801C5C98 */ .word	func_80133000
glabel D_801C5C9C
/* 295031 0x801C5C9C */ .word	0x04050607
/* 295032 0x801C5CA0 */ .word	0x03010104
/* 295033 0x801C5CA4 */ .word	0x03020405
/* 295034 0x801C5CA8 */ .word	0x04050604
/* 295035 0x801C5CAC */ .word	0x05020300
