.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ms_InitVars
/* 000344 0x80952B80 */ .word	0x00A50400
/* 000345 0x80952B84 */ .word	0x00000009
/* 000346 0x80952B88 */ .word	0x00F40000
/* 000347 0x80952B8C */ .word	0x00000244
/* 000348 0x80952B90 */ .word	EnMs_Init
/* 000349 0x80952B94 */ .word	EnMs_Destroy
/* 000350 0x80952B98 */ .word	EnMs_Update
/* 000351 0x80952B9C */ .word	EnMs_Draw
glabel D_80952BA0
/* 000352 0x80952BA0 */ .word	0x0A000939
/* 000353 0x80952BA4 */ .word	0x01000000
/* 000354 0x80952BA8 */ .word	0x00000000
/* 000355 0x80952BAC */ .word	0x00000000
/* 000356 0x80952BB0 */ .word	0x00000000
/* 000357 0x80952BB4 */ .word	0xF7CFFFFF
/* 000358 0x80952BB8 */ .word	0x00000000
/* 000359 0x80952BBC */ .word	0x00010100
/* 000360 0x80952BC0 */ .word	0x00160025
/* 000361 0x80952BC4 */ .word	0x00000000
/* 000362 0x80952BC8 */ .word	0x00000000
glabel D_80952BCC
/* 000363 0x80952BCC */ .word	0x801F0002
/* 000364 0x80952BD0 */ .word	0x305401F4
/* 000365 0x80952BD4 */ .word	0x00000000
/* 000366 0x80952BD8 */ .word	0x00000000
/* 000367 0x80952BDC */ .word	0x00000000
