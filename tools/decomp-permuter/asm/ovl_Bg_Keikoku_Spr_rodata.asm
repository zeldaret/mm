.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgKeikokuSprOverlayInfo
/* 000096 0x808C3BD0 */ .word	0x00000150
/* 000097 0x808C3BD4 */ .word	0x00000030
/* 000098 0x808C3BD8 */ .word	0x00000000
/* 000099 0x808C3BDC */ .word	0x00000000
/* 000100 0x808C3BE0 */ .word	0x00000006
glabel bgKeikokuSprOverlayRelocations
/* 000101 0x808C3BE4 */ .word	0x4500000C
/* 000102 0x808C3BE8 */ .word	0x46000014
/* 000103 0x808C3BEC */ .word	0x82000010
/* 000104 0x808C3BF0 */ .word	0x82000014
/* 000105 0x808C3BF4 */ .word	0x82000018
/* 000106 0x808C3BF8 */ .word	0x8200001C
glabel bgKeikokuSprOverlayInfoOffset
/* 000107 0x808C3BFC */ .word	0x00000030
