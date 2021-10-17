.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Elf_Msg4_InitVars
/* 000340 0x80AFD8D0 */ .word	0x01D70700
/* 000341 0x80AFD8D4 */ .word	0x00000010
/* 000342 0x80AFD8D8 */ .word	0x00010000
/* 000343 0x80AFD8DC */ .word	0x0000014C
/* 000344 0x80AFD8E0 */ .word	ElfMsg4_Init
/* 000345 0x80AFD8E4 */ .word	ElfMsg4_Destroy
/* 000346 0x80AFD8E8 */ .word	ElfMsg4_Update
/* 000347 0x80AFD8EC */ .word	0x00000000
glabel D_80AFD8F0
/* 000348 0x80AFD8F0 */ .word	0xC85803E8
/* 000349 0x80AFD8F4 */ .word	0x30FC03E8
/* 000350 0x80AFD8F8 */ .word	0x00000000
/* 000351 0x80AFD8FC */ .word	0x00000000
