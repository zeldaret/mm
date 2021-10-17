.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enEndingHero4OverlayInfo
/* 000124 0x80C23880 */ .word	0x000001D0
/* 000125 0x80C23884 */ .word	0x00000020
/* 000126 0x80C23888 */ .word	0x00000000
/* 000127 0x80C2388C */ .word	0x00000000
/* 000128 0x80C23890 */ .word	0x00000007
glabel enEndingHero4OverlayRelocations
/* 000129 0x80C23894 */ .word	0x4400008C
/* 000130 0x80C23898 */ .word	0x450000B8
/* 000131 0x80C2389C */ .word	0x460000C0
/* 000132 0x80C238A0 */ .word	0x82000010
/* 000133 0x80C238A4 */ .word	0x82000014
/* 000134 0x80C238A8 */ .word	0x82000018
/* 000135 0x80C238AC */ .word	0x8200001C
/* 000136 0x80C238B0 */ .word	0x00000000
/* 000137 0x80C238B4 */ .word	0x00000000
/* 000138 0x80C238B8 */ .word	0x00000000
glabel enEndingHero4OverlayInfoOffset
/* 000139 0x80C238BC */ .word	0x00000040
