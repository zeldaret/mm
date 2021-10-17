.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Fr_InitVars
/* 000072 0x808FC670 */ .word	0x00730700
/* 000073 0x808FC674 */ .word	0x40000000
/* 000074 0x808FC678 */ .word	0x00010000
/* 000075 0x808FC67C */ .word	0x00000144
/* 000076 0x808FC680 */ .word	EnFr_Init
/* 000077 0x808FC684 */ .word	EnFr_Destroy
/* 000078 0x808FC688 */ .word	EnFr_Update
/* 000079 0x808FC68C */ .word	0x00000000
