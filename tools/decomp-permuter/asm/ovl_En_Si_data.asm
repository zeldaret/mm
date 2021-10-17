.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Si_InitVars
/* 000208 0x8098CD60 */ .word	0x00E30700
/* 000209 0x8098CD64 */ .word	0x00000201
/* 000210 0x8098CD68 */ .word	0x00200000
/* 000211 0x8098CD6C */ .word	0x000001A0
/* 000212 0x8098CD70 */ .word	EnSi_Init
/* 000213 0x8098CD74 */ .word	EnSi_Destroy
/* 000214 0x8098CD78 */ .word	EnSi_Update
/* 000215 0x8098CD7C */ .word	EnSi_Draw
glabel D_8098CD80
/* 000216 0x8098CD80 */ .word	0x0A00093D
/* 000217 0x8098CD84 */ .word	0x10040000
/* 000218 0x8098CD88 */ .word	0x00000000
/* 000219 0x8098CD8C */ .word	0xF7CFFFFF
/* 000220 0x8098CD90 */ .word	0x00000000
/* 000221 0x8098CD94 */ .word	0xF7CFFFFF
/* 000222 0x8098CD98 */ .word	0x00000000
/* 000223 0x8098CD9C */ .word	0x01050100
/* 000224 0x8098CDA0 */ .word	0x00000000
/* 000225 0x8098CDA4 */ .word	0x00000000
/* 000226 0x8098CDA8 */ .word	0x000A0064
glabel D_8098CDAC
/* 000227 0x8098CDAC */ .word	0x01000000
/* 000228 0x8098CDB0 */ .word	0x00000000
/* 000229 0x8098CDB4 */ .word	0xFF000000
glabel D_8098CDB8
/* 000230 0x8098CDB8 */ .word	0x01010101
/* 000231 0x8098CDBC */ .word	0x01010101
/* 000232 0x8098CDC0 */ .word	0x01010101
/* 000233 0x8098CDC4 */ .word	0x01010101
/* 000234 0x8098CDC8 */ .word	0x01010101
/* 000235 0x8098CDCC */ .word	0x01010101
/* 000236 0x8098CDD0 */ .word	0x01010101
/* 000237 0x8098CDD4 */ .word	0x01010101
/* 000238 0x8098CDD8 */ .word	0x00000000
/* 000239 0x8098CDDC */ .word	0x00000000
