.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enEndingHero5OverlayInfo
/* 000220 0x80C23C30 */ .word	0x00000310
/* 000221 0x80C23C34 */ .word	0x00000040
/* 000222 0x80C23C38 */ .word	0x00000020
/* 000223 0x80C23C3C */ .word	0x00000000
/* 000224 0x80C23C40 */ .word	0x00000012
glabel enEndingHero5OverlayRelocations
/* 000225 0x80C23C44 */ .word	0x44000094
/* 000226 0x80C23C48 */ .word	0x450000C0
/* 000227 0x80C23C4C */ .word	0x460000C8
/* 000228 0x80C23C50 */ .word	0x4500018C
/* 000229 0x80C23C54 */ .word	0x460001AC
/* 000230 0x80C23C58 */ .word	0x45000200
/* 000231 0x80C23C5C */ .word	0x46000208
/* 000232 0x80C23C60 */ .word	0x450002E0
/* 000233 0x80C23C64 */ .word	0x460002E4
/* 000234 0x80C23C68 */ .word	0x82000010
/* 000235 0x80C23C6C */ .word	0x82000014
/* 000236 0x80C23C70 */ .word	0x82000018
/* 000237 0x80C23C74 */ .word	0x8200001C
/* 000238 0x80C23C78 */ .word	0xC2000000
/* 000239 0x80C23C7C */ .word	0xC2000004
/* 000240 0x80C23C80 */ .word	0xC2000008
/* 000241 0x80C23C84 */ .word	0xC200000C
/* 000242 0x80C23C88 */ .word	0xC2000010
glabel enEndingHero5OverlayInfoOffset
/* 000243 0x80C23C8C */ .word	0x00000060
