.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBeeOverlayInfo
/* 000724 0x80B5B270 */ .word	0x00000AD0
/* 000725 0x80B5B274 */ .word	0x00000070
/* 000726 0x80B5B278 */ .word	0x00000010
/* 000727 0x80B5B27C */ .word	0x00000000
/* 000728 0x80B5B280 */ .word	0x00000013
glabel enBeeOverlayRelocations
/* 000729 0x80B5B284 */ .word	0x45000068
/* 000730 0x80B5B288 */ .word	0x46000070
/* 000731 0x80B5B28C */ .word	0x45000084
/* 000732 0x80B5B290 */ .word	0x46000088
/* 000733 0x80B5B294 */ .word	0x4500009C
/* 000734 0x80B5B298 */ .word	0x460000A0
/* 000735 0x80B5B29C */ .word	0x440000EC
/* 000736 0x80B5B2A0 */ .word	0x450002A0
/* 000737 0x80B5B2A4 */ .word	0x460002A4
/* 000738 0x80B5B2A8 */ .word	0x44000488
/* 000739 0x80B5B2AC */ .word	0x450004F8
/* 000740 0x80B5B2B0 */ .word	0x46000500
/* 000741 0x80B5B2B4 */ .word	0x450007F4
/* 000742 0x80B5B2B8 */ .word	0x460007F8
/* 000743 0x80B5B2BC */ .word	0x440009A0
/* 000744 0x80B5B2C0 */ .word	0x82000014
/* 000745 0x80B5B2C4 */ .word	0x82000018
/* 000746 0x80B5B2C8 */ .word	0x8200001C
/* 000747 0x80B5B2CC */ .word	0x82000020
/* 000748 0x80B5B2D0 */ .word	0x00000000
/* 000749 0x80B5B2D4 */ .word	0x00000000
/* 000750 0x80B5B2D8 */ .word	0x00000000
glabel enBeeOverlayInfoOffset
/* 000751 0x80B5B2DC */ .word	0x00000070
