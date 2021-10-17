.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel itemInboxOverlayInfo
/* 000076 0x80945620 */ .word	0x00000110
/* 000077 0x80945624 */ .word	0x00000020
/* 000078 0x80945628 */ .word	0x00000000
/* 000079 0x8094562C */ .word	0x00000000
/* 000080 0x80945630 */ .word	0x00000006
glabel itemInboxOverlayRelocations
/* 000081 0x80945634 */ .word	0x4500000C
/* 000082 0x80945638 */ .word	0x46000010
/* 000083 0x8094563C */ .word	0x82000010
/* 000084 0x80945640 */ .word	0x82000014
/* 000085 0x80945644 */ .word	0x82000018
/* 000086 0x80945648 */ .word	0x8200001C
glabel itemInboxOverlayInfoOffset
/* 000087 0x8094564C */ .word	0x00000030
