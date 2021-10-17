.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_801DDFF0
/* 319820 0x801DDFF0 */ .word	L801320AC
/* 319821 0x801DDFF4 */ .word	L801320F8
/* 319822 0x801DDFF8 */ .word	L80132114
/* 319823 0x801DDFFC */ .word	L80132140
/* 319824 0x801DE000 */ .word	L8013217C
/* 319825 0x801DE004 */ .word	L80132198
/* 319826 0x801DE008 */ .word	L801321B4
/* 319827 0x801DE00C */ .word	L801321E0
/* 319828 0x801DE010 */ .word	L8013221C
/* 319829 0x801DE014 */ .word	0x00000000
/* 319830 0x801DE018 */ .word	0x00000000
/* 319831 0x801DE01C */ .word	0x00000000
