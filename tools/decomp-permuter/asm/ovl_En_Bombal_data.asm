.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Bombal_InitVars
/* 000628 0x80C06440 */ .word	0x02820600
/* 000629 0x80C06444 */ .word	0x00000010
/* 000630 0x80C06448 */ .word	0x02800000
/* 000631 0x80C0644C */ .word	0x00002A44
/* 000632 0x80C06450 */ .word	EnBombal_Init
/* 000633 0x80C06454 */ .word	EnBombal_Destroy
/* 000634 0x80C06458 */ .word	EnBombal_Update
/* 000635 0x80C0645C */ .word	EnBombal_Draw
glabel D_80C06460
/* 000636 0x80C06460 */ .word	0x0A000900
/* 000637 0x80C06464 */ .word	0x20010000
/* 000638 0x80C06468 */ .word	0x00000000
/* 000639 0x80C0646C */ .word	0x00000000
/* 000640 0x80C06470 */ .word	0x00000000
/* 000641 0x80C06474 */ .word	0x004138B0
/* 000642 0x80C06478 */ .word	0x00000000
/* 000643 0x80C0647C */ .word	0x00010000
/* 000644 0x80C06480 */ .word	0x003C005A
/* 000645 0x80C06484 */ .word	0xFFCE0000
/* 000646 0x80C06488 */ .word	0x00000000
/* 000647 0x80C0648C */ .word	0x00000000
