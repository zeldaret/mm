.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Mu_Pict_InitVars
/* 000336 0x80C06FE0 */ .word	0x02840600
/* 000337 0x80C06FE4 */ .word	0x00000009
/* 000338 0x80C06FE8 */ .word	0x00010000
/* 000339 0x80C06FEC */ .word	0x00000150
/* 000340 0x80C06FF0 */ .word	ObjMuPict_Init
/* 000341 0x80C06FF4 */ .word	ObjMuPict_Destroy
/* 000342 0x80C06FF8 */ .word	ObjMuPict_Update
/* 000343 0x80C06FFC */ .word	ObjMuPict_Draw
