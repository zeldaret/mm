.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel lightPositionalMapFuncs
/* 287740 0x801BEAB0 */ .word	Lights_MapPositional
/* 287741 0x801BEAB4 */ .word	Lights_MapDirectional
/* 287742 0x801BEAB8 */ .word	Lights_MapPositional
glabel lightDirectionalMapFuncs
/* 287743 0x801BEABC */ .word	Lights_MapPositionalWithReference
/* 287744 0x801BEAC0 */ .word	Lights_MapDirectional
/* 287745 0x801BEAC4 */ .word	Lights_MapPositionalWithReference
/* 287746 0x801BEAC8 */ .word	0x00000000
/* 287747 0x801BEACC */ .word	0x00000000
