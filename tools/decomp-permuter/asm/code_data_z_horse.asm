.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801BDA70
/* 286700 0x801BDA70 */ .word	0x002D0000
glabel D_801BDA74
/* 286701 0x801BDA74 */ .word	0x00400000
glabel D_801BDA78
/* 286702 0x801BDA78 */ .word	0x00350000
glabel D_801BDA7C
/* 286703 0x801BDA7C */ .word	0x006A0000
/* 286704 0x801BDA80 */ .word	0x00450000
/* 286705 0x801BDA84 */ .word	0x00000000
/* 286706 0x801BDA88 */ .word	0x00370000
/* 286707 0x801BDA8C */ .word	0x00380000
/* 286708 0x801BDA90 */ .word	0x00220000
/* 286709 0x801BDA94 */ .word	0x00530000
/* 286710 0x801BDA98 */ .word	0x001C0000
glabel D_801BDA9C
/* 286711 0x801BDA9C */ .word	0x00000000
glabel D_801BDAA0
/* 286712 0x801BDAA0 */ .word	0x00000000
glabel D_801BDAA4
/* 286713 0x801BDAA4 */ .word	0x00000000
glabel D_801BDAA8
/* 286714 0x801BDAA8 */ .short	0x002D
glabel D_801BDAAA
/* 286714 0x801BDAA8 */ .short	0x0004
glabel D_801BDAAC
/* 286715 0x801BDAAC */ .short	0x0037
glabel D_801BDAAE
/* 286715 0x801BDAAC */ .short	0x0000
glabel D_801BDAB0
/* 286716 0x801BDAB0 */ .short	0x0038
glabel D_801BDAB2
/* 286716 0x801BDAB0 */ .short	0x0000
glabel D_801BDAB4
/* 286717 0x801BDAB4 */ .short	0x001C
glabel D_801BDAB6
/* 286717 0x801BDAB4 */ .short	0x0000
/* 286718 0x801BDAB8 */ .word	0x00000000
/* 286719 0x801BDABC */ .word	0x00000000
