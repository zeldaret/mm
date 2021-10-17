.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Pzlblock_InitVars
/* 000788 0x809A4030 */ .word	0x01020600
/* 000789 0x809A4034 */ .word	0x04000010
/* 000790 0x809A4038 */ .word	0x00010000
/* 000791 0x809A403C */ .word	0x0000017C
/* 000792 0x809A4040 */ .word	ObjPzlblock_Init
/* 000793 0x809A4044 */ .word	ObjPzlblock_Destroy
/* 000794 0x809A4048 */ .word	ObjPzlblock_Update
/* 000795 0x809A404C */ .word	0x00000000
glabel D_809A4050
/* 000796 0x809A4050 */ .word	0x0001FFFF
/* 000797 0x809A4054 */ .word	0x00000000
glabel D_809A4058
/* 000798 0x809A4058 */ .word	0x00000000
/* 000799 0x809A405C */ .word	0x0001FFFF
glabel D_809A4060
/* 000800 0x809A4060 */ .word	0x00030000
/* 000801 0x809A4064 */ .word	0x0501D488
/* 000802 0x809A4068 */ .word	0x0501C228
/* 000803 0x809A406C */ .word	0x023C0000
/* 000804 0x809A4070 */ .word	0x06002CB8
/* 000805 0x809A4074 */ .word	0x06001A58
glabel D_809A4078
/* 000806 0x809A4078 */ .word	0xD0300000
/* 000807 0x809A407C */ .word	0xB0FC0FA0
/* 000808 0x809A4080 */ .word	0xB1000064
/* 000809 0x809A4084 */ .word	0x310400C8
glabel D_809A4088
/* 000810 0x809A4088 */ .word	0xB496FA64
/* 000811 0x809A408C */ .word	0xB4960000
/* 000812 0x809A4090 */ .word	0xFFFFFF00
/* 000813 0x809A4094 */ .word	0x00FFFFFF
/* 000814 0x809A4098 */ .word	0x00FF0000
/* 000815 0x809A409C */ .word	0x00FFFFFF
