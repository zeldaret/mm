.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgIkanaRayOverlayInfo
/* 000156 0x80BD5630 */ .word	0x00000210
/* 000157 0x80BD5634 */ .word	0x00000060
/* 000158 0x80BD5638 */ .word	0x00000000
/* 000159 0x80BD563C */ .word	0x00000000
/* 000160 0x80BD5640 */ .word	0x00000011
glabel bgIkanaRayOverlayRelocations
/* 000161 0x80BD5644 */ .word	0x45000014
/* 000162 0x80BD5648 */ .word	0x46000018
/* 000163 0x80BD564C */ .word	0x45000034
/* 000164 0x80BD5650 */ .word	0x46000038
/* 000165 0x80BD5654 */ .word	0x44000080
/* 000166 0x80BD5658 */ .word	0x44000090
/* 000167 0x80BD565C */ .word	0x450000DC
/* 000168 0x80BD5660 */ .word	0x460000E0
/* 000169 0x80BD5664 */ .word	0x44000128
/* 000170 0x80BD5668 */ .word	0x45000144
/* 000171 0x80BD566C */ .word	0x46000150
/* 000172 0x80BD5670 */ .word	0x4500014C
/* 000173 0x80BD5674 */ .word	0x46000154
/* 000174 0x80BD5678 */ .word	0x82000010
/* 000175 0x80BD567C */ .word	0x82000014
/* 000176 0x80BD5680 */ .word	0x82000018
/* 000177 0x80BD5684 */ .word	0x8200001C
/* 000178 0x80BD5688 */ .word	0x00000000
glabel bgIkanaRayOverlayInfoOffset
/* 000179 0x80BD568C */ .word	0x00000060
