.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel dmSaOverlayInfo
/* 000244 0x80A2ED30 */ .word	0x00000380
/* 000245 0x80A2ED34 */ .word	0x00000040
/* 000246 0x80A2ED38 */ .word	0x00000010
/* 000247 0x80A2ED3C */ .word	0x00000000
/* 000248 0x80A2ED40 */ .word	0x00000013
glabel dmSaOverlayRelocations
/* 000249 0x80A2ED44 */ .word	0x450000BC
/* 000250 0x80A2ED48 */ .word	0x460000C0
/* 000251 0x80A2ED4C */ .word	0x45000108
/* 000252 0x80A2ED50 */ .word	0x4600010C
/* 000253 0x80A2ED54 */ .word	0x44000114
/* 000254 0x80A2ED58 */ .word	0x4500012C
/* 000255 0x80A2ED5C */ .word	0x46000130
/* 000256 0x80A2ED60 */ .word	0x440002E4
/* 000257 0x80A2ED64 */ .word	0x44000320
/* 000258 0x80A2ED68 */ .word	0x4500033C
/* 000259 0x80A2ED6C */ .word	0x46000350
/* 000260 0x80A2ED70 */ .word	0x45000340
/* 000261 0x80A2ED74 */ .word	0x4600034C
/* 000262 0x80A2ED78 */ .word	0x45000344
/* 000263 0x80A2ED7C */ .word	0x46000348
/* 000264 0x80A2ED80 */ .word	0x82000010
/* 000265 0x80A2ED84 */ .word	0x82000014
/* 000266 0x80A2ED88 */ .word	0x82000018
/* 000267 0x80A2ED8C */ .word	0x8200001C
/* 000268 0x80A2ED90 */ .word	0x00000000
/* 000269 0x80A2ED94 */ .word	0x00000000
/* 000270 0x80A2ED98 */ .word	0x00000000
glabel dmSaOverlayInfoOffset
/* 000271 0x80A2ED9C */ .word	0x00000070
