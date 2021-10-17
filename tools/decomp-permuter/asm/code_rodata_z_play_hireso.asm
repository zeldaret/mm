.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DFC50
/* 321636 0x801DFC50 */ .word	0x452AAAAB
glabel D_801DFC54
/* 321637 0x801DFC54 */ .word	0x42360B61
glabel D_801DFC58
/* 321638 0x801DFC58 */ .word	0x452AAAAB
glabel D_801DFC5C
/* 321639 0x801DFC5C */ .word	0x42360B61
