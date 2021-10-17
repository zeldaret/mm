.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Demo_Effect_InitVars
/* 000724 0x808CE290 */ .word	0x00480100
/* 000725 0x808CE294 */ .word	0x00000030
/* 000726 0x808CE298 */ .word	0x00010000
/* 000727 0x808CE29C */ .word	0x0000017C
/* 000728 0x808CE2A0 */ .word	DemoEffect_Init
/* 000729 0x808CE2A4 */ .word	DemoEffect_Destroy
/* 000730 0x808CE2A8 */ .word	DemoEffect_Update
/* 000731 0x808CE2AC */ .word	0x00000000
glabel D_808CE2B0
/* 000732 0x808CE2B0 */ .word	0xC8C800FF
/* 000733 0x808CE2B4 */ .word	0x286432FF
/* 000734 0x808CE2B8 */ .word	0x000000FF
/* 000735 0x808CE2BC */ .word	0xFFFF5000
glabel D_808CE2C0
/* 000736 0x808CE2C0 */ .word	0x00840084
/* 000737 0x808CE2C4 */ .word	0x00840084
/* 000738 0x808CE2C8 */ .word	0x00010001
/* 000739 0x808CE2CC */ .word	0x00010001
/* 000740 0x808CE2D0 */ .word	0x00010000
glabel D_808CE2D4
/* 000741 0x808CE2D4 */ .byte	0x01
glabel D_808CE2D5
/* 000741 0x808CE2D4 */ .byte	0x01
/* 000741 0x808CE2D4 */ .short	0x0200
/* 000742 0x808CE2D8 */ .word	0x01010200
/* 000743 0x808CE2DC */ .word	0x01020002
/* 000744 0x808CE2E0 */ .word	0x01000100
/* 000745 0x808CE2E4 */ .word	0x02000202
/* 000746 0x808CE2E8 */ .word	0x00000000
/* 000747 0x808CE2EC */ .word	0x00000000
