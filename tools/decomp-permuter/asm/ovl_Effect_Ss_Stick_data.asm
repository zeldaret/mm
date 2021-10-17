.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097BA70
/* 000152 0x8097BA70 */ .word	0x00000010
/* 000153 0x8097BA74 */ .word	func_8097B810
/* 000154 0x8097BA78 */ .word	0x00000000
/* 000155 0x8097BA7C */ .word	0x00000000
glabel D_8097BA80
/* 000156 0x8097BA80 */ .word	0x3C23D70A
glabel D_8097BA84
/* 000157 0x8097BA84 */ .word	0x3B23D70A
/* 000158 0x8097BA88 */ .word	0x00000000
/* 000159 0x8097BA8C */ .word	0x00000000
glabel effectSsStickOverlayInfo
/* 000160 0x8097BA90 */ .word	0x00000260
/* 000161 0x8097BA94 */ .word	0x00000010
/* 000162 0x8097BA98 */ .word	0x00000010
/* 000163 0x8097BA9C */ .word	0x00000000
/* 000164 0x8097BAA0 */ .word	0x00000009
glabel effectSsStickOverlayRelocations
/* 000165 0x8097BAA4 */ .word	0x450000D0
/* 000166 0x8097BAA8 */ .word	0x460000DC
/* 000167 0x8097BAAC */ .word	0x450000D4
/* 000168 0x8097BAB0 */ .word	0x460000E0
/* 000169 0x8097BAB4 */ .word	0x4500014C
/* 000170 0x8097BAB8 */ .word	0x46000150
/* 000171 0x8097BABC */ .word	0x45000154
/* 000172 0x8097BAC0 */ .word	0x46000158
/* 000173 0x8097BAC4 */ .word	0x82000004
/* 000174 0x8097BAC8 */ .word	0x00000000
glabel effectSsStickOverlayInfoOffset
/* 000175 0x8097BACC */ .word	0x00000040
