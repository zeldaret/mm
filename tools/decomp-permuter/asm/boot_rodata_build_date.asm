.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800994D0
/* 025884 0x800994D0 */ .word	0x7A656C64
/* 025885 0x800994D4 */ .word	0x61407372
/* 025886 0x800994D8 */ .word	0x64343400
glabel D_800994DC
/* 025887 0x800994DC */ .word	0x30302D30
/* 025888 0x800994E0 */ .word	0x372D3331
/* 025889 0x800994E4 */ .word	0x2031373A
/* 025890 0x800994E8 */ .word	0x30343A31
/* 025891 0x800994EC */ .word	0x36000000
/* 025892 0x800994F0 */ .word	0x00000000
/* 025893 0x800994F4 */ .word	0x00000000
/* 025894 0x800994F8 */ .word	0x00000000
/* 025895 0x800994FC */ .word	0x00000000
