.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Tsn_InitVars
/* 001332 0x80AE1170 */ .word	0x01C20400
/* 001333 0x80AE1174 */ .word	0x02000019
/* 001334 0x80AE1178 */ .word	0x01A90000
/* 001335 0x80AE117C */ .word	0x00000234
/* 001336 0x80AE1180 */ .word	EnTsn_Init
/* 001337 0x80AE1184 */ .word	EnTsn_Destroy
/* 001338 0x80AE1188 */ .word	EnTsn_Update
/* 001339 0x80AE118C */ .word	EnTsn_Draw
glabel D_80AE1190
/* 001340 0x80AE1190 */ .word	0x0A001139
/* 001341 0x80AE1194 */ .word	0x10010000
/* 001342 0x80AE1198 */ .word	0x00000000
/* 001343 0x80AE119C */ .word	0x00000000
/* 001344 0x80AE11A0 */ .word	0x00000000
/* 001345 0x80AE11A4 */ .word	0xF7CFFFFF
/* 001346 0x80AE11A8 */ .word	0x00000000
/* 001347 0x80AE11AC */ .word	0x00010100
/* 001348 0x80AE11B0 */ .word	0x001E0028
/* 001349 0x80AE11B4 */ .word	0x00000000
/* 001350 0x80AE11B8 */ .word	0x00000000
glabel D_80AE11BC
/* 001351 0x80AE11BC */ .word	0x00000000
/* 001352 0x80AE11C0 */ .word	0x00000000
/* 001353 0x80AE11C4 */ .word	0x00000000
glabel D_80AE11C8
/* 001354 0x80AE11C8 */ .word	0x060073B8
/* 001355 0x80AE11CC */ .word	0x060085B8
