.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBoj02OverlayInfo
/* 000024 0x809C3E70 */ .word	0x00000040
/* 000025 0x809C3E74 */ .word	0x00000020
/* 000026 0x809C3E78 */ .word	0x00000000
/* 000027 0x809C3E7C */ .word	0x00000000
/* 000028 0x809C3E80 */ .word	0x00000004
glabel enBoj02OverlayRelocations
/* 000029 0x809C3E84 */ .word	0x82000010
/* 000030 0x809C3E88 */ .word	0x82000014
/* 000031 0x809C3E8C */ .word	0x82000018
/* 000032 0x809C3E90 */ .word	0x8200001C
/* 000033 0x809C3E94 */ .word	0x00000000
/* 000034 0x809C3E98 */ .word	0x00000000
glabel enBoj02OverlayInfoOffset
/* 000035 0x809C3E9C */ .word	0x00000030
