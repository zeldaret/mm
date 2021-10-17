.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80979AB0
/* 000316 0x80979AB0 */ .word	0x00000007
glabel D_80979AB4
/* 000317 0x80979AB4 */ .word	func_809795C0
/* 000318 0x80979AB8 */ .word	0x43918000
/* 000319 0x80979ABC */ .word	0x44118000
/* 000320 0x80979AC0 */ .word	0x44C80000
/* 000321 0x80979AC4 */ .word	0x00000000
/* 000322 0x80979AC8 */ .word	0x00000000
/* 000323 0x80979ACC */ .word	0x00000000
glabel D_80979AD0
/* 000324 0x80979AD0 */ .word	0x3E99999A
glabel D_80979AD4
/* 000325 0x80979AD4 */ .word	0x3E4CCCCD
/* 000326 0x80979AD8 */ .word	0x00000000
/* 000327 0x80979ADC */ .word	0x00000000
glabel effectSsBubbleOverlayInfo
/* 000328 0x80979AE0 */ .word	0x000004F0
/* 000329 0x80979AE4 */ .word	0x00000020
/* 000330 0x80979AE8 */ .word	0x00000010
/* 000331 0x80979AEC */ .word	0x00000000
/* 000332 0x80979AF0 */ .word	0x0000000B
glabel effectSsBubbleOverlayRelocations
/* 000333 0x80979AF4 */ .word	0x4500012C
/* 000334 0x80979AF8 */ .word	0x46000134
/* 000335 0x80979AFC */ .word	0x45000130
/* 000336 0x80979B00 */ .word	0x4600013C
/* 000337 0x80979B04 */ .word	0x450003B4
/* 000338 0x80979B08 */ .word	0x460003C4
/* 000339 0x80979B0C */ .word	0x45000484
/* 000340 0x80979B10 */ .word	0x46000488
/* 000341 0x80979B14 */ .word	0x4500048C
/* 000342 0x80979B18 */ .word	0x46000490
/* 000343 0x80979B1C */ .word	0x82000004
/* 000344 0x80979B20 */ .word	0x00000000
/* 000345 0x80979B24 */ .word	0x00000000
/* 000346 0x80979B28 */ .word	0x00000000
glabel effectSsBubbleOverlayInfoOffset
/* 000347 0x80979B2C */ .word	0x00000050
