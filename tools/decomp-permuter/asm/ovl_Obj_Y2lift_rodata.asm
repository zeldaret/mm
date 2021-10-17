.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objY2liftOverlayInfo
/* 000192 0x80B9A950 */ .word	0x000002D0
/* 000193 0x80B9A954 */ .word	0x00000030
/* 000194 0x80B9A958 */ .word	0x00000000
/* 000195 0x80B9A95C */ .word	0x00000000
/* 000196 0x80B9A960 */ .word	0x00000006
glabel objY2liftOverlayRelocations
/* 000197 0x80B9A964 */ .word	0x45000010
/* 000198 0x80B9A968 */ .word	0x46000014
/* 000199 0x80B9A96C */ .word	0x82000010
/* 000200 0x80B9A970 */ .word	0x82000014
/* 000201 0x80B9A974 */ .word	0x82000018
/* 000202 0x80B9A978 */ .word	0x8200001C
glabel objY2liftOverlayInfoOffset
/* 000203 0x80B9A97C */ .word	0x00000030
