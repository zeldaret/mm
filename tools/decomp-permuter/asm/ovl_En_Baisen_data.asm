.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Baisen_InitVars
/* 000576 0x80BE8DF0 */ .word	0x026C0400
/* 000577 0x80BE8DF4 */ .word	0x00000009
/* 000578 0x80BE8DF8 */ .word	0x02470000
/* 000579 0x80BE8DFC */ .word	0x000002FC
/* 000580 0x80BE8E00 */ .word	EnBaisen_Init
/* 000581 0x80BE8E04 */ .word	EnBaisen_Destroy
/* 000582 0x80BE8E08 */ .word	EnBaisen_Update
/* 000583 0x80BE8E0C */ .word	EnBaisen_Draw
glabel D_80BE8E10
/* 000584 0x80BE8E10 */ .word	0x0A000039
/* 000585 0x80BE8E14 */ .word	0x20010000
/* 000586 0x80BE8E18 */ .word	0x00000000
/* 000587 0x80BE8E1C */ .word	0x00000000
/* 000588 0x80BE8E20 */ .word	0x00000000
/* 000589 0x80BE8E24 */ .word	0xF7CFFFFF
/* 000590 0x80BE8E28 */ .word	0x00000000
/* 000591 0x80BE8E2C */ .word	0x00000100
/* 000592 0x80BE8E30 */ .word	0x0014003C
/* 000593 0x80BE8E34 */ .word	0x00000000
/* 000594 0x80BE8E38 */ .word	0x00000000
glabel D_80BE8E3C
/* 000595 0x80BE8E3C */ .word	0x2ABD2ABB
/* 000596 0x80BE8E40 */ .word	0x2AD52AD6
/* 000597 0x80BE8E44 */ .word	0x2AD72AD8
/* 000598 0x80BE8E48 */ .word	0x2AC60000
glabel D_80BE8E4C
/* 000599 0x80BE8E4C */ .word	0x060011C0
/* 000600 0x80BE8E50 */ .word	0x060008B4
/* 000601 0x80BE8E54 */ .word	0x06008198
glabel D_80BE8E58
/* 000602 0x80BE8E58 */ .word	0x00000000
/* 000603 0x80BE8E5C */ .word	0x00000000
