.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enRiverSoundOverlayInfo
/* 000144 0x808A8070 */ .word	0x00000210
/* 000145 0x808A8074 */ .word	0x00000030
/* 000146 0x808A8078 */ .word	0x00000000
/* 000147 0x808A807C */ .word	0x00000000
/* 000148 0x808A8080 */ .word	0x00000005
glabel enRiverSoundOverlayRelocations
/* 000149 0x808A8084 */ .word	0x450001E0
/* 000150 0x808A8088 */ .word	0x460001F4
/* 000151 0x808A808C */ .word	0x82000010
/* 000152 0x808A8090 */ .word	0x82000018
/* 000153 0x808A8094 */ .word	0x8200001C
/* 000154 0x808A8098 */ .word	0x00000000
glabel enRiverSoundOverlayInfoOffset
/* 000155 0x808A809C */ .word	0x00000030
