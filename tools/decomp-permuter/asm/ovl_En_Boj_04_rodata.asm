.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBoj04OverlayInfo
/* 000024 0x809CB260 */ .word	0x00000040
/* 000025 0x809CB264 */ .word	0x00000020
/* 000026 0x809CB268 */ .word	0x00000000
/* 000027 0x809CB26C */ .word	0x00000000
/* 000028 0x809CB270 */ .word	0x00000004
glabel enBoj04OverlayRelocations
/* 000029 0x809CB274 */ .word	0x82000010
/* 000030 0x809CB278 */ .word	0x82000014
/* 000031 0x809CB27C */ .word	0x82000018
/* 000032 0x809CB280 */ .word	0x8200001C
/* 000033 0x809CB284 */ .word	0x00000000
/* 000034 0x809CB288 */ .word	0x00000000
glabel enBoj04OverlayInfoOffset
/* 000035 0x809CB28C */ .word	0x00000030
