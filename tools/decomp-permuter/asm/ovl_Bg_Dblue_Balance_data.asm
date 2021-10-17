.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Dblue_Balance_InitVars
/* 001428 0x80B83A00 */ .word	0x021B0100
/* 001429 0x80B83A04 */ .word	0x00000000
/* 001430 0x80B83A08 */ .word	0x01840000
/* 001431 0x80B83A0C */ .word	0x0000022C
/* 001432 0x80B83A10 */ .word	BgDblueBalance_Init
/* 001433 0x80B83A14 */ .word	BgDblueBalance_Destroy
/* 001434 0x80B83A18 */ .word	BgDblueBalance_Update
/* 001435 0x80B83A1C */ .word	BgDblueBalance_Draw
glabel D_80B83A20
/* 001436 0x80B83A20 */ .word	0x0600B8F8
/* 001437 0x80B83A24 */ .word	0x0600BC08
/* 001438 0x80B83A28 */ .word	0x00000010
/* 001439 0x80B83A2C */ .word	0x43B40000
/* 001440 0x80B83A30 */ .word	0x43960000
/* 001441 0x80B83A34 */ .word	BgDblueBalance_Update
/* 001442 0x80B83A38 */ .word	BgDblueBalance_Draw
/* 001443 0x80B83A3C */ .word	0x0600BF48
/* 001444 0x80B83A40 */ .word	0x0600C180
/* 001445 0x80B83A44 */ .word	0x00000010
/* 001446 0x80B83A48 */ .word	0x43520000
/* 001447 0x80B83A4C */ .word	0x433E0000
/* 001448 0x80B83A50 */ .word	func_80B8330C
/* 001449 0x80B83A54 */ .word	BgDblueBalance_Draw
/* 001450 0x80B83A58 */ .word	0x0600C4B8
/* 001451 0x80B83A5C */ .word	0x0600C700
/* 001452 0x80B83A60 */ .word	0x00000010
/* 001453 0x80B83A64 */ .word	0x43340000
/* 001454 0x80B83A68 */ .word	0x43340000
/* 001455 0x80B83A6C */ .word	func_80B8330C
/* 001456 0x80B83A70 */ .word	BgDblueBalance_Draw
glabel D_80B83A74
/* 001457 0x80B83A74 */ .word	0x06001E68
/* 001458 0x80B83A78 */ .word	0x06002E78
/* 001459 0x80B83A7C */ .word	0x00000030
/* 001460 0x80B83A80 */ .word	0x44BB8000
/* 001461 0x80B83A84 */ .word	0x44BB8000
/* 001462 0x80B83A88 */ .word	func_80B83518
/* 001463 0x80B83A8C */ .word	func_80B83758
glabel D_80B83A90
/* 001464 0x80B83A90 */ .short	0x0004
glabel D_80B83A92
/* 001464 0x80B83A90 */ .short	0x0000
glabel D_80B83A94
/* 001465 0x80B83A94 */ .word	0x00020406
glabel D_80B83A98
/* 001466 0x80B83A98 */ .word	0xB0FC0FA0
/* 001467 0x80B83A9C */ .word	0x48580064
