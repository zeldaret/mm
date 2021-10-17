.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enJcMatoOverlayInfo
/* 000228 0x80B9E270 */ .word	0x00000310
/* 000229 0x80B9E274 */ .word	0x00000080
/* 000230 0x80B9E278 */ .word	0x00000000
/* 000231 0x80B9E27C */ .word	0x00000000
/* 000232 0x80B9E280 */ .word	0x0000000E
glabel enJcMatoOverlayRelocations
/* 000233 0x80B9E284 */ .word	0x450000E8
/* 000234 0x80B9E288 */ .word	0x460000EC
/* 000235 0x80B9E28C */ .word	0x4500018C
/* 000236 0x80B9E290 */ .word	0x46000194
/* 000237 0x80B9E294 */ .word	0x450001A4
/* 000238 0x80B9E298 */ .word	0x460001AC
/* 000239 0x80B9E29C */ .word	0x440001D4
/* 000240 0x80B9E2A0 */ .word	0x44000254
/* 000241 0x80B9E2A4 */ .word	0x450002EC
/* 000242 0x80B9E2A8 */ .word	0x460002F0
/* 000243 0x80B9E2AC */ .word	0x82000010
/* 000244 0x80B9E2B0 */ .word	0x82000014
/* 000245 0x80B9E2B4 */ .word	0x82000018
/* 000246 0x80B9E2B8 */ .word	0x8200001C
glabel enJcMatoOverlayInfoOffset
/* 000247 0x80B9E2BC */ .word	0x00000050
