.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DCBB0
/* 318524 0x801DCBB0 */ .word	0x6163746F
/* 318525 0x801DCBB4 */ .word	0x725F646C
/* 318526 0x801DCBB8 */ .word	0x6674626C
/* 318527 0x801DCBBC */ .word	0x73202575
/* 318528 0x801DCBC0 */ .word	0x0A000000
glabel D_801DCBC4
/* 318529 0x801DCBC4 */ .word	0x4E6F2E20
/* 318530 0x801DCBC8 */ .word	0x52616D53
/* 318531 0x801DCBCC */ .word	0x74617274
/* 318532 0x801DCBD0 */ .word	0x2D205261
/* 318533 0x801DCBD4 */ .word	0x6D456E64
/* 318534 0x801DCBD8 */ .word	0x20636E20
/* 318535 0x801DCBDC */ .word	0x204E616D
/* 318536 0x801DCBE0 */ .word	0x650A0000
glabel D_801DCBE4
/* 318537 0x801DCBE4 */ .word	0x25336420
/* 318538 0x801DCBE8 */ .word	0x25303878
/* 318539 0x801DCBEC */ .word	0x2D253038
/* 318540 0x801DCBF0 */ .word	0x78202533
/* 318541 0x801DCBF4 */ .word	0x64202573
/* 318542 0x801DCBF8 */ .word	0x0A000000
glabel D_801DCBFC
/* 318543 0x801DCBFC */ .word	0x00000000
