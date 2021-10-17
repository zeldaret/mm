.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enChaOverlayInfo
/* 000232 0x80BEB8C0 */ .word	0x00000340
/* 000233 0x80BEB8C4 */ .word	0x00000050
/* 000234 0x80BEB8C8 */ .word	0x00000010
/* 000235 0x80BEB8CC */ .word	0x00000000
/* 000236 0x80BEB8D0 */ .word	0x00000017
glabel enChaOverlayRelocations
/* 000237 0x80BEB8D4 */ .word	0x45000018
/* 000238 0x80BEB8D8 */ .word	0x4600001C
/* 000239 0x80BEB8DC */ .word	0x4500005C
/* 000240 0x80BEB8E0 */ .word	0x46000064
/* 000241 0x80BEB8E4 */ .word	0x440000CC
/* 000242 0x80BEB8E8 */ .word	0x450000DC
/* 000243 0x80BEB8EC */ .word	0x460000E4
/* 000244 0x80BEB8F0 */ .word	0x45000108
/* 000245 0x80BEB8F4 */ .word	0x4600010C
/* 000246 0x80BEB8F8 */ .word	0x450001B8
/* 000247 0x80BEB8FC */ .word	0x460001BC
/* 000248 0x80BEB900 */ .word	0x450001DC
/* 000249 0x80BEB904 */ .word	0x460001EC
/* 000250 0x80BEB908 */ .word	0x450001F0
/* 000251 0x80BEB90C */ .word	0x4600021C
/* 000252 0x80BEB910 */ .word	0x450002F4
/* 000253 0x80BEB914 */ .word	0x460002F8
/* 000254 0x80BEB918 */ .word	0x450002FC
/* 000255 0x80BEB91C */ .word	0x46000300
/* 000256 0x80BEB920 */ .word	0x82000010
/* 000257 0x80BEB924 */ .word	0x82000014
/* 000258 0x80BEB928 */ .word	0x82000018
/* 000259 0x80BEB92C */ .word	0x8200001C
/* 000260 0x80BEB930 */ .word	0x00000000
/* 000261 0x80BEB934 */ .word	0x00000000
/* 000262 0x80BEB938 */ .word	0x00000000
glabel enChaOverlayInfoOffset
/* 000263 0x80BEB93C */ .word	0x00000080
