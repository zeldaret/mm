.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgMbarChairOverlayInfo
/* 000064 0x80B7EA30 */ .word	0x000000D0
/* 000065 0x80B7EA34 */ .word	0x00000030
/* 000066 0x80B7EA38 */ .word	0x00000000
/* 000067 0x80B7EA3C */ .word	0x00000000
/* 000068 0x80B7EA40 */ .word	0x00000006
glabel bgMbarChairOverlayRelocations
/* 000069 0x80B7EA44 */ .word	0x45000010
/* 000070 0x80B7EA48 */ .word	0x46000014
/* 000071 0x80B7EA4C */ .word	0x82000010
/* 000072 0x80B7EA50 */ .word	0x82000014
/* 000073 0x80B7EA54 */ .word	0x82000018
/* 000074 0x80B7EA58 */ .word	0x8200001C
glabel bgMbarChairOverlayInfoOffset
/* 000075 0x80B7EA5C */ .word	0x00000030
