.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Ah_InitVars
/* 000620 0x80C1DDC0 */ .word	0x029F0400
/* 000621 0x80C1DDC4 */ .word	0x00000009
/* 000622 0x80C1DDC8 */ .word	0x00070000
/* 000623 0x80C1DDCC */ .word	0x000002A0
/* 000624 0x80C1DDD0 */ .word	DmAh_Init
/* 000625 0x80C1DDD4 */ .word	DmAh_Destroy
/* 000626 0x80C1DDD8 */ .word	DmAh_Update
/* 000627 0x80C1DDDC */ .word	DmAh_Draw
glabel D_80C1DDE0
/* 000628 0x80C1DDE0 */ .word	0x06001860
/* 000629 0x80C1DDE4 */ .word	0x3F800000
/* 000630 0x80C1DDE8 */ .word	0x0000FFFF
/* 000631 0x80C1DDEC */ .word	0x00000000
/* 000632 0x80C1DDF0 */ .word	0x06000DDC
/* 000633 0x80C1DDF4 */ .word	0x3F800000
/* 000634 0x80C1DDF8 */ .word	0x0000FFFF
/* 000635 0x80C1DDFC */ .word	0x00000000
glabel D_80C1DE00
/* 000636 0x80C1DE00 */ .word	0x00000000
/* 000637 0x80C1DE04 */ .word	0x00000000
/* 000638 0x80C1DE08 */ .word	0x00000000
/* 000639 0x80C1DE0C */ .word	0x00000000
/* 000640 0x80C1DE10 */ .word	0x00000000
glabel D_80C1DE14
/* 000641 0x80C1DE14 */ .word	0x447A0000
/* 000642 0x80C1DE18 */ .word	0x00000000
/* 000643 0x80C1DE1C */ .word	0x00000000
glabel D_80C1DE20
/* 000644 0x80C1DE20 */ .word	0x06008D70
/* 000645 0x80C1DE24 */ .word	0x06009570
glabel D_80C1DE28
/* 000646 0x80C1DE28 */ .word	0x06006D70
/* 000647 0x80C1DE2C */ .word	0x06007570
/* 000648 0x80C1DE30 */ .word	0x06007D70
/* 000649 0x80C1DE34 */ .word	0x06007570
/* 000650 0x80C1DE38 */ .word	0x06008570
/* 000651 0x80C1DE3C */ .word	0x00000000
