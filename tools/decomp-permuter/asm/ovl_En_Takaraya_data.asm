.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Takaraya_InitVars
/* 000980 0x80ADFAE0 */ .word	0x01C10400
/* 000981 0x80ADFAE4 */ .word	0x00000039
/* 000982 0x80ADFAE8 */ .word	0x01290000
/* 000983 0x80ADFAEC */ .word	0x000002BC
/* 000984 0x80ADFAF0 */ .word	EnTakaraya_Init
/* 000985 0x80ADFAF4 */ .word	EnTakaraya_Destroy
/* 000986 0x80ADFAF8 */ .word	EnTakaraya_Update
/* 000987 0x80ADFAFC */ .word	EnTakaraya_Draw
glabel D_80ADFB00
/* 000988 0x80ADFB00 */ .word	0x06006F58
/* 000989 0x80ADFB04 */ .word	0x06007358
/* 000990 0x80ADFB08 */ .word	0x06007758
/* 000991 0x80ADFB0C */ .word	0x06007358
glabel D_80ADFB10
/* 000992 0x80ADFB10 */ .word	0x06007B58
/* 000993 0x80ADFB14 */ .word	0x06007F58
/* 000994 0x80ADFB18 */ .word	0x06007758
/* 000995 0x80ADFB1C */ .word	0x06007F58
glabel D_80ADFB20
/* 000996 0x80ADFB20 */ .word	0x801F0006
/* 000997 0x80ADFB24 */ .word	0x305403E8
glabel D_80ADFB28
/* 000998 0x80ADFB28 */ .word	0x00000000
glabel D_80ADFB2C
/* 000999 0x80ADFB2C */ .word	0x076D076E
/* 001000 0x80ADFB30 */ .word	0x076F076C
/* 001001 0x80ADFB34 */ .word	0x076D0000
glabel D_80ADFB38
/* 001002 0x80ADFB38 */ .byte	0x05
glabel D_80ADFB39
/* 001002 0x80ADFB38 */ .byte	0x05
/* 001002 0x80ADFB38 */ .short	0x0C05
/* 001003 0x80ADFB3C */ .word	0x04042A29
/* 001004 0x80ADFB40 */ .word	0x05050000
glabel D_80ADFB44
/* 001005 0x80ADFB44 */ .word	0x07750776
/* 001006 0x80ADFB48 */ .word	0x07770774
/* 001007 0x80ADFB4C */ .word	0x07750000
glabel D_80ADFB50
/* 001008 0x80ADFB50 */ .word	0x07710772
/* 001009 0x80ADFB54 */ .word	0x07730770
/* 001010 0x80ADFB58 */ .word	0x07710000
/* 001011 0x80ADFB5C */ .word	0x00000000
