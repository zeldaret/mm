.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD5C0
/* 319168 0x801DD5C0 */ .word	0x3C23D70A
glabel D_801DD5C4
/* 319169 0x801DD5C4 */ .word	0x7E967699
glabel D_801DD5C8
/* 319170 0x801DD5C8 */ .word	0x3EAAAAAB
glabel D_801DD5CC
/* 319171 0x801DD5CC */ .word	0x3C03126F
glabel D_801DD5D0
/* 319172 0x801DD5D0 */ .word	0x3C03126F
glabel D_801DD5D4
/* 319173 0x801DD5D4 */ .word	0x3C03126F
glabel D_801DD5D8
/* 319174 0x801DD5D8 */ .word	0x3C03126F
glabel minCylinderIntersectAmount
/* 319175 0x801DD5DC */ .word	0x3C03126F
glabel D_801DD5E0
/* 319176 0x801DD5E0 */ .word	0x3C03126F
glabel D_801DD5E4
/* 319177 0x801DD5E4 */ .word	0x3C03126F
glabel D_801DD5E8
/* 319178 0x801DD5E8 */ .word	0x3C03126F
glabel D_801DD5EC
/* 319179 0x801DD5EC */ .word	0x3C03126F
glabel D_801DD5F0
/* 319180 0x801DD5F0 */ .word	0x3C03126F
glabel D_801DD5F4
/* 319181 0x801DD5F4 */ .word	0x3C03126F
glabel D_801DD5F8
/* 319182 0x801DD5F8 */ .word	0x3C03126F
glabel D_801DD5FC
/* 319183 0x801DD5FC */ .word	0x3C03126F
