.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Al_InitVars
/* 000304 0x80C1C250 */ .word	0x02620400
/* 000305 0x80C1C254 */ .word	0x00000009
/* 000306 0x80C1C258 */ .word	0x000D0000
/* 000307 0x80C1C25C */ .word	0x00000460
/* 000308 0x80C1C260 */ .word	DmAl_Init
/* 000309 0x80C1C264 */ .word	DmAl_Destroy
/* 000310 0x80C1C268 */ .word	DmAl_Update
/* 000311 0x80C1C26C */ .word	DmAl_Draw
glabel D_80C1C270
/* 000312 0x80C1C270 */ .word	0x0600DBE0
/* 000313 0x80C1C274 */ .word	0x3F800000
/* 000314 0x80C1C278 */ .word	0x0000FFFF
/* 000315 0x80C1C27C */ .word	0x00000000
glabel D_80C1C280
/* 000316 0x80C1C280 */ .word	0x00000000
/* 000317 0x80C1C284 */ .word	0x00000000
/* 000318 0x80C1C288 */ .word	0x00000000
/* 000319 0x80C1C28C */ .word	0x00000000
/* 000320 0x80C1C290 */ .word	0x00000000
glabel D_80C1C294
/* 000321 0x80C1C294 */ .word	0x06006598
/* 000322 0x80C1C298 */ .word	0x06005920
/* 000323 0x80C1C29C */ .word	0x06005878
/* 000324 0x80C1C2A0 */ .word	0x060057D0
/* 000325 0x80C1C2A4 */ .word	0x06005728
/* 000326 0x80C1C2A8 */ .word	0x06005680
glabel D_80C1C2AC
/* 000327 0x80C1C2AC */ .word	0x00000000
