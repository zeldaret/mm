.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097A610
/* 000104 0x8097A610 */ .word	0x0000000C
/* 000105 0x8097A614 */ .word	func_8097A470
glabel D_8097A618
/* 000106 0x8097A618 */ .word	0x04030270
/* 000107 0x8097A61C */ .word	0x04030670
/* 000108 0x8097A620 */ .word	0x04030A70
/* 000109 0x8097A624 */ .word	0x04030E70
/* 000110 0x8097A628 */ .word	0x04031270
/* 000111 0x8097A62C */ .word	0x04031670
/* 000112 0x8097A630 */ .word	0x04031A70
/* 000113 0x8097A634 */ .word	0x04031E70
/* 000114 0x8097A638 */ .word	0x00000000
/* 000115 0x8097A63C */ .word	0x00000000
glabel effectSsGFireOverlayInfo
/* 000116 0x8097A640 */ .word	0x000001A0
/* 000117 0x8097A644 */ .word	0x00000030
/* 000118 0x8097A648 */ .word	0x00000000
/* 000119 0x8097A64C */ .word	0x00000000
/* 000120 0x8097A650 */ .word	0x00000007
glabel effectSsGFireOverlayRelocations
/* 000121 0x8097A654 */ .word	0x4500004C
/* 000122 0x8097A658 */ .word	0x46000058
/* 000123 0x8097A65C */ .word	0x45000050
/* 000124 0x8097A660 */ .word	0x4600005C
/* 000125 0x8097A664 */ .word	0x450000EC
/* 000126 0x8097A668 */ .word	0x460000F0
/* 000127 0x8097A66C */ .word	0x82000004
/* 000128 0x8097A670 */ .word	0x00000000
/* 000129 0x8097A674 */ .word	0x00000000
/* 000130 0x8097A678 */ .word	0x00000000
glabel effectSsGFireOverlayInfoOffset
/* 000131 0x8097A67C */ .word	0x00000040
