.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E04E0
/* 322184 0x801E04E0 */ .word	0x3F34FDF4
glabel D_801E04E4
/* 322185 0x801E04E4 */ .word	0x457FFFFC
glabel D_801E04E8
/* 322186 0x801E04E8 */ .word	0x3FFFFF58
glabel D_801E04EC
/* 322187 0x801E04EC */ .word	0x407FFF58
glabel D_801E04F0
/* 322188 0x801E04F0 */ .word	0x3FFFFF58
glabel D_801E04F4
/* 322189 0x801E04F4 */ .word	0x3F7FFF58
glabel D_801E04F8
/* 322190 0x801E04F8 */ .word	0x3F85F3B6
glabel D_801E04FC
/* 322191 0x801E04FC */ .word	0x3FFFFFAC
glabel D_801E0500
/* 322192 0x801E0500 */ .word	0x3F05F3B6
glabel D_801E0504
/* 322193 0x801E0504 */ .word	0x407FFFD6
glabel D_801E0508
/* 322194 0x801E0508 */ .word	0x3E867770
glabel D_801E050C
/* 322195 0x801E050C */ .word	0x3E05F30E
glabel jtbl_D_801E0510
/* 322196 0x801E0510 */ .word	L801971B8
/* 322197 0x801E0514 */ .word	L801971C4
/* 322198 0x801E0518 */ .word	L801971E4
/* 322199 0x801E051C */ .word	L801971F4
/* 322200 0x801E0520 */ .word	L80197334
/* 322201 0x801E0524 */ .word	L80197424
/* 322202 0x801E0528 */ .word	L8019736C
/* 322203 0x801E052C */ .word	L8019736C
/* 322204 0x801E0530 */ .word	L801973FC
glabel D_801E0534
/* 322205 0x801E0534 */ .word	0x46FFFE00
glabel D_801E0538
/* 322206 0x801E0538 */ .word	0x3727C5AC
/* 322207 0x801E053C */ .word	0x00000000
