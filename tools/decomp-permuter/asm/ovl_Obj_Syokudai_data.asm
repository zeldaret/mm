.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Syokudai_InitVars
/* 000804 0x808BCCA0 */ .word	0x00390600
/* 000805 0x808BCCA4 */ .word	0x00000410
/* 000806 0x808BCCA8 */ .word	0x00800000
/* 000807 0x808BCCAC */ .word	0x000001F4
/* 000808 0x808BCCB0 */ .word	ObjSyokudai_Init
/* 000809 0x808BCCB4 */ .word	ObjSyokudai_Destroy
/* 000810 0x808BCCB8 */ .word	ObjSyokudai_Update
/* 000811 0x808BCCBC */ .word	ObjSyokudai_Draw
glabel D_808BCCC0
/* 000812 0x808BCCC0 */ .word	0x09000D39
/* 000813 0x808BCCC4 */ .word	0x20010000
/* 000814 0x808BCCC8 */ .word	0x02000000
/* 000815 0x808BCCCC */ .word	0x00100000
/* 000816 0x808BCCD0 */ .word	0x00000000
/* 000817 0x808BCCD4 */ .word	0xF6CFFFFF
/* 000818 0x808BCCD8 */ .word	0x00000000
/* 000819 0x808BCCDC */ .word	0x00050100
/* 000820 0x808BCCE0 */ .word	0x000C002D
/* 000821 0x808BCCE4 */ .word	0x00000000
/* 000822 0x808BCCE8 */ .word	0x00000000
glabel D_808BCCEC
/* 000823 0x808BCCEC */ .word	0x0A000900
/* 000824 0x808BCCF0 */ .word	0x00010000
/* 000825 0x808BCCF4 */ .word	0x02000000
/* 000826 0x808BCCF8 */ .word	0x00000000
/* 000827 0x808BCCFC */ .word	0x00000000
/* 000828 0x808BCD00 */ .word	0x00000820
/* 000829 0x808BCD04 */ .word	0x00000000
/* 000830 0x808BCD08 */ .word	0x00010000
/* 000831 0x808BCD0C */ .word	0x000F002D
/* 000832 0x808BCD10 */ .word	0x002D0000
/* 000833 0x808BCD14 */ .word	0x00000000
glabel D_808BCD18
/* 000834 0x808BCD18 */ .word	0xC85803E8
/* 000835 0x808BCD1C */ .word	0xB0FC0FA0
/* 000836 0x808BCD20 */ .word	0xB1000320
/* 000837 0x808BCD24 */ .word	0x31040320
glabel D_808BCD28
/* 000838 0x808BCD28 */ .word	0x090B0B00
glabel D_808BCD2C
/* 000839 0x808BCD2C */ .word	0x060003A0
/* 000840 0x808BCD30 */ .word	0x06000B90
/* 000841 0x808BCD34 */ .word	0x06000870
/* 000842 0x808BCD38 */ .word	0x00000000
/* 000843 0x808BCD3C */ .word	0x00000000
