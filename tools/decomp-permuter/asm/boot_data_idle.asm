.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80096B20
/* 023216 0x80096B20 */ .word	0x01000000
glabel gViConfigUseDefault
/* 023217 0x80096B24 */ .word	0x01000000
glabel gViConfigAdditionalScanLines
/* 023218 0x80096B28 */ .word	0x00000000
glabel gViConfigFeatures
/* 023219 0x80096B2C */ .word	0x00000042
glabel gViConfigXScale
/* 023220 0x80096B30 */ .word	0x3F800000
glabel gViConfigYScale
/* 023221 0x80096B34 */ .word	0x3F800000
/* 023222 0x80096B38 */ .word	0x00000000
/* 023223 0x80096B3C */ .word	0x00000000
