.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objFunenOverlayInfo
/* 000104 0x80A198E0 */ .word	0x00000170
/* 000105 0x80A198E4 */ .word	0x00000030
/* 000106 0x80A198E8 */ .word	0x00000000
/* 000107 0x80A198EC */ .word	0x00000000
/* 000108 0x80A198F0 */ .word	0x00000004
glabel objFunenOverlayRelocations
/* 000109 0x80A198F4 */ .word	0x45000010
/* 000110 0x80A198F8 */ .word	0x46000024
/* 000111 0x80A198FC */ .word	0x82000010
/* 000112 0x80A19900 */ .word	0x8200001C
/* 000113 0x80A19904 */ .word	0x00000000
/* 000114 0x80A19908 */ .word	0x00000000
glabel objFunenOverlayInfoOffset
/* 000115 0x80A1990C */ .word	0x00000030
