.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enEncount1OverlayInfo
/* 000372 0x808E0E00 */ .word	0x000005A0
/* 000373 0x808E0E04 */ .word	0x00000030
/* 000374 0x808E0E08 */ .word	0x00000000
/* 000375 0x808E0E0C */ .word	0x00000000
/* 000376 0x808E0E10 */ .word	0x00000008
glabel enEncount1OverlayRelocations
/* 000377 0x808E0E14 */ .word	0x45000100
/* 000378 0x808E0E18 */ .word	0x46000104
/* 000379 0x808E0E1C */ .word	0x450004E0
/* 000380 0x808E0E20 */ .word	0x460004E8
/* 000381 0x808E0E24 */ .word	0x450004C4
/* 000382 0x808E0E28 */ .word	0x460004CC
/* 000383 0x808E0E2C */ .word	0x82000010
/* 000384 0x808E0E30 */ .word	0x82000018
/* 000385 0x808E0E34 */ .word	0x00000000
/* 000386 0x808E0E38 */ .word	0x00000000
glabel enEncount1OverlayInfoOffset
/* 000387 0x808E0E3C */ .word	0x00000040
