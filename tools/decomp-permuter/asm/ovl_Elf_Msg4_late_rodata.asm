.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80AFD910
/* 000356 0x80AFD910 */ .word	0x3ECCCCCD
glabel D_80AFD914
/* 000357 0x80AFD914 */ .word	0x3D23D70A
glabel D_80AFD918
/* 000358 0x80AFD918 */ .word	0x3ECCCCCD
glabel D_80AFD91C
/* 000359 0x80AFD91C */ .word	0x3D23D70A
glabel elfMsg4OverlayInfo
/* 000360 0x80AFD920 */ .word	0x00000550
/* 000361 0x80AFD924 */ .word	0x00000030
/* 000362 0x80AFD928 */ .word	0x00000020
/* 000363 0x80AFD92C */ .word	0x00000000
/* 000364 0x80AFD930 */ .word	0x00000015
glabel elfMsg4OverlayRelocations
/* 000365 0x80AFD934 */ .word	0x44000140
/* 000366 0x80AFD938 */ .word	0x45000150
/* 000367 0x80AFD93C */ .word	0x46000154
/* 000368 0x80AFD940 */ .word	0x45000168
/* 000369 0x80AFD944 */ .word	0x4600018C
/* 000370 0x80AFD948 */ .word	0x450001B0
/* 000371 0x80AFD94C */ .word	0x460001B4
/* 000372 0x80AFD950 */ .word	0x450001BC
/* 000373 0x80AFD954 */ .word	0x460001CC
/* 000374 0x80AFD958 */ .word	0x450001E8
/* 000375 0x80AFD95C */ .word	0x460001EC
/* 000376 0x80AFD960 */ .word	0x45000164
/* 000377 0x80AFD964 */ .word	0x46000170
/* 000378 0x80AFD968 */ .word	0x44000314
/* 000379 0x80AFD96C */ .word	0x44000324
/* 000380 0x80AFD970 */ .word	0x450003F4
/* 000381 0x80AFD974 */ .word	0x460003F8
/* 000382 0x80AFD978 */ .word	0x44000474
/* 000383 0x80AFD97C */ .word	0x82000010
/* 000384 0x80AFD980 */ .word	0x82000014
/* 000385 0x80AFD984 */ .word	0x82000018
/* 000386 0x80AFD988 */ .word	0x00000000
glabel elfMsg4OverlayInfoOffset
/* 000387 0x80AFD98C */ .word	0x00000070
