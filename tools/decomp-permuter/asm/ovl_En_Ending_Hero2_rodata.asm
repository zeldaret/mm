.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enEndingHero2OverlayInfo
/* 000124 0x80C23420 */ .word	0x000001D0
/* 000125 0x80C23424 */ .word	0x00000020
/* 000126 0x80C23428 */ .word	0x00000000
/* 000127 0x80C2342C */ .word	0x00000000
/* 000128 0x80C23430 */ .word	0x00000007
glabel enEndingHero2OverlayRelocations
/* 000129 0x80C23434 */ .word	0x4400008C
/* 000130 0x80C23438 */ .word	0x450000B8
/* 000131 0x80C2343C */ .word	0x460000C0
/* 000132 0x80C23440 */ .word	0x82000010
/* 000133 0x80C23444 */ .word	0x82000014
/* 000134 0x80C23448 */ .word	0x82000018
/* 000135 0x80C2344C */ .word	0x8200001C
/* 000136 0x80C23450 */ .word	0x00000000
/* 000137 0x80C23454 */ .word	0x00000000
/* 000138 0x80C23458 */ .word	0x00000000
glabel enEndingHero2OverlayInfoOffset
/* 000139 0x80C2345C */ .word	0x00000040
