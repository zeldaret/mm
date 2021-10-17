.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Rsn_InitVars
/* 000172 0x80C25FF0 */ .word	0x02B10400
/* 000173 0x80C25FF4 */ .word	0x02000019
/* 000174 0x80C25FF8 */ .word	0x012C0000
/* 000175 0x80C25FFC */ .word	0x000001E4
/* 000176 0x80C26000 */ .word	EnRsn_Init
/* 000177 0x80C26004 */ .word	EnRsn_Destroy
/* 000178 0x80C26008 */ .word	EnRsn_Update
/* 000179 0x80C2600C */ .word	EnRsn_Draw
glabel D_80C26010
/* 000180 0x80C26010 */ .word	0x0600788C
/* 000181 0x80C26014 */ .word	0x3F800000
/* 000182 0x80C26018 */ .word	0x00000000
/* 000183 0x80C2601C */ .word	0x00000000
/* 000184 0x80C26020 */ .word	0x00000000
/* 000185 0x80C26024 */ .word	0x00000000
glabel D_80C26028
/* 000186 0x80C26028 */ .word	0x00000000
/* 000187 0x80C2602C */ .word	0x00000000
/* 000188 0x80C26030 */ .word	0x00000000
/* 000189 0x80C26034 */ .word	0x00000000
/* 000190 0x80C26038 */ .word	0x00000000
/* 000191 0x80C2603C */ .word	0x00000000
