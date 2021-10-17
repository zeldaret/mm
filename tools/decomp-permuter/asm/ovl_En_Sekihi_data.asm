.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Sekihi_InitVars
/* 000372 0x80A45250 */ .word	0x015C0600
/* 000373 0x80A45254 */ .word	0x00000019
/* 000374 0x80A45258 */ .word	0x00010000
/* 000375 0x80A4525C */ .word	0x0000016C
/* 000376 0x80A45260 */ .word	EnSekihi_Init
/* 000377 0x80A45264 */ .word	EnSekihi_Destroy
/* 000378 0x80A45268 */ .word	EnSekihi_Update
/* 000379 0x80A4526C */ .word	0x00000000
glabel D_80A45270
/* 000380 0x80A45270 */ .word	0x01730174
/* 000381 0x80A45274 */ .word	0x01750176
/* 000382 0x80A45278 */ .word	0x02060000
glabel D_80A4527C
/* 000383 0x80A4527C */ .word	0x060005E0
/* 000384 0x80A45280 */ .word	0x060005C8
/* 000385 0x80A45284 */ .word	0x060005C8
/* 000386 0x80A45288 */ .word	0x06000518
/* 000387 0x80A4528C */ .word	0x06006AA0
glabel D_80A45290
/* 000388 0x80A45290 */ .word	0x060004C0
/* 000389 0x80A45294 */ .word	0x060004A8
/* 000390 0x80A45298 */ .word	0x060004A8
/* 000391 0x80A4529C */ .word	0x06000510
/* 000392 0x80A452A0 */ .word	0x060069F0
glabel D_80A452A4
/* 000393 0x80A452A4 */ .word	0x00000000
/* 000394 0x80A452A8 */ .word	0x00000000
/* 000395 0x80A452AC */ .word	0x10180000
glabel D_80A452B0
/* 000396 0x80A452B0 */ .word	0x060033F8
/* 000397 0x80A452B4 */ .word	0x060033D8
/* 000398 0x80A452B8 */ .word	0x060033D8
/* 000399 0x80A452BC */ .word	0x06001010
/* 000400 0x80A452C0 */ .word	0x06008670
/* 000401 0x80A452C4 */ .word	0x00000000
/* 000402 0x80A452C8 */ .word	0x00000000
/* 000403 0x80A452CC */ .word	0x00000000
