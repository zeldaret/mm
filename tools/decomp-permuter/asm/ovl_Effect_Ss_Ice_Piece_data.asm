.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097F070
/* 000232 0x8097F070 */ .word	0x0000001A
/* 000233 0x8097F074 */ .word	func_8097ECD0
/* 000234 0x8097F078 */ .word	0x00000000
/* 000235 0x8097F07C */ .word	0x00000000
glabel D_8097F080
/* 000236 0x8097F080 */ .word	0x3C23D70A
glabel D_8097F084
/* 000237 0x8097F084 */ .word	0x3F59999A
/* 000238 0x8097F088 */ .word	0x00000000
/* 000239 0x8097F08C */ .word	0x00000000
glabel effectSsIcePieceOverlayInfo
/* 000240 0x8097F090 */ .word	0x000003A0
/* 000241 0x8097F094 */ .word	0x00000010
/* 000242 0x8097F098 */ .word	0x00000010
/* 000243 0x8097F09C */ .word	0x00000000
/* 000244 0x8097F0A0 */ .word	0x00000009
glabel effectSsIcePieceOverlayRelocations
/* 000245 0x8097F0A4 */ .word	0x45000014
/* 000246 0x8097F0A8 */ .word	0x46000018
/* 000247 0x8097F0AC */ .word	0x45000034
/* 000248 0x8097F0B0 */ .word	0x46000038
/* 000249 0x8097F0B4 */ .word	0x45000168
/* 000250 0x8097F0B8 */ .word	0x4600016C
/* 000251 0x8097F0BC */ .word	0x45000350
/* 000252 0x8097F0C0 */ .word	0x46000354
/* 000253 0x8097F0C4 */ .word	0x82000004
/* 000254 0x8097F0C8 */ .word	0x00000000
glabel effectSsIcePieceOverlayInfoOffset
/* 000255 0x8097F0CC */ .word	0x00000040
