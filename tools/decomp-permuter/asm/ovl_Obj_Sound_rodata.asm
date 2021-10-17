.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objSoundOverlayInfo
/* 000120 0x8099AB00 */ .word	0x000001C0
/* 000121 0x8099AB04 */ .word	0x00000020
/* 000122 0x8099AB08 */ .word	0x00000000
/* 000123 0x8099AB0C */ .word	0x00000000
/* 000124 0x8099AB10 */ .word	0x00000005
glabel objSoundOverlayRelocations
/* 000125 0x8099AB14 */ .word	0x45000038
/* 000126 0x8099AB18 */ .word	0x4600003C
/* 000127 0x8099AB1C */ .word	0x82000010
/* 000128 0x8099AB20 */ .word	0x82000014
/* 000129 0x8099AB24 */ .word	0x82000018
/* 000130 0x8099AB28 */ .word	0x00000000
glabel objSoundOverlayInfoOffset
/* 000131 0x8099AB2C */ .word	0x00000030
