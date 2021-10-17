.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_809CB050
/* 000792 0x809CB050 */ .word	0x00000000
/* 000793 0x809CB054 */ .word	0x00000000
/* 000794 0x809CB058 */ .word	0x00000000
glabel En_Syateki_Crow_InitVars
/* 000795 0x809CB05C */ .word	0x01200500
/* 000796 0x809CB060 */ .word	0x08000030
/* 000797 0x809CB064 */ .word	0x00060000
/* 000798 0x809CB068 */ .word	0x0000029C
/* 000799 0x809CB06C */ .word	EnSyatekiCrow_Init
/* 000800 0x809CB070 */ .word	EnSyatekiCrow_Destroy
/* 000801 0x809CB074 */ .word	EnSyatekiCrow_Update
/* 000802 0x809CB078 */ .word	EnSyatekiCrow_Draw
glabel D_809CB07C
/* 000803 0x809CB07C */ .word	0x00000000
/* 000804 0x809CB080 */ .word	0xF7CFFFFF
/* 000805 0x809CB084 */ .word	0x00000000
/* 000806 0x809CB088 */ .word	0xF7CFFFFF
/* 000807 0x809CB08C */ .word	0x00000000
/* 000808 0x809CB090 */ .word	0x00010100
/* 000809 0x809CB094 */ .word	0x01000000
/* 000810 0x809CB098 */ .word	0x003C0000
/* 000811 0x809CB09C */ .word	0x00320064
glabel D_809CB0A0
/* 000812 0x809CB0A0 */ .word	0x03110939
/* 000813 0x809CB0A4 */ .word	0x10000000
/* 000814 0x809CB0A8 */ .word	0x00000001
glabel D_809CB0AC
/* 000815 0x809CB0AC */ .word	D_809CB07C
glabel D_809CB0B0
/* 000816 0x809CB0B0 */ .word	0xB1000BB8
/* 000817 0x809CB0B4 */ .word	0x891F0058
/* 000818 0x809CB0B8 */ .word	0xB874FE0C
/* 000819 0x809CB0BC */ .word	0x305407D0
glabel D_809CB0C0
/* 000820 0x809CB0C0 */ .word	0x00000000
/* 000821 0x809CB0C4 */ .word	0x41A00000
/* 000822 0x809CB0C8 */ .word	0x00000000
glabel D_809CB0CC
/* 000823 0x809CB0CC */ .word	0x00000000
/* 000824 0x809CB0D0 */ .word	0x00000000
/* 000825 0x809CB0D4 */ .word	0x00000000
glabel D_809CB0D8
/* 000826 0x809CB0D8 */ .word	0x451C4000
/* 000827 0x809CB0DC */ .word	0x00000000
/* 000828 0x809CB0E0 */ .word	0x00000000
/* 000829 0x809CB0E4 */ .word	0x00000000
/* 000830 0x809CB0E8 */ .word	0x00000000
/* 000831 0x809CB0EC */ .word	0x00000000
