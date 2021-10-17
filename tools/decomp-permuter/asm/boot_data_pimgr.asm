.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel __osPiDevMgr
/* 024452 0x80097E70 */ .word	0x00000000
/* 024453 0x80097E74 */ .word	0x00000000
/* 024454 0x80097E78 */ .word	0x00000000
/* 024455 0x80097E7C */ .word	0x00000000
/* 024456 0x80097E80 */ .word	0x00000000
/* 024457 0x80097E84 */ .word	0x00000000
/* 024458 0x80097E88 */ .word	0x00000000
glabel __osPiTable
/* 024459 0x80097E8C */ .word	0x00000000
glabel D_80097E90
/* 024460 0x80097E90 */ .word	D_8009D130
/* 024461 0x80097E94 */ .word	D_8009D1A8
/* 024462 0x80097E98 */ .word	0x00000000
/* 024463 0x80097E9C */ .word	0x00000000
