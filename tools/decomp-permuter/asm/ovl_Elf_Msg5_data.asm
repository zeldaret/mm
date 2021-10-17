.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Elf_Msg5_InitVars
/* 000136 0x80AFDBB0 */ .word	0x01D80100
/* 000137 0x80AFDBB4 */ .word	0x00000010
/* 000138 0x80AFDBB8 */ .word	0x00010000
/* 000139 0x80AFDBBC */ .word	0x00000148
/* 000140 0x80AFDBC0 */ .word	ElfMsg5_Init
/* 000141 0x80AFDBC4 */ .word	ElfMsg5_Destroy
/* 000142 0x80AFDBC8 */ .word	ElfMsg5_Update
/* 000143 0x80AFDBCC */ .word	0x00000000
glabel D_80AFDBD0
/* 000144 0x80AFDBD0 */ .word	0xC85800C8
/* 000145 0x80AFDBD4 */ .word	0x30FC03E8
/* 000146 0x80AFDBD8 */ .word	0x00000000
/* 000147 0x80AFDBDC */ .word	0x00000000
