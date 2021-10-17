.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel sFaultDrawContext
/* 023264 0x80096BE0 */ .word	sFaultDrawerStruct
glabel sFaultDrawerDefault
/* 023265 0x80096BE4 */ .word	0x803DA800
/* 023266 0x80096BE8 */ .word	0x014000F0
/* 023267 0x80096BEC */ .word	0x001000DF
/* 023268 0x80096BF0 */ .word	0x00160129
/* 023269 0x80096BF4 */ .word	0xFFFF0000
/* 023270 0x80096BF8 */ .word	0x00160010
/* 023271 0x80096BFC */ .word	faultDrawFont
/* 023272 0x80096C00 */ .word	0x08080000
/* 023273 0x80096C04 */ .word	0x0001F801
/* 023274 0x80096C08 */ .word	0x07C1FFC1
/* 023275 0x80096C0C */ .word	0x003FF83F
/* 023276 0x80096C10 */ .word	0x07FFFFFF
/* 023277 0x80096C14 */ .word	0x7BDFB5AD
/* 023278 0x80096C18 */ .word	0x00000000
/* 023279 0x80096C1C */ .word	0x00000000
