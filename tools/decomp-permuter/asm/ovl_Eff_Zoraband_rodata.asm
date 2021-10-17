.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel effZorabandOverlayInfo
/* 000232 0x80C07AE0 */ .word	0x00000380
/* 000233 0x80C07AE4 */ .word	0x00000020
/* 000234 0x80C07AE8 */ .word	0x00000000
/* 000235 0x80C07AEC */ .word	0x00000000
/* 000236 0x80C07AF0 */ .word	0x00000008
glabel effZorabandOverlayRelocations
/* 000237 0x80C07AF4 */ .word	0x4500001C
/* 000238 0x80C07AF8 */ .word	0x46000020
/* 000239 0x80C07AFC */ .word	0x450000D0
/* 000240 0x80C07B00 */ .word	0x460000D8
/* 000241 0x80C07B04 */ .word	0x82000010
/* 000242 0x80C07B08 */ .word	0x82000014
/* 000243 0x80C07B0C */ .word	0x82000018
/* 000244 0x80C07B10 */ .word	0x8200001C
/* 000245 0x80C07B14 */ .word	0x00000000
/* 000246 0x80C07B18 */ .word	0x00000000
glabel effZorabandOverlayInfoOffset
/* 000247 0x80C07B1C */ .word	0x00000040
