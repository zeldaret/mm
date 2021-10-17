.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ani_InitVars
/* 000800 0x80968650 */ .word	0x00BD0400
/* 000801 0x80968654 */ .word	0x00000009
/* 000802 0x80968658 */ .word	0x00C20000
/* 000803 0x8096865C */ .word	0x00000300
/* 000804 0x80968660 */ .word	EnAni_Init
/* 000805 0x80968664 */ .word	EnAni_Destroy
/* 000806 0x80968668 */ .word	EnAni_Update
/* 000807 0x8096866C */ .word	EnAni_Draw
glabel D_80968670
/* 000808 0x80968670 */ .word	0x0A001139
/* 000809 0x80968674 */ .word	0x10010000
/* 000810 0x80968678 */ .word	0x00000000
/* 000811 0x8096867C */ .word	0x00000000
/* 000812 0x80968680 */ .word	0x00000000
/* 000813 0x80968684 */ .word	0xF7CFFFFF
/* 000814 0x80968688 */ .word	0x00000000
/* 000815 0x8096868C */ .word	0x00010100
/* 000816 0x80968690 */ .word	0x001E0028
/* 000817 0x80968694 */ .word	0x00000000
/* 000818 0x80968698 */ .word	0x00000000
glabel D_8096869C
/* 000819 0x8096869C */ .word	0xC858000A
/* 000820 0x809686A0 */ .word	0x30FC0352
glabel D_809686A4
/* 000821 0x809686A4 */ .word	0x44480000
/* 000822 0x809686A8 */ .word	0x43FA0000
/* 000823 0x809686AC */ .word	0x00000000
glabel D_809686B0
/* 000824 0x809686B0 */ .word	0x06006498
/* 000825 0x809686B4 */ .word	0x06006B18
/* 000826 0x809686B8 */ .word	0x06006F18
/* 000827 0x809686BC */ .word	0x00000000
