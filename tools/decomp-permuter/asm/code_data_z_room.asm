.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801C1D10
/* 290964 0x801C1D10 */ .word	0x00000000
/* 290965 0x801C1D14 */ .word	0x00000000
/* 290966 0x801C1D18 */ .word	0x00000000
glabel roomDrawFuncs
/* 290967 0x801C1D1C */ .word	Room_DrawType0Mesh
/* 290968 0x801C1D20 */ .word	Room_DrawType1Mesh
/* 290969 0x801C1D24 */ .word	Room_DrawType2Mesh
/* 290970 0x801C1D28 */ .word	Room_DrawType3Mesh
/* 290971 0x801C1D2C */ .word	0x00000000
