.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Eff_Zoraband_InitVars
/* 000224 0x80C07AC0 */ .word	0x02860700
/* 000225 0x80C07AC4 */ .word	0x00000030
/* 000226 0x80C07AC8 */ .word	0x02550000
/* 000227 0x80C07ACC */ .word	0x0000014C
/* 000228 0x80C07AD0 */ .word	EffZoraband_Init
/* 000229 0x80C07AD4 */ .word	EffZoraband_Destroy
/* 000230 0x80C07AD8 */ .word	EffZoraband_Update
/* 000231 0x80C07ADC */ .word	EffZoraband_Draw
