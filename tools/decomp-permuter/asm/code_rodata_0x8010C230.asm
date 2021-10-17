.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DDAE0
/* 319496 0x801DDAE0 */ .word	0x3C23D70A
glabel D_801DDAE4
/* 319497 0x801DDAE4 */ .word	0x42652EE0
glabel D_801DDAE8
/* 319498 0x801DDAE8 */ .word	0x43360AAB
glabel D_801DDAEC
/* 319499 0x801DDAEC */ .word	0x42652EE0
glabel D_801DDAF0
/* 319500 0x801DDAF0 */ .word	0x43360AAB
glabel D_801DDAF4
/* 319501 0x801DDAF4 */ .word	0x42652EE0
glabel D_801DDAF8
/* 319502 0x801DDAF8 */ .word	0x42652EE0
glabel D_801DDAFC
/* 319503 0x801DDAFC */ .word	0x43360AAB
