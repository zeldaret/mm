.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBoj05OverlayInfo
/* 000024 0x80A0C7E0 */ .word	0x00000040
/* 000025 0x80A0C7E4 */ .word	0x00000020
/* 000026 0x80A0C7E8 */ .word	0x00000000
/* 000027 0x80A0C7EC */ .word	0x00000000
/* 000028 0x80A0C7F0 */ .word	0x00000004
glabel enBoj05OverlayRelocations
/* 000029 0x80A0C7F4 */ .word	0x82000010
/* 000030 0x80A0C7F8 */ .word	0x82000014
/* 000031 0x80A0C7FC */ .word	0x82000018
/* 000032 0x80A0C800 */ .word	0x8200001C
/* 000033 0x80A0C804 */ .word	0x00000000
/* 000034 0x80A0C808 */ .word	0x00000000
glabel enBoj05OverlayInfoOffset
/* 000035 0x80A0C80C */ .word	0x00000030
