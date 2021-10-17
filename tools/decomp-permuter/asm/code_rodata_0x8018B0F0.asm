.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E02B0
/* 322044 0x801E02B0 */ .word	0x3EA8F5C3
glabel D_801E02B4
/* 322045 0x801E02B4 */ .word	0x3F28F5C3
glabel D_801E02B8
/* 322046 0x801E02B8 */ .word	0x488001E0
glabel jtbl_D_801E02BC
/* 322047 0x801E02BC */ .word	L8018CF08
/* 322048 0x801E02C0 */ .word	L8018CECC
/* 322049 0x801E02C4 */ .word	L8018CE64
/* 322050 0x801E02C8 */ .word	L8018CD90
/* 322051 0x801E02CC */ .word	L8018CD08
glabel D_801E02D0
/* 322052 0x801E02D0 */ .word	0x4A2FC800
glabel jtbl_D_801E02D4
/* 322053 0x801E02D4 */ .word	L8018E374
/* 322054 0x801E02D8 */ .word	L8018E38C
/* 322055 0x801E02DC */ .word	L8018E550
/* 322056 0x801E02E0 */ .word	L8018E584
/* 322057 0x801E02E4 */ .word	L8018E5B8
/* 322058 0x801E02E8 */ .word	L8018E5EC
/* 322059 0x801E02EC */ .word	L8018E620
/* 322060 0x801E02F0 */ .word	L8018E654
/* 322061 0x801E02F4 */ .word	L8018E75C
/* 322062 0x801E02F8 */ .word	L8018E864
/* 322063 0x801E02FC */ .word	0x00000000
