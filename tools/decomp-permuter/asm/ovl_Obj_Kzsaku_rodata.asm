.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objKzsakuOverlayInfo
/* 000220 0x80C08DF0 */ .word	0x00000350
/* 000221 0x80C08DF4 */ .word	0x00000020
/* 000222 0x80C08DF8 */ .word	0x00000000
/* 000223 0x80C08DFC */ .word	0x00000000
/* 000224 0x80C08E00 */ .word	0x0000000E
glabel objKzsakuOverlayRelocations
/* 000225 0x80C08E04 */ .word	0x44000080
/* 000226 0x80C08E08 */ .word	0x44000090
/* 000227 0x80C08E0C */ .word	0x450000E4
/* 000228 0x80C08E10 */ .word	0x460000E8
/* 000229 0x80C08E14 */ .word	0x44000124
/* 000230 0x80C08E18 */ .word	0x4500013C
/* 000231 0x80C08E1C */ .word	0x46000140
/* 000232 0x80C08E20 */ .word	0x440001DC
/* 000233 0x80C08E24 */ .word	0x45000210
/* 000234 0x80C08E28 */ .word	0x46000214
/* 000235 0x80C08E2C */ .word	0x82000010
/* 000236 0x80C08E30 */ .word	0x82000014
/* 000237 0x80C08E34 */ .word	0x82000018
/* 000238 0x80C08E38 */ .word	0x8200001C
glabel objKzsakuOverlayInfoOffset
/* 000239 0x80C08E3C */ .word	0x00000050
