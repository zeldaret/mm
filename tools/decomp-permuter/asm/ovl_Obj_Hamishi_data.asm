.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Hamishi_InitVars
/* 000728 0x809A1A80 */ .word	0x00FC0600
/* 000729 0x809A1A84 */ .word	0x00000010
/* 000730 0x809A1A88 */ .word	0x00020000
/* 000731 0x809A1A8C */ .word	0x000001A4
/* 000732 0x809A1A90 */ .word	ObjHamishi_Init
/* 000733 0x809A1A94 */ .word	ObjHamishi_Destroy
/* 000734 0x809A1A98 */ .word	ObjHamishi_Update
/* 000735 0x809A1A9C */ .word	ObjHamishi_Draw
glabel D_809A1AA0
/* 000736 0x809A1AA0 */ .word	0x0C000D39
/* 000737 0x809A1AA4 */ .word	0x20010000
/* 000738 0x809A1AA8 */ .word	0x00000000
/* 000739 0x809A1AAC */ .word	0x00000000
/* 000740 0x809A1AB0 */ .word	0x00000000
/* 000741 0x809A1AB4 */ .word	0x81C37FB6
/* 000742 0x809A1AB8 */ .word	0x00000000
/* 000743 0x809A1ABC */ .word	0x00010100
/* 000744 0x809A1AC0 */ .word	0x00320046
/* 000745 0x809A1AC4 */ .word	0x00000000
/* 000746 0x809A1AC8 */ .word	0x00000000
glabel D_809A1ACC
/* 000747 0x809A1ACC */ .word	0x0000000C
/* 000748 0x809A1AD0 */ .word	0x003CFF00
glabel D_809A1AD4
/* 000749 0x809A1AD4 */ .word	0x00910087
/* 000750 0x809A1AD8 */ .word	0x00730055
/* 000751 0x809A1ADC */ .word	0x004B0035
/* 000752 0x809A1AE0 */ .word	0x002D0028
/* 000753 0x809A1AE4 */ .word	0x00230000
glabel D_809A1AE8
/* 000754 0x809A1AE8 */ .word	0xC8580190
/* 000755 0x809A1AEC */ .word	0xB0FC07D0
/* 000756 0x809A1AF0 */ .word	0xB10000FA
/* 000757 0x809A1AF4 */ .word	0x310401F4
/* 000758 0x809A1AF8 */ .word	0x00000000
/* 000759 0x809A1AFC */ .word	0x00000000
