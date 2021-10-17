.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800990C0
/* 025624 0x800990C0 */ .word	0xBEAAAAAB
/* 025625 0x800990C4 */ .word	0x3E4CCCCD
/* 025626 0x800990C8 */ .word	0xBE124925
/* 025627 0x800990CC */ .word	0x3DE38E39
/* 025628 0x800990D0 */ .word	0xBDBA2E8C
/* 025629 0x800990D4 */ .word	0x3D9D89D9
/* 025630 0x800990D8 */ .word	0xBD888889
/* 025631 0x800990DC */ .word	0x3D70F0F1
/* 025632 0x800990E0 */ .word	0x00000000
glabel D_800990E4
/* 025633 0x800990E4 */ .word	0x3ED413CC
glabel D_800990E8
/* 025634 0x800990E8 */ .word	0x401A827A
glabel D_800990EC
/* 025635 0x800990EC */ .word	0x3FC90FDB
glabel D_800990F0
/* 025636 0x800990F0 */ .word	0x3F490FDB
glabel D_800990F4
/* 025637 0x800990F4 */ .word	0x3FC90FDB
glabel D_800990F8
/* 025638 0x800990F8 */ .word	0xBFC90FDB
glabel D_800990FC
/* 025639 0x800990FC */ .word	0x3FC90FDB
glabel D_80099100
/* 025640 0x80099100 */ .word	0xBFC90FDB
glabel D_80099104
/* 025641 0x80099104 */ .word	0x40490FDB
glabel D_80099108
/* 025642 0x80099108 */ .word	0x40490FDB
glabel D_8009910C
/* 025643 0x8009910C */ .word	0x3FC90FDB
