.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Iknin_Susceil_InitVars
/* 000608 0x80C0B0C0 */ .word	0x028E0100
/* 000609 0x80C0B0C4 */ .word	0x00000030
/* 000610 0x80C0B0C8 */ .word	0x02360000
/* 000611 0x80C0B0CC */ .word	0x0000016C
/* 000612 0x80C0B0D0 */ .word	BgIkninSusceil_Init
/* 000613 0x80C0B0D4 */ .word	BgIkninSusceil_Destroy
/* 000614 0x80C0B0D8 */ .word	BgIkninSusceil_Update
/* 000615 0x80C0B0DC */ .word	BgIkninSusceil_Draw
/* 000616 0x80C0B0E0 */ .word	0x00000000
glabel D_80C0B0E4
/* 000617 0x80C0B0E4 */ .word	0x44700000
glabel D_80C0B0E8
/* 000618 0x80C0B0E8 */ .word	0xC3A00000
/* 000619 0x80C0B0EC */ .word	0x00000000
glabel D_80C0B0F0
/* 000620 0x80C0B0F0 */ .word	0x0000070A
/* 000621 0x80C0B0F4 */ .word	0x0A0B0B00
glabel D_80C0B0F8
/* 000622 0x80C0B0F8 */ .word	0x01020001
/* 000623 0x80C0B0FC */ .short	0x0201
glabel D_80C0B0FE
/* 000623 0x80C0B0FC */ .byte	0x02
glabel D_80C0B0FF
/* 000623 0x80C0B0FC */ .byte	0x00
glabel D_80C0B100
/* 000624 0x80C0B100 */ .word	0x48580064
/* 000625 0x80C0B104 */ .word	0x00000000
/* 000626 0x80C0B108 */ .word	0x00000000
/* 000627 0x80C0B10C */ .word	0x00000000
