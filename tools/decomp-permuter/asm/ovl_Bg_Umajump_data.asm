.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Umajump_InitVars
/* 000560 0x8091A7F0 */ .word	0x007C0600
/* 000561 0x8091A7F4 */ .word	0x00000000
/* 000562 0x8091A7F8 */ .word	0x00010000
/* 000563 0x8091A7FC */ .word	0x0000016C
/* 000564 0x8091A800 */ .word	BgUmajump_Init
/* 000565 0x8091A804 */ .word	BgUmajump_Destroy
/* 000566 0x8091A808 */ .word	BgUmajump_Update
/* 000567 0x8091A80C */ .word	0x00000000
glabel D_8091A810
/* 000568 0x8091A810 */ .word	0xB10004B0
/* 000569 0x8091A814 */ .word	0xB104012C
/* 000570 0x8091A818 */ .word	0x48580064
/* 000571 0x8091A81C */ .word	0x00000000
