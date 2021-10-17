.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel __libm_qnan_f
/* 025852 0x80099450 */ .word	0x7F810000
/* 025853 0x80099454 */ .word	0x00000000
/* 025854 0x80099458 */ .word	0x00000000
/* 025855 0x8009945C */ .word	0x00000000
