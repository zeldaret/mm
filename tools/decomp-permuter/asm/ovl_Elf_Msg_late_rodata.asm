.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_8092E490
/* 000320 0x8092E490 */ .word	0x3ECCCCCD
glabel D_8092E494
/* 000321 0x8092E494 */ .word	0x3D23D70A
glabel D_8092E498
/* 000322 0x8092E498 */ .word	0x3ECCCCCD
glabel D_8092E49C
/* 000323 0x8092E49C */ .word	0x3D23D70A
glabel elfMsgOverlayInfo
/* 000324 0x8092E4A0 */ .word	0x000004C0
/* 000325 0x8092E4A4 */ .word	0x00000030
/* 000326 0x8092E4A8 */ .word	0x00000020
/* 000327 0x8092E4AC */ .word	0x00000000
/* 000328 0x8092E4B0 */ .word	0x00000014
glabel elfMsgOverlayRelocations
/* 000329 0x8092E4B4 */ .word	0x44000154
/* 000330 0x8092E4B8 */ .word	0x45000164
/* 000331 0x8092E4BC */ .word	0x4600016C
/* 000332 0x8092E4C0 */ .word	0x45000190
/* 000333 0x8092E4C4 */ .word	0x46000194
/* 000334 0x8092E4C8 */ .word	0x450001B8
/* 000335 0x8092E4CC */ .word	0x460001BC
/* 000336 0x8092E4D0 */ .word	0x450001C4
/* 000337 0x8092E4D4 */ .word	0x460001D4
/* 000338 0x8092E4D8 */ .word	0x450001F0
/* 000339 0x8092E4DC */ .word	0x460001F4
/* 000340 0x8092E4E0 */ .word	0x45000178
/* 000341 0x8092E4E4 */ .word	0x46000208
/* 000342 0x8092E4E8 */ .word	0x44000204
/* 000343 0x8092E4EC */ .word	0x44000320
/* 000344 0x8092E4F0 */ .word	0x44000330
/* 000345 0x8092E4F4 */ .word	0x44000418
/* 000346 0x8092E4F8 */ .word	0x82000010
/* 000347 0x8092E4FC */ .word	0x82000014
/* 000348 0x8092E500 */ .word	0x82000018
/* 000349 0x8092E504 */ .word	0x00000000
/* 000350 0x8092E508 */ .word	0x00000000
glabel elfMsgOverlayInfoOffset
/* 000351 0x8092E50C */ .word	0x00000070
