.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgOpenSpotOverlayInfo
/* 000120 0x80ACB3C0 */ .word	0x000001B0
/* 000121 0x80ACB3C4 */ .word	0x00000030
/* 000122 0x80ACB3C8 */ .word	0x00000000
/* 000123 0x80ACB3CC */ .word	0x00000000
/* 000124 0x80ACB3D0 */ .word	0x00000007
glabel bgOpenSpotOverlayRelocations
/* 000125 0x80ACB3D4 */ .word	0x45000010
/* 000126 0x80ACB3D8 */ .word	0x46000014
/* 000127 0x80ACB3DC */ .word	0x450000B4
/* 000128 0x80ACB3E0 */ .word	0x460000B8
/* 000129 0x80ACB3E4 */ .word	0x82000010
/* 000130 0x80ACB3E8 */ .word	0x82000014
/* 000131 0x80ACB3EC */ .word	0x82000018
/* 000132 0x80ACB3F0 */ .word	0x00000000
/* 000133 0x80ACB3F4 */ .word	0x00000000
/* 000134 0x80ACB3F8 */ .word	0x00000000
glabel bgOpenSpotOverlayInfoOffset
/* 000135 0x80ACB3FC */ .word	0x00000040
