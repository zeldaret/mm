.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Eff_Stk_InitVars
/* 000204 0x80BF10C0 */ .word	0x02750700
/* 000205 0x80BF10C4 */ .word	0x00000030
/* 000206 0x80BF10C8 */ .word	0x01BE0000
/* 000207 0x80BF10CC */ .word	0x00000150
/* 000208 0x80BF10D0 */ .word	EffStk_Init
/* 000209 0x80BF10D4 */ .word	EffStk_Destroy
/* 000210 0x80BF10D8 */ .word	EffStk_Update
/* 000211 0x80BF10DC */ .word	EffStk_Draw
