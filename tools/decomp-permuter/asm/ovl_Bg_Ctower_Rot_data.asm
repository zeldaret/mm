.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ctower_Rot_InitVars
/* 000308 0x808E2540 */ .word	0x00610100
/* 000309 0x808E2544 */ .word	0x00000030
/* 000310 0x808E2548 */ .word	0x00880000
/* 000311 0x808E254C */ .word	0x00000168
/* 000312 0x808E2550 */ .word	BgCtowerRot_Init
/* 000313 0x808E2554 */ .word	BgCtowerRot_Destroy
/* 000314 0x808E2558 */ .word	BgCtowerRot_Update
/* 000315 0x808E255C */ .word	BgCtowerRot_Draw
glabel D_808E2560
/* 000316 0x808E2560 */ .word	0x48580064
glabel D_808E2564
/* 000317 0x808E2564 */ .word	0x06012DA0
/* 000318 0x808E2568 */ .word	0x06017220
/* 000319 0x808E256C */ .word	0x060174E0
