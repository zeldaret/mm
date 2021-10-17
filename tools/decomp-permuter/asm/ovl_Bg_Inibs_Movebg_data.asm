.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Inibs_Movebg_InitVars
/* 000076 0x80B96540 */ .word	0x02270100
/* 000077 0x80B96544 */ .word	0x00000030
/* 000078 0x80B96548 */ .word	0x020C0000
/* 000079 0x80B9654C */ .word	0x00000168
/* 000080 0x80B96550 */ .word	BgInibsMovebg_Init
/* 000081 0x80B96554 */ .word	BgInibsMovebg_Destroy
/* 000082 0x80B96558 */ .word	func_800BDFB0
/* 000083 0x80B9655C */ .word	BgInibsMovebg_Draw
glabel D_80B96560
/* 000084 0x80B96560 */ .word	0x060062D8
/* 000085 0x80B96564 */ .word	0x06001DC0
glabel D_80B96568
/* 000086 0x80B96568 */ .word	0x06006140
/* 000087 0x80B9656C */ .word	0x06001C10
glabel D_80B96570
/* 000088 0x80B96570 */ .word	0x06006858
/* 000089 0x80B96574 */ .word	0x06002598
glabel D_80B96578
/* 000090 0x80B96578 */ .word	0x485803E8
/* 000091 0x80B9657C */ .word	0x00000000
