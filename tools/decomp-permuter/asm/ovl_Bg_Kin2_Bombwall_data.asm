.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Kin2_Bombwall_InitVars
/* 000428 0x80B6E6D0 */ .word	0x020E0100
/* 000429 0x80B6E6D4 */ .word	0x10000010
/* 000430 0x80B6E6D8 */ .word	0x01F50000
/* 000431 0x80B6E6DC */ .word	0x000001B0
/* 000432 0x80B6E6E0 */ .word	BgKin2Bombwall_Init
/* 000433 0x80B6E6E4 */ .word	BgKin2Bombwall_Destroy
/* 000434 0x80B6E6E8 */ .word	BgKin2Bombwall_Update
/* 000435 0x80B6E6EC */ .word	BgKin2Bombwall_Draw
glabel D_80B6E6F0
/* 000436 0x80B6E6F0 */ .word	0x0A000900
/* 000437 0x80B6E6F4 */ .word	0x00010000
/* 000438 0x80B6E6F8 */ .word	0x00000000
/* 000439 0x80B6E6FC */ .word	0x00000000
/* 000440 0x80B6E700 */ .word	0x00000000
/* 000441 0x80B6E704 */ .word	0x00000008
/* 000442 0x80B6E708 */ .word	0x00000000
/* 000443 0x80B6E70C */ .word	0x00010000
/* 000444 0x80B6E710 */ .word	0x003C003C
/* 000445 0x80B6E714 */ .word	0x00000000
/* 000446 0x80B6E718 */ .word	0x00000000
glabel D_80B6E71C
/* 000447 0x80B6E71C */ .word	0xD2D2D2FF
glabel D_80B6E720
/* 000448 0x80B6E720 */ .word	0x8C8C8CFF
glabel D_80B6E724
/* 000449 0x80B6E724 */ .word	0x00000000
/* 000450 0x80B6E728 */ .word	0x3EA8F5C3
/* 000451 0x80B6E72C */ .word	0x00000000
glabel D_80B6E730
/* 000452 0x80B6E730 */ .word	0xC4DEF812
glabel D_80B6E734
/* 000453 0x80B6E734 */ .byte	0x2C
glabel D_80B6E735
/* 000453 0x80B6E734 */ .byte	0x00
/* 000453 0x80B6E734 */ .short	0x0000
glabel D_80B6E738
/* 000454 0x80B6E738 */ .word	0x00190017
/* 000455 0x80B6E73C */ .word	0x00150013
/* 000456 0x80B6E740 */ .word	0x0011000F
/* 000457 0x80B6E744 */ .word	0x000D000A
glabel D_80B6E748
/* 000458 0x80B6E748 */ .word	0xB0FC0FA0
/* 000459 0x80B6E74C */ .word	0xB10000C8
/* 000460 0x80B6E750 */ .word	0xB104012C
/* 000461 0x80B6E754 */ .word	0x485803E8
/* 000462 0x80B6E758 */ .word	0x00000000
/* 000463 0x80B6E75C */ .word	0x00000000
