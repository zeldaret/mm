.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Scopecoin_InitVars
/* 000176 0x80BFD260 */ .word	0x027C0400
/* 000177 0x80BFD264 */ .word	0x00000030
/* 000178 0x80BFD268 */ .word	0x00010000
/* 000179 0x80BFD26C */ .word	0x0000014C
/* 000180 0x80BFD270 */ .word	EnScopecoin_Init
/* 000181 0x80BFD274 */ .word	EnScopecoin_Destroy
/* 000182 0x80BFD278 */ .word	EnScopecoin_Update
/* 000183 0x80BFD27C */ .word	EnScopecoin_Draw
glabel D_80BFD280
/* 000184 0x80BFD280 */ .word	0x04061FC0
/* 000185 0x80BFD284 */ .word	0x04061FE0
/* 000186 0x80BFD288 */ .word	0x04062000
/* 000187 0x80BFD28C */ .word	0x04062040
/* 000188 0x80BFD290 */ .word	0x04062020
/* 000189 0x80BFD294 */ .word	0x04062060
/* 000190 0x80BFD298 */ .word	0x04062000
/* 000191 0x80BFD29C */ .word	0x00000000
