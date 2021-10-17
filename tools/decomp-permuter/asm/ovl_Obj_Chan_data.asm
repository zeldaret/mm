.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Chan_InitVars
/* 001164 0x80BBAB10 */ .word	0x02400100
/* 001165 0x80BBAB14 */ .word	0x00000030
/* 001166 0x80BBAB18 */ .word	0x021E0000
/* 001167 0x80BBAB1C */ .word	0x000001E4
/* 001168 0x80BBAB20 */ .word	ObjChan_Init
/* 001169 0x80BBAB24 */ .word	ObjChan_Destroy
/* 001170 0x80BBAB28 */ .word	ObjChan_Update
/* 001171 0x80BBAB2C */ .word	ObjChan_Draw
glabel D_80BBAB30
/* 001172 0x80BBAB30 */ .word	0x0C000900
/* 001173 0x80BBAB34 */ .word	0x10010000
/* 001174 0x80BBAB38 */ .word	0x01000000
/* 001175 0x80BBAB3C */ .word	0x00000000
/* 001176 0x80BBAB40 */ .word	0x00000000
/* 001177 0x80BBAB44 */ .word	0xF7CFFFFF
/* 001178 0x80BBAB48 */ .word	0x00000000
/* 001179 0x80BBAB4C */ .word	0x00010000
/* 001180 0x80BBAB50 */ .word	0x0030004C
/* 001181 0x80BBAB54 */ .word	0xFFC40000
/* 001182 0x80BBAB58 */ .word	0x00000000
glabel D_80BBAB5C
/* 001183 0x80BBAB5C */ .word	0x48580064
glabel D_80BBAB60
/* 001184 0x80BBAB60 */ .word	0x3E23D70A
/* 001185 0x80BBAB64 */ .word	0x3DE147AE
/* 001186 0x80BBAB68 */ .word	0x3F800000
/* 001187 0x80BBAB6C */ .word	0x3E051EB8
/* 001188 0x80BBAB70 */ .word	0x3DB851EC
/* 001189 0x80BBAB74 */ .word	0x3F800000
glabel D_80BBAB78
/* 001190 0x80BBAB78 */ .word	0x44E10000
/* 001191 0x80BBAB7C */ .word	0x44E10000
