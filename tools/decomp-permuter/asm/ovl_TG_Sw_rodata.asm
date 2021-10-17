.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 000248 0x80B1A340 */ .word	0x3E4CCCCD
/* 000249 0x80B1A344 */ .word	0x3DCCCCCD
/* 000250 0x80B1A348 */ .word	0x3DCCCCCD
/* 000251 0x80B1A34C */ .word	0x3E4CCCCD
glabel tGSwOverlayInfo
/* 000252 0x80B1A350 */ .word	0x000003C0
/* 000253 0x80B1A354 */ .word	0x00000020
/* 000254 0x80B1A358 */ .word	0x00000010
/* 000255 0x80B1A35C */ .word	0x00000000
/* 000256 0x80B1A360 */ .word	0x00000010
glabel tGSwOverlayRelocations
/* 000257 0x80B1A364 */ .word	0x45000088
/* 000258 0x80B1A368 */ .word	0x46000090
/* 000259 0x80B1A36C */ .word	0x45000204
/* 000260 0x80B1A370 */ .word	0x46000208
/* 000261 0x80B1A374 */ .word	0x4500029C
/* 000262 0x80B1A378 */ .word	0x460002A0
/* 000263 0x80B1A37C */ .word	0x450002AC
/* 000264 0x80B1A380 */ .word	0x460002D8
/* 000265 0x80B1A384 */ .word	0x45000324
/* 000266 0x80B1A388 */ .word	0x4600032C
/* 000267 0x80B1A38C */ .word	0x45000330
/* 000268 0x80B1A390 */ .word	0x46000338
/* 000269 0x80B1A394 */ .word	0x82000010
/* 000270 0x80B1A398 */ .word	0x82000014
/* 000271 0x80B1A39C */ .word	0x82000018
/* 000272 0x80B1A3A0 */ .word	0x8200001C
/* 000273 0x80B1A3A4 */ .word	0x00000000
/* 000274 0x80B1A3A8 */ .word	0x00000000
glabel tGSwOverlayInfoOffset
/* 000275 0x80B1A3AC */ .word	0x00000060
