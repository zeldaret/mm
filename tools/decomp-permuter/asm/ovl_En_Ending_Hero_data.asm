.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ending_Hero_InitVars
/* 000176 0x80C1E950 */ .word	0x02A20400
/* 000177 0x80C1E954 */ .word	0x00000009
/* 000178 0x80C1E958 */ .word	0x02410000
/* 000179 0x80C1E95C */ .word	0x00000248
/* 000180 0x80C1E960 */ .word	EnEndingHero_Init
/* 000181 0x80C1E964 */ .word	EnEndingHero_Destroy
/* 000182 0x80C1E968 */ .word	EnEndingHero_Update
/* 000183 0x80C1E96C */ .word	EnEndingHero_Draw
glabel D_80C1E970
/* 000184 0x80C1E970 */ .word	0x06007350
/* 000185 0x80C1E974 */ .word	0x06009590
/* 000186 0x80C1E978 */ .word	0x06009F90
/* 000187 0x80C1E97C */ .word	0x0600A790
/* 000188 0x80C1E980 */ .word	0x0600AB90
glabel D_80C1E984
/* 000189 0x80C1E984 */ .word	0x06007750
/* 000190 0x80C1E988 */ .word	0x0600A390
/* 000191 0x80C1E98C */ .word	0x0600A490
