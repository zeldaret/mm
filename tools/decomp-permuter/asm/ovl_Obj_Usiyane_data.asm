.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Usiyane_InitVars
/* 000624 0x80C08640 */ .word	0x02880600
/* 000625 0x80C08644 */ .word	0x00000020
/* 000626 0x80C08648 */ .word	0x02570000
/* 000627 0x80C0864C */ .word	0x00000748
/* 000628 0x80C08650 */ .word	ObjUsiyane_Init
/* 000629 0x80C08654 */ .word	ObjUsiyane_Destroy
/* 000630 0x80C08658 */ .word	ObjUsiyane_Update
/* 000631 0x80C0865C */ .word	ObjUsiyane_Draw
glabel D_80C08660
/* 000632 0x80C08660 */ .word	0x44480000
/* 000633 0x80C08664 */ .word	0xC46B0000
/* 000634 0x80C08668 */ .word	0x44FA0000
glabel D_80C0866C
/* 000635 0x80C0866C */ .word	0x00000000
/* 000636 0x80C08670 */ .word	0x2AF80000
/* 000637 0x80C08674 */ .word	0x440C0000
/* 000638 0x80C08678 */ .word	0xC4458000
/* 000639 0x80C0867C */ .word	0xC4FA0000
/* 000640 0x80C08680 */ .word	0x00000000
/* 000641 0x80C08684 */ .word	0x2EE00000
/* 000642 0x80C08688 */ .word	0xC3F00000
/* 000643 0x80C0868C */ .word	0xC4430000
/* 000644 0x80C08690 */ .word	0xC4F8C000
/* 000645 0x80C08694 */ .word	0x00000000
/* 000646 0x80C08698 */ .word	0xD8F00000
/* 000647 0x80C0869C */ .word	0xC3EB0000
/* 000648 0x80C086A0 */ .word	0xC4548000
/* 000649 0x80C086A4 */ .word	0x44FA0000
/* 000650 0x80C086A8 */ .word	0x00000000
/* 000651 0x80C086AC */ .word	0xD8F00000
glabel D_80C086B0
/* 000652 0x80C086B0 */ .word	0xB10004B0
/* 000653 0x80C086B4 */ .word	0xB0FC0BB8
/* 000654 0x80C086B8 */ .word	0x31040384
/* 000655 0x80C086BC */ .word	0x00000000
