.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgBotihasiraOverlayInfo
/* 000172 0x80B28330 */ .word	0x00000250
/* 000173 0x80B28334 */ .word	0x00000050
/* 000174 0x80B28338 */ .word	0x00000010
/* 000175 0x80B2833C */ .word	0x00000000
/* 000176 0x80B28340 */ .word	0x0000000A
glabel bgBotihasiraOverlayRelocations
/* 000177 0x80B28344 */ .word	0x45000064
/* 000178 0x80B28348 */ .word	0x4600006C
/* 000179 0x80B2834C */ .word	0x45000070
/* 000180 0x80B28350 */ .word	0x46000074
/* 000181 0x80B28354 */ .word	0x45000078
/* 000182 0x80B28358 */ .word	0x4600007C
/* 000183 0x80B2835C */ .word	0x82000010
/* 000184 0x80B28360 */ .word	0x82000014
/* 000185 0x80B28364 */ .word	0x82000018
/* 000186 0x80B28368 */ .word	0x8200001C
glabel bgBotihasiraOverlayInfoOffset
/* 000187 0x80B2836C */ .word	0x00000040
