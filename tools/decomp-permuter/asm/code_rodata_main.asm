.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel schedThreadName
/* 321708 0x801DFD70 */ .word	0x73636865
/* 321709 0x801DFD74 */ .word	0x64000000
glabel audioThreadName
/* 321710 0x801DFD78 */ .word	0x61756469
/* 321711 0x801DFD7C */ .word	0x6F000000
glabel padmgrThreadName
/* 321712 0x801DFD80 */ .word	0x7061646D
/* 321713 0x801DFD84 */ .word	0x67720000
glabel graphThreadName
/* 321714 0x801DFD88 */ .word	0x67726170
/* 321715 0x801DFD8C */ .word	0x68000000
