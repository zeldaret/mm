.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enInvisibleRuppeOverlayInfo
/* 000184 0x80C25B80 */ .word	0x00000290
/* 000185 0x80C25B84 */ .word	0x00000050
/* 000186 0x80C25B88 */ .word	0x00000000
/* 000187 0x80C25B8C */ .word	0x00000000
/* 000188 0x80C25B90 */ .word	0x0000000A
glabel enInvisibleRuppeOverlayRelocations
/* 000189 0x80C25B94 */ .word	0x45000128
/* 000190 0x80C25B98 */ .word	0x4600012C
/* 000191 0x80C25B9C */ .word	0x450001E4
/* 000192 0x80C25BA0 */ .word	0x460001EC
/* 000193 0x80C25BA4 */ .word	0x450001FC
/* 000194 0x80C25BA8 */ .word	0x46000200
/* 000195 0x80C25BAC */ .word	0x4400026C
/* 000196 0x80C25BB0 */ .word	0x82000010
/* 000197 0x80C25BB4 */ .word	0x82000014
/* 000198 0x80C25BB8 */ .word	0x82000018
glabel enInvisibleRuppeOverlayInfoOffset
/* 000199 0x80C25BBC */ .word	0x00000040
