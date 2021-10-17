.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_801E1050
/* 322916 0x801E1050 */ .word	L801A5E30
/* 322917 0x801E1054 */ .word	L801A5E5C
/* 322918 0x801E1058 */ .word	L801A5E98
/* 322919 0x801E105C */ .word	L801A5EBC
/* 322920 0x801E1060 */ .word	L801A5EF0
/* 322921 0x801E1064 */ .word	L801A5F24
glabel D_801E1068
/* 322922 0x801E1068 */ .word	0x501502F9
/* 322923 0x801E106C */ .word	0x00000000
