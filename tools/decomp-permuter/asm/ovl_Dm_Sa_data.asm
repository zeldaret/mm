.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Sa_InitVars
/* 000224 0x80A2ECE0 */ .word	0x01490700
/* 000225 0x80A2ECE4 */ .word	0x00000030
/* 000226 0x80A2ECE8 */ .word	0x01920000
/* 000227 0x80A2ECEC */ .word	0x000002F4
/* 000228 0x80A2ECF0 */ .word	DmSa_Init
/* 000229 0x80A2ECF4 */ .word	DmSa_Destroy
/* 000230 0x80A2ECF8 */ .word	DmSa_Update
/* 000231 0x80A2ECFC */ .word	DmSa_Draw
glabel D_80A2ED00
/* 000232 0x80A2ED00 */ .word	0x0600CC94
/* 000233 0x80A2ED04 */ .word	0x3F800000
/* 000234 0x80A2ED08 */ .word	0x00000000
/* 000235 0x80A2ED0C */ .word	0xBF800000
/* 000236 0x80A2ED10 */ .word	0x00000000
/* 000237 0x80A2ED14 */ .word	0x00000000
/* 000238 0x80A2ED18 */ .word	0x00000000
/* 000239 0x80A2ED1C */ .word	0x00000000
