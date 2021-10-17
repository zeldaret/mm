.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80096B80
/* 023240 0x80096B80 */ .word	D_800982B0
/* 023241 0x80096B84 */ .word	D_800982BC
/* 023242 0x80096B88 */ .word	D_800982D0
/* 023243 0x80096B8C */ .word	D_800982E8
/* 023244 0x80096B90 */ .word	D_80098300
/* 023245 0x80096B94 */ .word	D_80098318
/* 023246 0x80096B98 */ .word	D_80098330
/* 023247 0x80096B9C */ .word	D_80098344
/* 023248 0x80096BA0 */ .word	D_80098358
/* 023249 0x80096BA4 */ .word	D_80098370
/* 023250 0x80096BA8 */ .word	D_80098388
/* 023251 0x80096BAC */ .word	D_800983A0
/* 023252 0x80096BB0 */ .word	D_800983B8
/* 023253 0x80096BB4 */ .word	D_800983CC
/* 023254 0x80096BB8 */ .word	D_800983DC
/* 023255 0x80096BBC */ .word	D_800983F8
/* 023256 0x80096BC0 */ .word	D_80098414
/* 023257 0x80096BC4 */ .word	D_8009842C
glabel D_80096BC8
/* 023258 0x80096BC8 */ .word	D_80098448
/* 023259 0x80096BCC */ .word	D_80098460
/* 023260 0x80096BD0 */ .word	D_80098474
/* 023261 0x80096BD4 */ .word	D_80098488
/* 023262 0x80096BD8 */ .word	D_80098494
/* 023263 0x80096BDC */ .word	D_800984A0
