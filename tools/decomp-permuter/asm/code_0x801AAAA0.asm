.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel nop_801AAAA0
/* 267256 0x801AAAA0 AFA40000 */ sw	$a0, 0X0($sp)
/* 267257 0x801AAAA4 03E00008 */ jr	$ra
/* 267258 0x801AAAA8 00000000 */ nop
/* 267259 0x801AAAAC 00000000 */ nop
