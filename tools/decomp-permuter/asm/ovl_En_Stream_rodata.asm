.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enStreamOverlayInfo
/* 000316 0x80965B40 */ .word	0x000004B0
/* 000317 0x80965B44 */ .word	0x00000030
/* 000318 0x80965B48 */ .word	0x00000010
/* 000319 0x80965B4C */ .word	0x00000000
/* 000320 0x80965B50 */ .word	0x00000013
glabel enStreamOverlayRelocations
/* 000321 0x80965B54 */ .word	0x4500001C
/* 000322 0x80965B58 */ .word	0x46000020
/* 000323 0x80965B5C */ .word	0x45000050
/* 000324 0x80965B60 */ .word	0x46000054
/* 000325 0x80965B64 */ .word	0x4500003C
/* 000326 0x80965B68 */ .word	0x46000060
/* 000327 0x80965B6C */ .word	0x4400005C
/* 000328 0x80965B70 */ .word	0x440001D4
/* 000329 0x80965B74 */ .word	0x4500030C
/* 000330 0x80965B78 */ .word	0x46000314
/* 000331 0x80965B7C */ .word	0x44000310
/* 000332 0x80965B80 */ .word	0x44000354
/* 000333 0x80965B84 */ .word	0x45000364
/* 000334 0x80965B88 */ .word	0x4600036C
/* 000335 0x80965B8C */ .word	0x44000368
/* 000336 0x80965B90 */ .word	0x82000010
/* 000337 0x80965B94 */ .word	0x82000014
/* 000338 0x80965B98 */ .word	0x82000018
/* 000339 0x80965B9C */ .word	0x8200001C
/* 000340 0x80965BA0 */ .word	0x00000000
/* 000341 0x80965BA4 */ .word	0x00000000
/* 000342 0x80965BA8 */ .word	0x00000000
glabel enStreamOverlayInfoOffset
/* 000343 0x80965BAC */ .word	0x00000070
