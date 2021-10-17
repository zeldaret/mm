.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Danpei_Movebg_InitVars
/* 000460 0x80AF7510 */ .word	0x01D30100
/* 000461 0x80AF7514 */ .word	0x00000010
/* 000462 0x80AF7518 */ .word	0x00010000
/* 000463 0x80AF751C */ .word	0x000001D8
/* 000464 0x80AF7520 */ .word	BgDanpeiMovebg_Init
/* 000465 0x80AF7524 */ .word	BgDanpeiMovebg_Destroy
/* 000466 0x80AF7528 */ .word	BgDanpeiMovebg_Update
/* 000467 0x80AF752C */ .word	0x00000000
glabel D_80AF7530
/* 000468 0x80AF7530 */ .word	0x00ED01C0
glabel D_80AF7534
/* 000469 0x80AF7534 */ .word	0x06000D10
glabel D_80AF7538
/* 000470 0x80AF7538 */ .word	0x06000F00
glabel D_80AF753C
/* 000471 0x80AF753C */ .word	0xB10005DC
/* 000472 0x80AF7540 */ .word	0xB104044C
/* 000473 0x80AF7544 */ .word	0xB0FC03E8
/* 000474 0x80AF7548 */ .word	0x48580064
/* 000475 0x80AF754C */ .word	0x00000000
