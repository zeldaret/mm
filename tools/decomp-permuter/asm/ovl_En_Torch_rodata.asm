.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTorchOverlayInfo
/* 000048 0x80973610 */ .word	0x00000090
/* 000049 0x80973614 */ .word	0x00000030
/* 000050 0x80973618 */ .word	0x00000000
/* 000051 0x8097361C */ .word	0x00000000
/* 000052 0x80973620 */ .word	0x00000003
glabel enTorchOverlayRelocations
/* 000053 0x80973624 */ .word	0x45000028
/* 000054 0x80973628 */ .word	0x46000038
/* 000055 0x8097362C */ .word	0x82000010
/* 000056 0x80973630 */ .word	0x00000000
/* 000057 0x80973634 */ .word	0x00000000
/* 000058 0x80973638 */ .word	0x00000000
glabel enTorchOverlayInfoOffset
/* 000059 0x8097363C */ .word	0x00000030
