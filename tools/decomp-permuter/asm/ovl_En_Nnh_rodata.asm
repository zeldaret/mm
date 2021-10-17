.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enNnhOverlayInfo
/* 000180 0x80C08A30 */ .word	0x00000280
/* 000181 0x80C08A34 */ .word	0x00000050
/* 000182 0x80C08A38 */ .word	0x00000000
/* 000183 0x80C08A3C */ .word	0x00000000
/* 000184 0x80C08A40 */ .word	0x0000000D
glabel enNnhOverlayRelocations
/* 000185 0x80C08A44 */ .word	0x45000034
/* 000186 0x80C08A48 */ .word	0x4600003C
/* 000187 0x80C08A4C */ .word	0x44000080
/* 000188 0x80C08A50 */ .word	0x450000C8
/* 000189 0x80C08A54 */ .word	0x460000CC
/* 000190 0x80C08A58 */ .word	0x44000114
/* 000191 0x80C08A5C */ .word	0x45000144
/* 000192 0x80C08A60 */ .word	0x46000148
/* 000193 0x80C08A64 */ .word	0x44000174
/* 000194 0x80C08A68 */ .word	0x82000010
/* 000195 0x80C08A6C */ .word	0x82000014
/* 000196 0x80C08A70 */ .word	0x82000018
/* 000197 0x80C08A74 */ .word	0x8200001C
/* 000198 0x80C08A78 */ .word	0x00000000
glabel enNnhOverlayInfoOffset
/* 000199 0x80C08A7C */ .word	0x00000050
