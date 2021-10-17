.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enSekihiOverlayInfo
/* 000404 0x80A452D0 */ .word	0x000005D0
/* 000405 0x80A452D4 */ .word	0x00000080
/* 000406 0x80A452D8 */ .word	0x00000000
/* 000407 0x80A452DC */ .word	0x00000000
/* 000408 0x80A452E0 */ .word	0x0000001B
glabel enSekihiOverlayRelocations
/* 000409 0x80A452E4 */ .word	0x45000028
/* 000410 0x80A452E8 */ .word	0x4600002C
/* 000411 0x80A452EC */ .word	0x4500003C
/* 000412 0x80A452F0 */ .word	0x46000098
/* 000413 0x80A452F4 */ .word	0x450000CC
/* 000414 0x80A452F8 */ .word	0x460000D0
/* 000415 0x80A452FC */ .word	0x450000DC
/* 000416 0x80A45300 */ .word	0x460000EC
/* 000417 0x80A45304 */ .word	0x450000F8
/* 000418 0x80A45308 */ .word	0x46000108
/* 000419 0x80A4530C */ .word	0x4500017C
/* 000420 0x80A45310 */ .word	0x46000184
/* 000421 0x80A45314 */ .word	0x450001DC
/* 000422 0x80A45318 */ .word	0x460001E4
/* 000423 0x80A4531C */ .word	0x45000204
/* 000424 0x80A45320 */ .word	0x46000208
/* 000425 0x80A45324 */ .word	0x450001F8
/* 000426 0x80A45328 */ .word	0x46000214
/* 000427 0x80A4532C */ .word	0x4500039C
/* 000428 0x80A45330 */ .word	0x460003A0
/* 000429 0x80A45334 */ .word	0x45000414
/* 000430 0x80A45338 */ .word	0x46000418
/* 000431 0x80A4533C */ .word	0x45000450
/* 000432 0x80A45340 */ .word	0x46000454
/* 000433 0x80A45344 */ .word	0x82000010
/* 000434 0x80A45348 */ .word	0x82000014
/* 000435 0x80A4534C */ .word	0x82000018
/* 000436 0x80A45350 */ .word	0x00000000
/* 000437 0x80A45354 */ .word	0x00000000
/* 000438 0x80A45358 */ .word	0x00000000
glabel enSekihiOverlayInfoOffset
/* 000439 0x80A4535C */ .word	0x00000090
