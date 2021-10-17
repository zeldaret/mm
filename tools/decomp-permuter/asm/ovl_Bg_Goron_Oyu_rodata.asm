.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgGoronOyuOverlayInfo
/* 000452 0x80B40790 */ .word	0x000006E0
/* 000453 0x80B40794 */ .word	0x00000030
/* 000454 0x80B40798 */ .word	0x00000000
/* 000455 0x80B4079C */ .word	0x00000000
/* 000456 0x80B407A0 */ .word	0x00000014
glabel bgGoronOyuOverlayRelocations
/* 000457 0x80B407A4 */ .word	0x45000000
/* 000458 0x80B407A8 */ .word	0x46000008
/* 000459 0x80B407AC */ .word	0x45000028
/* 000460 0x80B407B0 */ .word	0x4600002C
/* 000461 0x80B407B4 */ .word	0x4400005C
/* 000462 0x80B407B8 */ .word	0x44000068
/* 000463 0x80B407BC */ .word	0x450000B8
/* 000464 0x80B407C0 */ .word	0x460000BC
/* 000465 0x80B407C4 */ .word	0x4400011C
/* 000466 0x80B407C8 */ .word	0x4400014C
/* 000467 0x80B407CC */ .word	0x45000154
/* 000468 0x80B407D0 */ .word	0x46000158
/* 000469 0x80B407D4 */ .word	0x4400054C
/* 000470 0x80B407D8 */ .word	0x4400056C
/* 000471 0x80B407DC */ .word	0x4400058C
/* 000472 0x80B407E0 */ .word	0x44000600
/* 000473 0x80B407E4 */ .word	0x82000010
/* 000474 0x80B407E8 */ .word	0x82000014
/* 000475 0x80B407EC */ .word	0x82000018
/* 000476 0x80B407F0 */ .word	0x8200001C
/* 000477 0x80B407F4 */ .word	0x00000000
/* 000478 0x80B407F8 */ .word	0x00000000
glabel bgGoronOyuOverlayInfoOffset
/* 000479 0x80B407FC */ .word	0x00000070
