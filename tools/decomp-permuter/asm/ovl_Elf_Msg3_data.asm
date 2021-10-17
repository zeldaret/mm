.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Elf_Msg3_InitVars
/* 000300 0x80A2D1C0 */ .word	0x01460700
/* 000301 0x80A2D1C4 */ .word	0x00000010
/* 000302 0x80A2D1C8 */ .word	0x00010000
/* 000303 0x80A2D1CC */ .word	0x00000148
/* 000304 0x80A2D1D0 */ .word	ElfMsg3_Init
/* 000305 0x80A2D1D4 */ .word	ElfMsg3_Destroy
/* 000306 0x80A2D1D8 */ .word	ElfMsg3_Update
/* 000307 0x80A2D1DC */ .word	0x00000000
glabel D_80A2D1E0
/* 000308 0x80A2D1E0 */ .word	0xC85803E8
/* 000309 0x80A2D1E4 */ .word	0x30FC03E8
/* 000310 0x80A2D1E8 */ .word	0x00000000
/* 000311 0x80A2D1EC */ .word	0x00000000
