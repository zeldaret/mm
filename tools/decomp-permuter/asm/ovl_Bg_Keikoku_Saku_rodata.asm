.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgKeikokuSakuOverlayInfo
/* 000236 0x80A53B80 */ .word	0x00000380
/* 000237 0x80A53B84 */ .word	0x00000020
/* 000238 0x80A53B88 */ .word	0x00000010
/* 000239 0x80A53B8C */ .word	0x00000000
/* 000240 0x80A53B90 */ .word	0x00000012
glabel bgKeikokuSakuOverlayRelocations
/* 000241 0x80A53B94 */ .word	0x4500006C
/* 000242 0x80A53B98 */ .word	0x46000070
/* 000243 0x80A53B9C */ .word	0x45000068
/* 000244 0x80A53BA0 */ .word	0x4600007C
/* 000245 0x80A53BA4 */ .word	0x450000F4
/* 000246 0x80A53BA8 */ .word	0x460000F8
/* 000247 0x80A53BAC */ .word	0x45000144
/* 000248 0x80A53BB0 */ .word	0x46000168
/* 000249 0x80A53BB4 */ .word	0x450001A0
/* 000250 0x80A53BB8 */ .word	0x460001A8
/* 000251 0x80A53BBC */ .word	0x450001CC
/* 000252 0x80A53BC0 */ .word	0x460001D0
/* 000253 0x80A53BC4 */ .word	0x4500021C
/* 000254 0x80A53BC8 */ .word	0x46000224
/* 000255 0x80A53BCC */ .word	0x82000010
/* 000256 0x80A53BD0 */ .word	0x82000014
/* 000257 0x80A53BD4 */ .word	0x82000018
/* 000258 0x80A53BD8 */ .word	0x8200001C
glabel bgKeikokuSakuOverlayInfoOffset
/* 000259 0x80A53BDC */ .word	0x00000060
