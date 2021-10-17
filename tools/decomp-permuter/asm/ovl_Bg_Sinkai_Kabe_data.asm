.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Sinkai_Kabe_InitVars
/* 000316 0x80B6DB50 */ .word	0x020C0700
/* 000317 0x80B6DB54 */ .word	0x00000010
/* 000318 0x80B6DB58 */ .word	0x01F40000
/* 000319 0x80B6DB5C */ .word	0x00000170
/* 000320 0x80B6DB60 */ .word	BgSinkaiKabe_Init
/* 000321 0x80B6DB64 */ .word	BgSinkaiKabe_Destroy
/* 000322 0x80B6DB68 */ .word	BgSinkaiKabe_Update
/* 000323 0x80B6DB6C */ .word	0x00000000
glabel D_80B6DB70
/* 000324 0x80B6DB70 */ .word	0x00000000
/* 000325 0x80B6DB74 */ .word	0x00000000
/* 000326 0x80B6DB78 */ .word	0x00000000
/* 000327 0x80B6DB7C */ .word	0x00000000
