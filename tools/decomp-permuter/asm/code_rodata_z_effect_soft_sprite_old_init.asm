.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DC100
/* 317840 0x801DC100 */ .word	0x3B23D70A
glabel D_801DC104
/* 317841 0x801DC104 */ .word	0xBD8F5C29
glabel D_801DC108
/* 317842 0x801DC108 */ .word	0x3FFEB852
glabel D_801DC10C
/* 317843 0x801DC10C */ .word	0xBE4CCCCD
glabel D_801DC110
/* 317844 0x801DC110 */ .word	0x3FA66666
glabel D_801DC114
/* 317845 0x801DC114 */ .word	0x3E3851EC
/* 317846 0x801DC118 */ .word	0x00000000
/* 317847 0x801DC11C */ .word	0x00000000
