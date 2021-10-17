.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel itemBHeartOverlayInfo
/* 000236 0x808BD1A0 */ .word	0x00000370
/* 000237 0x808BD1A4 */ .word	0x00000030
/* 000238 0x808BD1A8 */ .word	0x00000010
/* 000239 0x808BD1AC */ .word	0x00000000
/* 000240 0x808BD1B0 */ .word	0x00000009
glabel itemBHeartOverlayRelocations
/* 000241 0x808BD1B4 */ .word	0x45000038
/* 000242 0x808BD1B8 */ .word	0x46000040
/* 000243 0x808BD1BC */ .word	0x45000068
/* 000244 0x808BD1C0 */ .word	0x4600006C
/* 000245 0x808BD1C4 */ .word	0x440000E0
/* 000246 0x808BD1C8 */ .word	0x82000010
/* 000247 0x808BD1CC */ .word	0x82000014
/* 000248 0x808BD1D0 */ .word	0x82000018
/* 000249 0x808BD1D4 */ .word	0x8200001C
/* 000250 0x808BD1D8 */ .word	0x00000000
glabel itemBHeartOverlayInfoOffset
/* 000251 0x808BD1DC */ .word	0x00000040
