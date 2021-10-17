.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Zob_InitVars
/* 001744 0x80BA10B0 */ .word	0x02310400
/* 001745 0x80BA10B4 */ .word	0x00000009
/* 001746 0x80BA10B8 */ .word	0x02110000
/* 001747 0x80BA10BC */ .word	0x00000318
/* 001748 0x80BA10C0 */ .word	EnZob_Init
/* 001749 0x80BA10C4 */ .word	EnZob_Destroy
/* 001750 0x80BA10C8 */ .word	EnZob_Update
/* 001751 0x80BA10CC */ .word	EnZob_Draw
glabel D_80BA10D0
/* 001752 0x80BA10D0 */ .word	0x0A001139
/* 001753 0x80BA10D4 */ .word	0x10010000
/* 001754 0x80BA10D8 */ .word	0x00000000
/* 001755 0x80BA10DC */ .word	0x00000000
/* 001756 0x80BA10E0 */ .word	0x00000000
/* 001757 0x80BA10E4 */ .word	0xF7CFFFFF
/* 001758 0x80BA10E8 */ .word	0x00000000
/* 001759 0x80BA10EC */ .word	0x00010100
/* 001760 0x80BA10F0 */ .word	0x001E0028
/* 001761 0x80BA10F4 */ .word	0x00000000
/* 001762 0x80BA10F8 */ .word	0x00000000
glabel D_80BA10FC
/* 001763 0x80BA10FC */ .word	0x060027D0
/* 001764 0x80BA1100 */ .word	0x06002B38
/* 001765 0x80BA1104 */ .word	0x060037A0
/* 001766 0x80BA1108 */ .word	0x060043C4
/* 001767 0x80BA110C */ .word	0x06005224
/* 001768 0x80BA1110 */ .word	0x06005E90
/* 001769 0x80BA1114 */ .word	0x06006998
/* 001770 0x80BA1118 */ .word	0x06011144
/* 001771 0x80BA111C */ .word	0x06001FD4
glabel D_80BA1120
/* 001772 0x80BA1120 */ .word	0x43960000
/* 001773 0x80BA1124 */ .word	0x44610000
/* 001774 0x80BA1128 */ .word	0x00000000
/* 001775 0x80BA112C */ .word	0x00000000
