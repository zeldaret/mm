.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel shotSunOverlayInfo
/* 000360 0x80973BE0 */ .word	0x00000540
/* 000361 0x80973BE4 */ .word	0x00000050
/* 000362 0x80973BE8 */ .word	0x00000010
/* 000363 0x80973BEC */ .word	0x00000000
/* 000364 0x80973BF0 */ .word	0x00000015
glabel shotSunOverlayRelocations
/* 000365 0x80973BF4 */ .word	0x45000018
/* 000366 0x80973BF8 */ .word	0x46000024
/* 000367 0x80973BFC */ .word	0x45000074
/* 000368 0x80973C00 */ .word	0x46000080
/* 000369 0x80973C04 */ .word	0x45000090
/* 000370 0x80973C08 */ .word	0x4600009C
/* 000371 0x80973C0C */ .word	0x45000218
/* 000372 0x80973C10 */ .word	0x4600021C
/* 000373 0x80973C14 */ .word	0x450002D4
/* 000374 0x80973C18 */ .word	0x460002D8
/* 000375 0x80973C1C */ .word	0x450002FC
/* 000376 0x80973C20 */ .word	0x46000300
/* 000377 0x80973C24 */ .word	0x45000384
/* 000378 0x80973C28 */ .word	0x46000388
/* 000379 0x80973C2C */ .word	0x450003DC
/* 000380 0x80973C30 */ .word	0x460003E0
/* 000381 0x80973C34 */ .word	0x4500044C
/* 000382 0x80973C38 */ .word	0x46000450
/* 000383 0x80973C3C */ .word	0x82000010
/* 000384 0x80973C40 */ .word	0x82000014
/* 000385 0x80973C44 */ .word	0x82000018
/* 000386 0x80973C48 */ .word	0x00000000
glabel shotSunOverlayInfoOffset
/* 000387 0x80973C4C */ .word	0x00000070
