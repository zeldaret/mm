.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBoj01OverlayInfo
/* 000024 0x809C3DE0 */ .word	0x00000040
/* 000025 0x809C3DE4 */ .word	0x00000020
/* 000026 0x809C3DE8 */ .word	0x00000000
/* 000027 0x809C3DEC */ .word	0x00000000
/* 000028 0x809C3DF0 */ .word	0x00000004
glabel enBoj01OverlayRelocations
/* 000029 0x809C3DF4 */ .word	0x82000010
/* 000030 0x809C3DF8 */ .word	0x82000014
/* 000031 0x809C3DFC */ .word	0x82000018
/* 000032 0x809C3E00 */ .word	0x8200001C
/* 000033 0x809C3E04 */ .word	0x00000000
/* 000034 0x809C3E08 */ .word	0x00000000
glabel enBoj01OverlayInfoOffset
/* 000035 0x809C3E0C */ .word	0x00000030
