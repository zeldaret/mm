.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Kujiya_InitVars
/* 000776 0x80BB1500 */ .word	0x02390400
/* 000777 0x80BB1504 */ .word	0x08000009
/* 000778 0x80BB1508 */ .word	0x02630000
/* 000779 0x80BB150C */ .word	0x0000014C
/* 000780 0x80BB1510 */ .word	EnKujiya_Init
/* 000781 0x80BB1514 */ .word	EnKujiya_Destroy
/* 000782 0x80BB1518 */ .word	EnKujiya_Update
/* 000783 0x80BB151C */ .word	EnKujiya_Draw
