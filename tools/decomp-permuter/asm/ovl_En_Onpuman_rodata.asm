.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enOnpumanOverlayInfo
/* 000344 0x80B123C0 */ .word	0x00000510
/* 000345 0x80B123C4 */ .word	0x00000050
/* 000346 0x80B123C8 */ .word	0x00000000
/* 000347 0x80B123CC */ .word	0x00000000
/* 000348 0x80B123D0 */ .word	0x00000014
glabel enOnpumanOverlayRelocations
/* 000349 0x80B123D4 */ .word	0x45000034
/* 000350 0x80B123D8 */ .word	0x46000044
/* 000351 0x80B123DC */ .word	0x4500007C
/* 000352 0x80B123E0 */ .word	0x46000084
/* 000353 0x80B123E4 */ .word	0x45000134
/* 000354 0x80B123E8 */ .word	0x46000144
/* 000355 0x80B123EC */ .word	0x450001B0
/* 000356 0x80B123F0 */ .word	0x460001B4
/* 000357 0x80B123F4 */ .word	0x45000228
/* 000358 0x80B123F8 */ .word	0x46000280
/* 000359 0x80B123FC */ .word	0x45000354
/* 000360 0x80B12400 */ .word	0x46000358
/* 000361 0x80B12404 */ .word	0x450003A4
/* 000362 0x80B12408 */ .word	0x460003A8
/* 000363 0x80B1240C */ .word	0x440003C0
/* 000364 0x80B12410 */ .word	0x450003E0
/* 000365 0x80B12414 */ .word	0x460003E4
/* 000366 0x80B12418 */ .word	0x82000010
/* 000367 0x80B1241C */ .word	0x82000014
/* 000368 0x80B12420 */ .word	0x82000018
/* 000369 0x80B12424 */ .word	0x00000000
/* 000370 0x80B12428 */ .word	0x00000000
glabel enOnpumanOverlayInfoOffset
/* 000371 0x80B1242C */ .word	0x00000070
