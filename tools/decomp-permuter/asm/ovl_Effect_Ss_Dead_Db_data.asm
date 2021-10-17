.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80980CD0
/* 000228 0x80980CD0 */ .word	0x00000020
/* 000229 0x80980CD4 */ .word	func_80980940
glabel D_80980CD8
/* 000230 0x80980CD8 */ .word	0x0403F300
/* 000231 0x80980CDC */ .word	0x0403FB00
/* 000232 0x80980CE0 */ .word	0x04040300
/* 000233 0x80980CE4 */ .word	0x04040B00
/* 000234 0x80980CE8 */ .word	0x04041300
/* 000235 0x80980CEC */ .word	0x04041B00
/* 000236 0x80980CF0 */ .word	0x04042300
/* 000237 0x80980CF4 */ .word	0x04042B00
/* 000238 0x80980CF8 */ .word	0x04043300
/* 000239 0x80980CFC */ .word	0x04043B00
glabel D_80980D00
/* 000240 0x80980D00 */ .word	0x3C23D70A
/* 000241 0x80980D04 */ .word	0x00000000
/* 000242 0x80980D08 */ .word	0x00000000
/* 000243 0x80980D0C */ .word	0x00000000
glabel effectSsDeadDbOverlayInfo
/* 000244 0x80980D10 */ .word	0x00000390
/* 000245 0x80980D14 */ .word	0x00000030
/* 000246 0x80980D18 */ .word	0x00000010
/* 000247 0x80980D1C */ .word	0x00000000
/* 000248 0x80980D20 */ .word	0x00000009
glabel effectSsDeadDbOverlayRelocations
/* 000249 0x80980D24 */ .word	0x45000064
/* 000250 0x80980D28 */ .word	0x46000074
/* 000251 0x80980D2C */ .word	0x45000068
/* 000252 0x80980D30 */ .word	0x46000078
/* 000253 0x80980D34 */ .word	0x4500010C
/* 000254 0x80980D38 */ .word	0x46000110
/* 000255 0x80980D3C */ .word	0x45000244
/* 000256 0x80980D40 */ .word	0x46000258
/* 000257 0x80980D44 */ .word	0x82000004
/* 000258 0x80980D48 */ .word	0x00000000
glabel effectSsDeadDbOverlayInfoOffset
/* 000259 0x80980D4C */ .word	0x00000040
