.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ikana_Bombwall_InitVars
/* 000716 0x80BD5250 */ .word	0x02550100
/* 000717 0x80BD5254 */ .word	0x10000000
/* 000718 0x80BD5258 */ .word	0x02030000
/* 000719 0x80BD525C */ .word	0x000001B0
/* 000720 0x80BD5260 */ .word	BgIkanaBombwall_Init
/* 000721 0x80BD5264 */ .word	BgIkanaBombwall_Destroy
/* 000722 0x80BD5268 */ .word	BgIkanaBombwall_Update
/* 000723 0x80BD526C */ .word	BgIkanaBombwall_Draw
glabel D_80BD5270
/* 000724 0x80BD5270 */ .word	0x0A000900
/* 000725 0x80BD5274 */ .word	0x00010000
/* 000726 0x80BD5278 */ .word	0x00000000
/* 000727 0x80BD527C */ .word	0x00000000
/* 000728 0x80BD5280 */ .word	0x00000000
/* 000729 0x80BD5284 */ .word	0x00000008
/* 000730 0x80BD5288 */ .word	0x00000000
/* 000731 0x80BD528C */ .word	0x00010000
/* 000732 0x80BD5290 */ .word	0x00500050
/* 000733 0x80BD5294 */ .word	0x00000000
/* 000734 0x80BD5298 */ .word	0x00000000
glabel D_80BD529C
/* 000735 0x80BD529C */ .word	0x0A000900
/* 000736 0x80BD52A0 */ .word	0x00010000
/* 000737 0x80BD52A4 */ .word	0x00000000
/* 000738 0x80BD52A8 */ .word	0x00000000
/* 000739 0x80BD52AC */ .word	0x00000000
/* 000740 0x80BD52B0 */ .word	0x00000008
/* 000741 0x80BD52B4 */ .word	0x00000000
/* 000742 0x80BD52B8 */ .word	0x00010000
/* 000743 0x80BD52BC */ .word	0x00320014
/* 000744 0x80BD52C0 */ .word	0x00000000
/* 000745 0x80BD52C4 */ .word	0x00000000
glabel D_80BD52C8
/* 000746 0x80BD52C8 */ .word	0x00200015
/* 000747 0x80BD52CC */ .word	0x000F0008
glabel D_80BD52D0
/* 000748 0x80BD52D0 */ .word	0xB0FC0FA0
/* 000749 0x80BD52D4 */ .word	0xB10001F4
/* 000750 0x80BD52D8 */ .word	0xB10401F4
/* 000751 0x80BD52DC */ .word	0x485803E8
glabel D_80BD52E0
/* 000752 0x80BD52E0 */ .word	0x06000378
/* 000753 0x80BD52E4 */ .word	0x06000048
/* 000754 0x80BD52E8 */ .word	0x00000000
/* 000755 0x80BD52EC */ .word	0x00000000
