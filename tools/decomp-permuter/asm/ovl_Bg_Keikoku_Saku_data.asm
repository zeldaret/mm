.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Keikoku_Saku_InitVars
/* 000224 0x80A53B50 */ .word	0x016C0700
/* 000225 0x80A53B54 */ .word	0x00000000
/* 000226 0x80A53B58 */ .word	0x017E0000
/* 000227 0x80A53B5C */ .word	0x00000164
/* 000228 0x80A53B60 */ .word	BgKeikokuSaku_Init
/* 000229 0x80A53B64 */ .word	BgKeikokuSaku_Destroy
/* 000230 0x80A53B68 */ .word	BgKeikokuSaku_Update
/* 000231 0x80A53B6C */ .word	BgKeikokuSaku_Draw
