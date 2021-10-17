.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Minislime_InitVars
/* 001972 0x809857C0 */ .word	0x00D90900
/* 001973 0x809857C4 */ .word	0x00000235
/* 001974 0x809857C8 */ .word	0x01280000
/* 001975 0x809857CC */ .word	0x000001AC
/* 001976 0x809857D0 */ .word	EnMinislime_Init
/* 001977 0x809857D4 */ .word	EnMinislime_Destroy
/* 001978 0x809857D8 */ .word	EnMinislime_Update
/* 001979 0x809857DC */ .word	0x00000000
glabel D_809857E0
/* 001980 0x809857E0 */ .word	0x0A100838
/* 001981 0x809857E4 */ .word	0x10010000
/* 001982 0x809857E8 */ .word	0x00000000
/* 001983 0x809857EC */ .word	0xF7CFFFFF
/* 001984 0x809857F0 */ .word	0x00040000
/* 001985 0x809857F4 */ .word	0xF7CFFFFF
/* 001986 0x809857F8 */ .word	0x00000000
/* 001987 0x809857FC */ .word	0x09050100
/* 001988 0x80985800 */ .word	0x0036003C
/* 001989 0x80985804 */ .word	0xFFE20000
/* 001990 0x80985808 */ .word	0x00000000
glabel D_8098580C
/* 001991 0x8098580C */ .word	0x04000028
/* 001992 0x80985810 */ .word	0x00281E00
glabel D_80985814
/* 001993 0x80985814 */ .word	0x000101F1
/* 001994 0x80985818 */ .word	0x010101E0
/* 001995 0x8098581C */ .word	0xF101F121
/* 001996 0x80985820 */ .word	0x3101F101
/* 001997 0x80985824 */ .word	0x01010001
/* 001998 0x80985828 */ .word	0x00000101
/* 001999 0x8098582C */ .word	0x01000000
/* 002000 0x80985830 */ .word	0x000000F1
/* 002001 0x80985834 */ .word	0x00000000
/* 002002 0x80985838 */ .word	0x00000000
/* 002003 0x8098583C */ .word	0x00000000
