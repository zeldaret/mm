.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Elf_Msg6_InitVars
/* 000848 0x80BA22E0 */ .word	0x02320700
/* 000849 0x80BA22E4 */ .word	0x00000010
/* 000850 0x80BA22E8 */ .word	0x00010000
/* 000851 0x80BA22EC */ .word	0x00000148
/* 000852 0x80BA22F0 */ .word	ElfMsg6_Init
/* 000853 0x80BA22F4 */ .word	ElfMsg6_Destroy
/* 000854 0x80BA22F8 */ .word	ElfMsg6_Update
/* 000855 0x80BA22FC */ .word	0x00000000
glabel D_80BA2300
/* 000856 0x80BA2300 */ .word	0xC85803E8
/* 000857 0x80BA2304 */ .word	0x30FC03E8
/* 000858 0x80BA2308 */ .word	0x00000000
/* 000859 0x80BA230C */ .word	0x00000000
