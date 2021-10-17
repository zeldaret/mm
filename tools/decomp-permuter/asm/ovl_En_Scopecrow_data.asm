.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Scopecrow_InitVars
/* 000724 0x80BCDB50 */ .word	0x024D0400
/* 000725 0x80BCDB54 */ .word	0x00000030
/* 000726 0x80BCDB58 */ .word	0x00060000
/* 000727 0x80BCDB5C */ .word	0x00000268
/* 000728 0x80BCDB60 */ .word	EnScopecrow_Init
/* 000729 0x80BCDB64 */ .word	EnScopecrow_Destroy
/* 000730 0x80BCDB68 */ .word	EnScopecrow_Update
/* 000731 0x80BCDB6C */ .word	EnScopecrow_Draw
glabel D_80BCDB70
/* 000732 0x80BCDB70 */ .word	0x00000000
/* 000733 0x80BCDB74 */ .word	0x00000000
/* 000734 0x80BCDB78 */ .word	0x00000000
/* 000735 0x80BCDB7C */ .word	0xF7CFFFFF
/* 000736 0x80BCDB80 */ .word	0x00000000
/* 000737 0x80BCDB84 */ .word	0x00010100
/* 000738 0x80BCDB88 */ .word	0x01000000
/* 000739 0x80BCDB8C */ .word	0x003C0000
/* 000740 0x80BCDB90 */ .word	0x00320064
glabel D_80BCDB94
/* 000741 0x80BCDB94 */ .word	0x03000939
/* 000742 0x80BCDB98 */ .word	0x10000000
/* 000743 0x80BCDB9C */ .word	0x00000001
glabel D_80BCDBA0
/* 000744 0x80BCDBA0 */ .word	D_80BCDB70
/* 000745 0x80BCDBA4 */ .word	0x00000000
/* 000746 0x80BCDBA8 */ .word	0x00000000
/* 000747 0x80BCDBAC */ .word	0x00000000
