.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80978BD0
/* 000192 0x80978BD0 */ .word	0x00000004
/* 000193 0x80978BD4 */ .word	func_809788D0
/* 000194 0x80978BD8 */ .word	0x00000000
/* 000195 0x80978BDC */ .word	0x00000000
glabel D_80978BE0
/* 000196 0x80978BE0 */ .word	0x3B23D70A
/* 000197 0x80978BE4 */ .word	0x00000000
/* 000198 0x80978BE8 */ .word	0x00000000
/* 000199 0x80978BEC */ .word	0x00000000
glabel effectSsBlastOverlayInfo
/* 000200 0x80978BF0 */ .word	0x00000300
/* 000201 0x80978BF4 */ .word	0x00000010
/* 000202 0x80978BF8 */ .word	0x00000010
/* 000203 0x80978BFC */ .word	0x00000000
/* 000204 0x80978C00 */ .word	0x00000007
glabel effectSsBlastOverlayRelocations
/* 000205 0x80978C04 */ .word	0x45000030
/* 000206 0x80978C08 */ .word	0x46000040
/* 000207 0x80978C0C */ .word	0x4500003C
/* 000208 0x80978C10 */ .word	0x4600004C
/* 000209 0x80978C14 */ .word	0x45000158
/* 000210 0x80978C18 */ .word	0x4600015C
/* 000211 0x80978C1C */ .word	0x82000004
/* 000212 0x80978C20 */ .word	0x00000000
/* 000213 0x80978C24 */ .word	0x00000000
/* 000214 0x80978C28 */ .word	0x00000000
glabel effectSsBlastOverlayInfoOffset
/* 000215 0x80978C2C */ .word	0x00000040
