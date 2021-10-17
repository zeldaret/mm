.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objRoomtimerOverlayInfo
/* 000152 0x80973EB0 */ .word	0x00000240
/* 000153 0x80973EB4 */ .word	0x00000020
/* 000154 0x80973EB8 */ .word	0x00000000
/* 000155 0x80973EBC */ .word	0x00000000
/* 000156 0x80973EC0 */ .word	0x00000009
glabel objRoomtimerOverlayRelocations
/* 000157 0x80973EC4 */ .word	0x4500000C
/* 000158 0x80973EC8 */ .word	0x4600002C
/* 000159 0x80973ECC */ .word	0x450000D0
/* 000160 0x80973ED0 */ .word	0x460000D4
/* 000161 0x80973ED4 */ .word	0x45000134
/* 000162 0x80973ED8 */ .word	0x46000138
/* 000163 0x80973EDC */ .word	0x82000010
/* 000164 0x80973EE0 */ .word	0x82000014
/* 000165 0x80973EE4 */ .word	0x82000018
/* 000166 0x80973EE8 */ .word	0x00000000
glabel objRoomtimerOverlayInfoOffset
/* 000167 0x80973EEC */ .word	0x00000040
