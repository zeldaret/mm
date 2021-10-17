.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objKinokoOverlayInfo
/* 000232 0x80BB4AA0 */ .word	0x00000370
/* 000233 0x80BB4AA4 */ .word	0x00000020
/* 000234 0x80BB4AA8 */ .word	0x00000010
/* 000235 0x80BB4AAC */ .word	0x00000000
/* 000236 0x80BB4AB0 */ .word	0x0000000C
glabel objKinokoOverlayRelocations
/* 000237 0x80BB4AB4 */ .word	0x45000050
/* 000238 0x80BB4AB8 */ .word	0x46000058
/* 000239 0x80BB4ABC */ .word	0x45000144
/* 000240 0x80BB4AC0 */ .word	0x4600014C
/* 000241 0x80BB4AC4 */ .word	0x45000154
/* 000242 0x80BB4AC8 */ .word	0x46000158
/* 000243 0x80BB4ACC */ .word	0x45000170
/* 000244 0x80BB4AD0 */ .word	0x4600018C
/* 000245 0x80BB4AD4 */ .word	0x82000010
/* 000246 0x80BB4AD8 */ .word	0x82000014
/* 000247 0x80BB4ADC */ .word	0x82000018
/* 000248 0x80BB4AE0 */ .word	0x8200001C
/* 000249 0x80BB4AE4 */ .word	0x00000000
/* 000250 0x80BB4AE8 */ .word	0x00000000
glabel objKinokoOverlayInfoOffset
/* 000251 0x80BB4AEC */ .word	0x00000050
