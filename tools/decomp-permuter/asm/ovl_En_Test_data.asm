.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Test_InitVars
/* 000784 0x808637B0 */ .word	0x00010700
/* 000785 0x808637B4 */ .word	0x00000010
/* 000786 0x808637B8 */ .word	0x00010000
/* 000787 0x808637BC */ .word	0x000006BC
/* 000788 0x808637C0 */ .word	EnTest_Init
/* 000789 0x808637C4 */ .word	EnTest_Destroy
/* 000790 0x808637C8 */ .word	EnTest_Update
/* 000791 0x808637CC */ .word	EnTest_Draw
