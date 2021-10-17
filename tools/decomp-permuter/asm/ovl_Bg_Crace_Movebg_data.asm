.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Crace_Movebg_InitVars
/* 000612 0x80A71080 */ .word	0x017E0100
/* 000613 0x80A71084 */ .word	0x00000010
/* 000614 0x80A71088 */ .word	0x018A0000
/* 000615 0x80A7108C */ .word	0x00000194
/* 000616 0x80A71090 */ .word	BgCraceMovebg_Init
/* 000617 0x80A71094 */ .word	BgCraceMovebg_Destroy
/* 000618 0x80A71098 */ .word	BgCraceMovebg_Update
/* 000619 0x80A7109C */ .word	BgCraceMovebg_Draw
glabel D_80A710A0
/* 000620 0x80A710A0 */ .word	0x00000000
glabel D_80A710A4
/* 000621 0x80A710A4 */ .word	0x00000000
glabel D_80A710A8
/* 000622 0x80A710A8 */ .word	0x485803E8
glabel D_80A710AC
/* 000623 0x80A710AC */ .word	0x00000000
/* 000624 0x80A710B0 */ .word	0x00000000
/* 000625 0x80A710B4 */ .word	0x3F800000
/* 000626 0x80A710B8 */ .word	0x00000000
/* 000627 0x80A710BC */ .word	0x00000000
