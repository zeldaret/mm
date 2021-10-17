.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enSiOverlayInfo
/* 000240 0x8098CDE0 */ .word	0x00000340
/* 000241 0x8098CDE4 */ .word	0x00000080
/* 000242 0x8098CDE8 */ .word	0x00000000
/* 000243 0x8098CDEC */ .word	0x00000000
/* 000244 0x8098CDF0 */ .word	0x00000011
glabel enSiOverlayRelocations
/* 000245 0x8098CDF4 */ .word	0x45000160
/* 000246 0x8098CDF8 */ .word	0x4600016C
/* 000247 0x8098CDFC */ .word	0x44000188
/* 000248 0x8098CE00 */ .word	0x440001D8
/* 000249 0x8098CE04 */ .word	0x4500021C
/* 000250 0x8098CE08 */ .word	0x46000224
/* 000251 0x8098CE0C */ .word	0x45000234
/* 000252 0x8098CE10 */ .word	0x46000240
/* 000253 0x8098CE14 */ .word	0x45000238
/* 000254 0x8098CE18 */ .word	0x4600023C
/* 000255 0x8098CE1C */ .word	0x45000258
/* 000256 0x8098CE20 */ .word	0x4600025C
/* 000257 0x8098CE24 */ .word	0x440002C8
/* 000258 0x8098CE28 */ .word	0x82000010
/* 000259 0x8098CE2C */ .word	0x82000014
/* 000260 0x8098CE30 */ .word	0x82000018
/* 000261 0x8098CE34 */ .word	0x8200001C
/* 000262 0x8098CE38 */ .word	0x00000000
glabel enSiOverlayInfoOffset
/* 000263 0x8098CE3C */ .word	0x00000060
