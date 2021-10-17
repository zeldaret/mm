.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objMakeoshihikiOverlayInfo
/* 000192 0x80972650 */ .word	0x000002E0
/* 000193 0x80972654 */ .word	0x00000020
/* 000194 0x80972658 */ .word	0x00000000
/* 000195 0x8097265C */ .word	0x00000000
/* 000196 0x80972660 */ .word	0x00000004
glabel objMakeoshihikiOverlayRelocations
/* 000197 0x80972664 */ .word	0x4400015C
/* 000198 0x80972668 */ .word	0x44000294
/* 000199 0x8097266C */ .word	0x82000010
/* 000200 0x80972670 */ .word	0x82000018
/* 000201 0x80972674 */ .word	0x00000000
/* 000202 0x80972678 */ .word	0x00000000
glabel objMakeoshihikiOverlayInfoOffset
/* 000203 0x8097267C */ .word	0x00000030
