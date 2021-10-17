.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTorch2OverlayInfo
/* 000284 0x808A3620 */ .word	0x00000400
/* 000285 0x808A3624 */ .word	0x00000070
/* 000286 0x808A3628 */ .word	0x00000000
/* 000287 0x808A362C */ .word	0x00000000
/* 000288 0x808A3630 */ .word	0x0000000E
glabel enTorch2OverlayRelocations
/* 000289 0x808A3634 */ .word	0x45000010
/* 000290 0x808A3638 */ .word	0x46000014
/* 000291 0x808A363C */ .word	0x45000028
/* 000292 0x808A3640 */ .word	0x4600002C
/* 000293 0x808A3644 */ .word	0x4500011C
/* 000294 0x808A3648 */ .word	0x46000124
/* 000295 0x808A364C */ .word	0x45000284
/* 000296 0x808A3650 */ .word	0x46000294
/* 000297 0x808A3654 */ .word	0x4500031C
/* 000298 0x808A3658 */ .word	0x46000338
/* 000299 0x808A365C */ .word	0x82000010
/* 000300 0x808A3660 */ .word	0x82000014
/* 000301 0x808A3664 */ .word	0x82000018
/* 000302 0x808A3668 */ .word	0x8200001C
glabel enTorch2OverlayInfoOffset
/* 000303 0x808A366C */ .word	0x00000050
