.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ingate_InitVars
/* 000900 0x809548A0 */ .word	0x00A70100
/* 000901 0x809548A4 */ .word	0x00000030
/* 000902 0x809548A8 */ .word	0x017F0000
/* 000903 0x809548AC */ .word	0x00000190
/* 000904 0x809548B0 */ .word	BgIngate_Init
/* 000905 0x809548B4 */ .word	BgIngate_Destroy
/* 000906 0x809548B8 */ .word	BgIngate_Update
/* 000907 0x809548BC */ .word	BgIngate_Draw
