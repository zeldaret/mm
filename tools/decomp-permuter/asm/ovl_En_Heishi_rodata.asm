.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enHeishiOverlayInfo
/* 000352 0x80BE94A0 */ .word	0x00000510
/* 000353 0x80BE94A4 */ .word	0x00000070
/* 000354 0x80BE94A8 */ .word	0x00000000
/* 000355 0x80BE94AC */ .word	0x00000000
/* 000356 0x80BE94B0 */ .word	0x00000013
glabel enHeishiOverlayRelocations
/* 000357 0x80BE94B4 */ .word	0x45000128
/* 000358 0x80BE94B8 */ .word	0x46000134
/* 000359 0x80BE94BC */ .word	0x44000154
/* 000360 0x80BE94C0 */ .word	0x450001B0
/* 000361 0x80BE94C4 */ .word	0x460001C0
/* 000362 0x80BE94C8 */ .word	0x450001E4
/* 000363 0x80BE94CC */ .word	0x460001F8
/* 000364 0x80BE94D0 */ .word	0x450001CC
/* 000365 0x80BE94D4 */ .word	0x460001EC
/* 000366 0x80BE94D8 */ .word	0x440002C8
/* 000367 0x80BE94DC */ .word	0x450002D4
/* 000368 0x80BE94E0 */ .word	0x460002D8
/* 000369 0x80BE94E4 */ .word	0x440003DC
/* 000370 0x80BE94E8 */ .word	0x450004D8
/* 000371 0x80BE94EC */ .word	0x460004DC
/* 000372 0x80BE94F0 */ .word	0x82000010
/* 000373 0x80BE94F4 */ .word	0x82000014
/* 000374 0x80BE94F8 */ .word	0x82000018
/* 000375 0x80BE94FC */ .word	0x8200001C
/* 000376 0x80BE9500 */ .word	0x00000000
/* 000377 0x80BE9504 */ .word	0x00000000
/* 000378 0x80BE9508 */ .word	0x00000000
glabel enHeishiOverlayInfoOffset
/* 000379 0x80BE950C */ .word	0x00000070
