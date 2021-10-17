.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objGrassUnitOverlayInfo
/* 000404 0x809AC430 */ .word	0x00000560
/* 000405 0x809AC434 */ .word	0x000000F0
/* 000406 0x809AC438 */ .word	0x00000000
/* 000407 0x809AC43C */ .word	0x00000000
/* 000408 0x809AC440 */ .word	0x00000017
glabel objGrassUnitOverlayRelocations
/* 000409 0x809AC444 */ .word	0x4500003C
/* 000410 0x809AC448 */ .word	0x46000040
/* 000411 0x809AC44C */ .word	0x450000AC
/* 000412 0x809AC450 */ .word	0x460000B0
/* 000413 0x809AC454 */ .word	0x45000120
/* 000414 0x809AC458 */ .word	0x46000124
/* 000415 0x809AC45C */ .word	0x450001D0
/* 000416 0x809AC460 */ .word	0x460001E4
/* 000417 0x809AC464 */ .word	0x44000230
/* 000418 0x809AC468 */ .word	0x45000250
/* 000419 0x809AC46C */ .word	0x46000254
/* 000420 0x809AC470 */ .word	0x44000268
/* 000421 0x809AC474 */ .word	0x45000284
/* 000422 0x809AC478 */ .word	0x46000288
/* 000423 0x809AC47C */ .word	0x4400029C
/* 000424 0x809AC480 */ .word	0x450002B8
/* 000425 0x809AC484 */ .word	0x460002BC
/* 000426 0x809AC488 */ .word	0x45000354
/* 000427 0x809AC48C */ .word	0x46000358
/* 000428 0x809AC490 */ .word	0x44000494
/* 000429 0x809AC494 */ .word	0x82000010
/* 000430 0x809AC498 */ .word	0x820000CC
/* 000431 0x809AC49C */ .word	0x820000D4
/* 000432 0x809AC4A0 */ .word	0x00000000
/* 000433 0x809AC4A4 */ .word	0x00000000
/* 000434 0x809AC4A8 */ .word	0x00000000
glabel objGrassUnitOverlayInfoOffset
/* 000435 0x809AC4AC */ .word	0x00000080
