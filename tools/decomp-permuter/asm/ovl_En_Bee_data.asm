.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80B5B1F0
/* 000692 0x80B5B1F0 */ .word	0x00000000
glabel En_Bee_InitVars
/* 000693 0x80B5B1F4 */ .word	0x02040500
/* 000694 0x80B5B1F8 */ .word	0x00000005
/* 000695 0x80B5B1FC */ .word	0x01EB0000
/* 000696 0x80B5B200 */ .word	0x00000288
/* 000697 0x80B5B204 */ .word	EnBee_Init
/* 000698 0x80B5B208 */ .word	EnBee_Destroy
/* 000699 0x80B5B20C */ .word	EnBee_Update
/* 000700 0x80B5B210 */ .word	EnBee_Draw
glabel D_80B5B214
/* 000701 0x80B5B214 */ .word	0xF1F1F1F1
/* 000702 0x80B5B218 */ .word	0xF1F100F1
/* 000703 0x80B5B21C */ .word	0xF1F1F1F2
/* 000704 0x80B5B220 */ .word	0xF2F2F1F1
/* 000705 0x80B5B224 */ .word	0xF1F1F1F1
/* 000706 0x80B5B228 */ .word	0x0000F1F1
/* 000707 0x80B5B22C */ .word	0xF1F1F100
/* 000708 0x80B5B230 */ .word	0x000000F1
glabel D_80B5B234
/* 000709 0x80B5B234 */ .word	0x0A110D01
/* 000710 0x80B5B238 */ .word	0x10010000
/* 000711 0x80B5B23C */ .word	0x00000000
/* 000712 0x80B5B240 */ .word	0xF7CFFFFF
/* 000713 0x80B5B244 */ .word	0x08020000
/* 000714 0x80B5B248 */ .word	0xF7CFFFFF
/* 000715 0x80B5B24C */ .word	0x00000000
/* 000716 0x80B5B250 */ .word	0x01010100
/* 000717 0x80B5B254 */ .word	0x0006000D
/* 000718 0x80B5B258 */ .word	0xFFFC0000
/* 000719 0x80B5B25C */ .word	0x00000000
