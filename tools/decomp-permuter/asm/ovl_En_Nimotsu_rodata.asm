.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enNimotsuOverlayInfo
/* 000220 0x80BE1FF0 */ .word	0x00000310
/* 000221 0x80BE1FF4 */ .word	0x00000050
/* 000222 0x80BE1FF8 */ .word	0x00000010
/* 000223 0x80BE1FFC */ .word	0x00000000
/* 000224 0x80BE2000 */ .word	0x00000009
glabel enNimotsuOverlayRelocations
/* 000225 0x80BE2004 */ .word	0x45000090
/* 000226 0x80BE2008 */ .word	0x4600009C
/* 000227 0x80BE200C */ .word	0x44000200
/* 000228 0x80BE2010 */ .word	0x450002A8
/* 000229 0x80BE2014 */ .word	0x460002AC
/* 000230 0x80BE2018 */ .word	0x82000010
/* 000231 0x80BE201C */ .word	0x82000014
/* 000232 0x80BE2020 */ .word	0x82000018
/* 000233 0x80BE2024 */ .word	0x8200001C
/* 000234 0x80BE2028 */ .word	0x00000000
glabel enNimotsuOverlayInfoOffset
/* 000235 0x80BE202C */ .word	0x00000040
