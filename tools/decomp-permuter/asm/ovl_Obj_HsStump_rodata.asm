.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objHsStumpOverlayInfo
/* 000352 0x80BDAFB0 */ .word	0x00000530
/* 000353 0x80BDAFB4 */ .word	0x00000030
/* 000354 0x80BDAFB8 */ .word	0x00000020
/* 000355 0x80BDAFBC */ .word	0x00000000
/* 000356 0x80BDAFC0 */ .word	0x0000001B
glabel objHsStumpOverlayRelocations
/* 000357 0x80BDAFC4 */ .word	0x45000018
/* 000358 0x80BDAFC8 */ .word	0x4600001C
/* 000359 0x80BDAFCC */ .word	0x440000B4
/* 000360 0x80BDAFD0 */ .word	0x450000D4
/* 000361 0x80BDAFD4 */ .word	0x460000D8
/* 000362 0x80BDAFD8 */ .word	0x44000124
/* 000363 0x80BDAFDC */ .word	0x45000150
/* 000364 0x80BDAFE0 */ .word	0x46000154
/* 000365 0x80BDAFE4 */ .word	0x45000164
/* 000366 0x80BDAFE8 */ .word	0x46000168
/* 000367 0x80BDAFEC */ .word	0x45000180
/* 000368 0x80BDAFF0 */ .word	0x46000184
/* 000369 0x80BDAFF4 */ .word	0x450001F4
/* 000370 0x80BDAFF8 */ .word	0x460001F8
/* 000371 0x80BDAFFC */ .word	0x450002E4
/* 000372 0x80BDB000 */ .word	0x460002EC
/* 000373 0x80BDB004 */ .word	0x4500039C
/* 000374 0x80BDB008 */ .word	0x460003A8
/* 000375 0x80BDB00C */ .word	0x450003E0
/* 000376 0x80BDB010 */ .word	0x460003E4
/* 000377 0x80BDB014 */ .word	0x45000418
/* 000378 0x80BDB018 */ .word	0x4600041C
/* 000379 0x80BDB01C */ .word	0x44000450
/* 000380 0x80BDB020 */ .word	0x82000010
/* 000381 0x80BDB024 */ .word	0x82000014
/* 000382 0x80BDB028 */ .word	0x82000018
/* 000383 0x80BDB02C */ .word	0x8200001C
/* 000384 0x80BDB030 */ .word	0x00000000
/* 000385 0x80BDB034 */ .word	0x00000000
/* 000386 0x80BDB038 */ .word	0x00000000
glabel objHsStumpOverlayInfoOffset
/* 000387 0x80BDB03C */ .word	0x00000090
