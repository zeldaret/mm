.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel oceffWipeOverlayInfo
/* 000824 0x80977190 */ .word	0x000004D0
/* 000825 0x80977194 */ .word	0x00000800
/* 000826 0x80977198 */ .word	0x00000010
/* 000827 0x8097719C */ .word	0x00000010
/* 000828 0x809771A0 */ .word	0x00000013
glabel oceffWipeOverlayRelocations
/* 000829 0x809771A4 */ .word	0x450001B0
/* 000830 0x809771A8 */ .word	0x4600020C
/* 000831 0x809771AC */ .word	0x450001FC
/* 000832 0x809771B0 */ .word	0x46000208
/* 000833 0x809771B4 */ .word	0x45000200
/* 000834 0x809771B8 */ .word	0x46000204
/* 000835 0x809771BC */ .word	0x450002FC
/* 000836 0x809771C0 */ .word	0x46000300
/* 000837 0x809771C4 */ .word	0x4500041C
/* 000838 0x809771C8 */ .word	0x46000420
/* 000839 0x809771CC */ .word	0x450004A0
/* 000840 0x809771D0 */ .word	0x460004A4
/* 000841 0x809771D4 */ .word	0x82000010
/* 000842 0x809771D8 */ .word	0x82000014
/* 000843 0x809771DC */ .word	0x82000018
/* 000844 0x809771E0 */ .word	0x8200001C
/* 000845 0x809771E4 */ .word	0x820006BC
/* 000846 0x809771E8 */ .word	0x8200072C
/* 000847 0x809771EC */ .word	0x820007BC
/* 000848 0x809771F0 */ .word	0x00000000
/* 000849 0x809771F4 */ .word	0x00000000
/* 000850 0x809771F8 */ .word	0x00000000
glabel oceffWipeOverlayInfoOffset
/* 000851 0x809771FC */ .word	0x00000070
