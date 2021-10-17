.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel effStkOverlayInfo
/* 000216 0x80BF10F0 */ .word	0x00000330
/* 000217 0x80BF10F4 */ .word	0x00000020
/* 000218 0x80BF10F8 */ .word	0x00000010
/* 000219 0x80BF10FC */ .word	0x00000000
/* 000220 0x80BF1100 */ .word	0x00000010
glabel effStkOverlayRelocations
/* 000221 0x80BF1104 */ .word	0x45000024
/* 000222 0x80BF1108 */ .word	0x46000028
/* 000223 0x80BF110C */ .word	0x450000C0
/* 000224 0x80BF1110 */ .word	0x460000C4
/* 000225 0x80BF1114 */ .word	0x450000E4
/* 000226 0x80BF1118 */ .word	0x460000E8
/* 000227 0x80BF111C */ .word	0x45000108
/* 000228 0x80BF1120 */ .word	0x4600010C
/* 000229 0x80BF1124 */ .word	0x4500012C
/* 000230 0x80BF1128 */ .word	0x46000130
/* 000231 0x80BF112C */ .word	0x4500020C
/* 000232 0x80BF1130 */ .word	0x46000210
/* 000233 0x80BF1134 */ .word	0x82000010
/* 000234 0x80BF1138 */ .word	0x82000014
/* 000235 0x80BF113C */ .word	0x82000018
/* 000236 0x80BF1140 */ .word	0x8200001C
/* 000237 0x80BF1144 */ .word	0x00000000
/* 000238 0x80BF1148 */ .word	0x00000000
glabel effStkOverlayInfoOffset
/* 000239 0x80BF114C */ .word	0x00000060
