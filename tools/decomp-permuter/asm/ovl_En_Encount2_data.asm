.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Encount2_InitVars
/* 000604 0x808E1ED0 */ .word	0x005F0600
/* 000605 0x808E1ED4 */ .word	0x00000010
/* 000606 0x808E1ED8 */ .word	0x02800000
/* 000607 0x808E1EDC */ .word	0x00002A70
/* 000608 0x808E1EE0 */ .word	EnEncount2_Init
/* 000609 0x808E1EE4 */ .word	EnEncount2_Destroy
/* 000610 0x808E1EE8 */ .word	EnEncount2_Update
/* 000611 0x808E1EEC */ .word	EnEncount2_Draw
glabel D_808E1EF0
/* 000612 0x808E1EF0 */ .word	0x00000000
/* 000613 0x808E1EF4 */ .word	0xF7CFFFFF
/* 000614 0x808E1EF8 */ .word	0x00000000
/* 000615 0x808E1EFC */ .word	0xF7CFFFFF
/* 000616 0x808E1F00 */ .word	0x00000000
/* 000617 0x808E1F04 */ .word	0x00010100
/* 000618 0x808E1F08 */ .word	0x01000000
/* 000619 0x808E1F0C */ .word	0x00000000
/* 000620 0x808E1F10 */ .word	0x00000001
glabel D_808E1F14
/* 000621 0x808E1F14 */ .word	0x0C000939
/* 000622 0x808E1F18 */ .word	0x10000000
/* 000623 0x808E1F1C */ .word	0x00000001
/* 000624 0x808E1F20 */ .word	D_808E1EF0
glabel D_808E1F24
/* 000625 0x808E1F24 */ .word	0xF0F000F0
/* 000626 0x808E1F28 */ .word	0xE1E100E1
/* 000627 0x808E1F2C */ .word	0xF0F0F0E1
/* 000628 0x808E1F30 */ .word	0xE1E1F0F0
/* 000629 0x808E1F34 */ .word	0xE1F0F0F0
/* 000630 0x808E1F38 */ .word	0x0000E1F0
/* 000631 0x808E1F3C */ .word	0xF0000000
/* 000632 0x808E1F40 */ .word	0x000000F0
/* 000633 0x808E1F44 */ .word	0x00000000
/* 000634 0x808E1F48 */ .word	0x00000000
/* 000635 0x808E1F4C */ .word	0x00000000
