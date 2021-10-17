.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Tanron4_InitVars
/* 000832 0x80BE4880 */ .word	0x02670700
/* 000833 0x80BE4884 */ .word	0x02000010
/* 000834 0x80BE4888 */ .word	0x023F0000
/* 000835 0x80BE488C */ .word	0x00000230
/* 000836 0x80BE4890 */ .word	EnTanron4_Init
/* 000837 0x80BE4894 */ .word	EnTanron4_Destroy
/* 000838 0x80BE4898 */ .word	EnTanron4_Update
/* 000839 0x80BE489C */ .word	EnTanron4_Draw
