.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enFirefly2OverlayInfo
/* 000024 0x80A56120 */ .word	0x00000040
/* 000025 0x80A56124 */ .word	0x00000020
/* 000026 0x80A56128 */ .word	0x00000000
/* 000027 0x80A5612C */ .word	0x00000000
/* 000028 0x80A56130 */ .word	0x00000004
glabel enFirefly2OverlayRelocations
/* 000029 0x80A56134 */ .word	0x82000010
/* 000030 0x80A56138 */ .word	0x82000014
/* 000031 0x80A5613C */ .word	0x82000018
/* 000032 0x80A56140 */ .word	0x8200001C
/* 000033 0x80A56144 */ .word	0x00000000
/* 000034 0x80A56148 */ .word	0x00000000
glabel enFirefly2OverlayInfoOffset
/* 000035 0x80A5614C */ .word	0x00000030
