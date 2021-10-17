.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_F40_Block_InitVars
/* 000800 0x80BC4600 */ .word	0x02450100
/* 000801 0x80BC4604 */ .word	0x00000010
/* 000802 0x80BC4608 */ .word	0x005C0000
/* 000803 0x80BC460C */ .word	0x00000170
/* 000804 0x80BC4610 */ .word	BgF40Block_Init
/* 000805 0x80BC4614 */ .word	BgF40Block_Destroy
/* 000806 0x80BC4618 */ .word	BgF40Block_Update
/* 000807 0x80BC461C */ .word	BgF40Block_Draw
glabel D_80BC4620
/* 000808 0x80BC4620 */ .word	0x3F800000
/* 000809 0x80BC4624 */ .word	0x00000000
/* 000810 0x80BC4628 */ .word	0x00000000
/* 000811 0x80BC462C */ .word	0x00000000
/* 000812 0x80BC4630 */ .word	0x3F800000
/* 000813 0x80BC4634 */ .word	0x00000000
/* 000814 0x80BC4638 */ .word	0x00000000
/* 000815 0x80BC463C */ .word	0x00000000
/* 000816 0x80BC4640 */ .word	0x3F800000
/* 000817 0x80BC4644 */ .word	0xBF800000
/* 000818 0x80BC4648 */ .word	0x00000000
/* 000819 0x80BC464C */ .word	0x00000000
/* 000820 0x80BC4650 */ .word	0x00000000
/* 000821 0x80BC4654 */ .word	0xBF800000
/* 000822 0x80BC4658 */ .word	0x00000000
/* 000823 0x80BC465C */ .word	0x00000000
/* 000824 0x80BC4660 */ .word	0x00000000
/* 000825 0x80BC4664 */ .word	0xBF800000
glabel D_80BC4668
/* 000826 0x80BC4668 */ .word	0xB0FC0FA0
/* 000827 0x80BC466C */ .word	0xB1000190
/* 000828 0x80BC4670 */ .word	0xB1040190
/* 000829 0x80BC4674 */ .word	0x48580064
/* 000830 0x80BC4678 */ .word	0x00000000
/* 000831 0x80BC467C */ .word	0x00000000
