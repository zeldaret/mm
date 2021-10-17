.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Eff_Kamejima_Wave_InitVars
/* 000340 0x80BCF070 */ .word	0x024F0700
/* 000341 0x80BCF074 */ .word	0x00000010
/* 000342 0x80BCF078 */ .word	0x02290000
/* 000343 0x80BCF07C */ .word	0x00000150
/* 000344 0x80BCF080 */ .word	EffKamejimaWave_Init
/* 000345 0x80BCF084 */ .word	EffKamejimaWave_Destroy
/* 000346 0x80BCF088 */ .word	EffKamejimaWave_Update
/* 000347 0x80BCF08C */ .word	0x00000000
glabel D_80BCF090
/* 000348 0x80BCF090 */ .word	0xFFF0FFFF
/* 000349 0x80BCF094 */ .word	0xFFFFFFFF
/* 000350 0x80BCF098 */ .word	0xFFF0E6FF
/* 000351 0x80BCF09C */ .word	0x8CAADCFF
glabel D_80BCF0A0
/* 000352 0x80BCF0A0 */ .word	0x82505AFF
/* 000353 0x80BCF0A4 */ .word	0x5A7882FF
/* 000354 0x80BCF0A8 */ .word	0x825046FF
/* 000355 0x80BCF0AC */ .word	0x283C6EFF
