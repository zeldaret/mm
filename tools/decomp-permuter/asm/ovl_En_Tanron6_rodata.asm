.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTanron6OverlayInfo
/* 000084 0x80BE6190 */ .word	0x00000110
/* 000085 0x80BE6194 */ .word	0x00000040
/* 000086 0x80BE6198 */ .word	0x00000000
/* 000087 0x80BE619C */ .word	0x00000000
/* 000088 0x80BE61A0 */ .word	0x00000009
glabel enTanron6OverlayRelocations
/* 000089 0x80BE61A4 */ .word	0x45000034
/* 000090 0x80BE61A8 */ .word	0x4600003C
/* 000091 0x80BE61AC */ .word	0x44000050
/* 000092 0x80BE61B0 */ .word	0x4500007C
/* 000093 0x80BE61B4 */ .word	0x46000080
/* 000094 0x80BE61B8 */ .word	0x82000010
/* 000095 0x80BE61BC */ .word	0x82000014
/* 000096 0x80BE61C0 */ .word	0x82000018
/* 000097 0x80BE61C4 */ .word	0x8200001C
/* 000098 0x80BE61C8 */ .word	0x00000000
glabel enTanron6OverlayInfoOffset
/* 000099 0x80BE61CC */ .word	0x00000040
