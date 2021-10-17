.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enWarpUzuOverlayInfo
/* 000228 0x80A66510 */ .word	0x00000320
/* 000229 0x80A66514 */ .word	0x00000070
/* 000230 0x80A66518 */ .word	0x00000000
/* 000231 0x80A6651C */ .word	0x00000000
/* 000232 0x80A66520 */ .word	0x00000010
glabel enWarpUzuOverlayRelocations
/* 000233 0x80A66524 */ .word	0x45000010
/* 000234 0x80A66528 */ .word	0x46000014
/* 000235 0x80A6652C */ .word	0x45000028
/* 000236 0x80A66530 */ .word	0x4600002C
/* 000237 0x80A66534 */ .word	0x44000044
/* 000238 0x80A66538 */ .word	0x450000AC
/* 000239 0x80A6653C */ .word	0x460000B0
/* 000240 0x80A66540 */ .word	0x450000D8
/* 000241 0x80A66544 */ .word	0x460000DC
/* 000242 0x80A66548 */ .word	0x44000128
/* 000243 0x80A6654C */ .word	0x45000248
/* 000244 0x80A66550 */ .word	0x46000250
/* 000245 0x80A66554 */ .word	0x82000010
/* 000246 0x80A66558 */ .word	0x82000014
/* 000247 0x80A6655C */ .word	0x82000018
/* 000248 0x80A66560 */ .word	0x8200001C
/* 000249 0x80A66564 */ .word	0x00000000
/* 000250 0x80A66568 */ .word	0x00000000
glabel enWarpUzuOverlayInfoOffset
/* 000251 0x80A6656C */ .word	0x00000060
