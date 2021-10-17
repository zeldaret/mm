.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel effLastdayOverlayInfo
/* 000444 0x80BEC1B0 */ .word	0x000006D0
/* 000445 0x80BEC1B4 */ .word	0x00000020
/* 000446 0x80BEC1B8 */ .word	0x00000000
/* 000447 0x80BEC1BC */ .word	0x00000000
/* 000448 0x80BEC1C0 */ .word	0x0000001D
glabel effLastdayOverlayRelocations
/* 000449 0x80BEC1C4 */ .word	0x45000070
/* 000450 0x80BEC1C8 */ .word	0x46000078
/* 000451 0x80BEC1CC */ .word	0x450000B0
/* 000452 0x80BEC1D0 */ .word	0x460000B8
/* 000453 0x80BEC1D4 */ .word	0x450000F0
/* 000454 0x80BEC1D8 */ .word	0x460000F8
/* 000455 0x80BEC1DC */ .word	0x45000134
/* 000456 0x80BEC1E0 */ .word	0x4600013C
/* 000457 0x80BEC1E4 */ .word	0x450002D4
/* 000458 0x80BEC1E8 */ .word	0x460002D8
/* 000459 0x80BEC1EC */ .word	0x450002BC
/* 000460 0x80BEC1F0 */ .word	0x46000314
/* 000461 0x80BEC1F4 */ .word	0x45000398
/* 000462 0x80BEC1F8 */ .word	0x460003C0
/* 000463 0x80BEC1FC */ .word	0x450003AC
/* 000464 0x80BEC200 */ .word	0x460003D4
/* 000465 0x80BEC204 */ .word	0x45000458
/* 000466 0x80BEC208 */ .word	0x46000480
/* 000467 0x80BEC20C */ .word	0x4500046C
/* 000468 0x80BEC210 */ .word	0x46000494
/* 000469 0x80BEC214 */ .word	0x4500055C
/* 000470 0x80BEC218 */ .word	0x46000560
/* 000471 0x80BEC21C */ .word	0x45000528
/* 000472 0x80BEC220 */ .word	0x4600059C
/* 000473 0x80BEC224 */ .word	0x4400065C
/* 000474 0x80BEC228 */ .word	0x82000010
/* 000475 0x80BEC22C */ .word	0x82000014
/* 000476 0x80BEC230 */ .word	0x82000018
/* 000477 0x80BEC234 */ .word	0x8200001C
/* 000478 0x80BEC238 */ .word	0x00000000
glabel effLastdayOverlayInfoOffset
/* 000479 0x80BEC23C */ .word	0x00000090
