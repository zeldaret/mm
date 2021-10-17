.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enFall2OverlayInfo
/* 000432 0x80C1BD00 */ .word	0x000005A0
/* 000433 0x80C1BD04 */ .word	0x00000110
/* 000434 0x80C1BD08 */ .word	0x00000010
/* 000435 0x80C1BD0C */ .word	0x00000000
/* 000436 0x80C1BD10 */ .word	0x0000001D
glabel enFall2OverlayRelocations
/* 000437 0x80C1BD14 */ .word	0x45000020
/* 000438 0x80C1BD18 */ .word	0x46000024
/* 000439 0x80C1BD1C */ .word	0x4500008C
/* 000440 0x80C1BD20 */ .word	0x46000090
/* 000441 0x80C1BD24 */ .word	0x45000160
/* 000442 0x80C1BD28 */ .word	0x46000164
/* 000443 0x80C1BD2C */ .word	0x450001AC
/* 000444 0x80C1BD30 */ .word	0x460001E0
/* 000445 0x80C1BD34 */ .word	0x45000198
/* 000446 0x80C1BD38 */ .word	0x460001F8
/* 000447 0x80C1BD3C */ .word	0x4500019C
/* 000448 0x80C1BD40 */ .word	0x460001B4
/* 000449 0x80C1BD44 */ .word	0x450001E4
/* 000450 0x80C1BD48 */ .word	0x460001E8
/* 000451 0x80C1BD4C */ .word	0x45000280
/* 000452 0x80C1BD50 */ .word	0x46000284
/* 000453 0x80C1BD54 */ .word	0x450002DC
/* 000454 0x80C1BD58 */ .word	0x460002F0
/* 000455 0x80C1BD5C */ .word	0x45000310
/* 000456 0x80C1BD60 */ .word	0x46000324
/* 000457 0x80C1BD64 */ .word	0x4500034C
/* 000458 0x80C1BD68 */ .word	0x46000360
/* 000459 0x80C1BD6C */ .word	0x44000428
/* 000460 0x80C1BD70 */ .word	0x44000430
/* 000461 0x80C1BD74 */ .word	0x4400046C
/* 000462 0x80C1BD78 */ .word	0x82000010
/* 000463 0x80C1BD7C */ .word	0x82000014
/* 000464 0x80C1BD80 */ .word	0x82000018
/* 000465 0x80C1BD84 */ .word	0x8200001C
/* 000466 0x80C1BD88 */ .word	0x00000000
glabel enFall2OverlayInfoOffset
/* 000467 0x80C1BD8C */ .word	0x00000090
