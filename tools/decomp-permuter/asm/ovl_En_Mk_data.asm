.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Mk_InitVars
/* 000984 0x8095A240 */ .word	0x00AE0400
/* 000985 0x8095A244 */ .word	0x00000019
/* 000986 0x8095A248 */ .word	0x00FE0000
/* 000987 0x8095A24C */ .word	0x00000284
/* 000988 0x8095A250 */ .word	EnMk_Init
/* 000989 0x8095A254 */ .word	EnMk_Destroy
/* 000990 0x8095A258 */ .word	EnMk_Update
/* 000991 0x8095A25C */ .word	EnMk_Draw
glabel D_8095A260
/* 000992 0x8095A260 */ .word	0x0A001139
/* 000993 0x8095A264 */ .word	0x10010000
/* 000994 0x8095A268 */ .word	0x00000000
/* 000995 0x8095A26C */ .word	0x00000000
/* 000996 0x8095A270 */ .word	0x00000000
/* 000997 0x8095A274 */ .word	0xF7CFFFFF
/* 000998 0x8095A278 */ .word	0x00000000
/* 000999 0x8095A27C */ .word	0x00010100
/* 001000 0x8095A280 */ .word	0x001E0028
/* 001001 0x8095A284 */ .word	0x00000000
/* 001002 0x8095A288 */ .word	0x00000000
glabel D_8095A28C
/* 001003 0x8095A28C */ .word	0x06001C38
/* 001004 0x8095A290 */ .word	0x06000438
/* 001005 0x8095A294 */ .word	0x060007D8
/* 001006 0x8095A298 */ .word	0x060010F4
/* 001007 0x8095A29C */ .word	0x06001964
glabel D_8095A2A0
/* 001008 0x8095A2A0 */ .word	0x447A0000
/* 001009 0x8095A2A4 */ .word	0xC2C80000
/* 001010 0x8095A2A8 */ .word	0x00000000
/* 001011 0x8095A2AC */ .word	0x00000000
