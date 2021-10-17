.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D0B70
/* 306220 0x801D0B70 */ .word	0x00000000
/* 306221 0x801D0B74 */ .word	0x00C90550
/* 306222 0x801D0B78 */ .word	0x00CA7F00
/* 306223 0x801D0B7C */ .word	func_808160A0
/* 306224 0x801D0B80 */ .word	func_8082DA90
/* 306225 0x801D0B84 */ .word	0x00000000
/* 306226 0x801D0B88 */ .word	D_801DF9C0
glabel D_801D0B8C
/* 306227 0x801D0B8C */ .word	0x00000000
/* 306228 0x801D0B90 */ .word	0x00CA7F00
/* 306229 0x801D0B94 */ .word	0x00CDCF60
/* 306230 0x801D0B98 */ .word	func_8082DA90
/* 306231 0x801D0B9C */ .word	func_80862B70
/* 306232 0x801D0BA0 */ .word	0x00000000
/* 306233 0x801D0BA4 */ .word	D_801DF9D0
glabel D_801D0BA8
/* 306234 0x801D0BA8 */ .word	0x00000000
glabel D_801D0BAC
/* 306235 0x801D0BAC */ .word	0x00000000
