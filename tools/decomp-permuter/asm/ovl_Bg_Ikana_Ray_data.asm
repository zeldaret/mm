.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ikana_Ray_InitVars
/* 000132 0x80BD55D0 */ .word	0x02560600
/* 000133 0x80BD55D4 */ .word	0x00000000
/* 000134 0x80BD55D8 */ .word	0x02030000
/* 000135 0x80BD55DC */ .word	0x00000198
/* 000136 0x80BD55E0 */ .word	BgIkanaRay_Init
/* 000137 0x80BD55E4 */ .word	BgIkanaRay_Destroy
/* 000138 0x80BD55E8 */ .word	BgIkanaRay_Update
/* 000139 0x80BD55EC */ .word	BgIkanaRay_Draw
glabel bgIkanaRayCylinderInit
/* 000140 0x80BD55F0 */ .word	0x0A210000
/* 000141 0x80BD55F4 */ .word	0x00010000
/* 000142 0x80BD55F8 */ .word	0x00000000
/* 000143 0x80BD55FC */ .word	0x00200000
/* 000144 0x80BD5600 */ .word	0x00000000
/* 000145 0x80BD5604 */ .word	0x00000000
/* 000146 0x80BD5608 */ .word	0x00000000
/* 000147 0x80BD560C */ .word	0x19000100
/* 000148 0x80BD5610 */ .word	0x005A01A4
/* 000149 0x80BD5614 */ .word	0xFE5C0000
/* 000150 0x80BD5618 */ .word	0x00000000
glabel bgIkanaRayCompInit
/* 000151 0x80BD561C */ .word	0xB0FC0FA0
/* 000152 0x80BD5620 */ .word	0xB10003E8
/* 000153 0x80BD5624 */ .word	0xB10403E8
/* 000154 0x80BD5628 */ .word	0x48580064
/* 000155 0x80BD562C */ .word	0x00000000
