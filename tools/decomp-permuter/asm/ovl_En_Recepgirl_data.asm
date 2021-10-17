.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Recepgirl_InitVars
/* 000432 0x80C10690 */ .word	0x02900400
/* 000433 0x80C10694 */ .word	0x00000009
/* 000434 0x80C10698 */ .word	0x01290000
/* 000435 0x80C1069C */ .word	0x000002B4
/* 000436 0x80C106A0 */ .word	EnRecepgirl_Init
/* 000437 0x80C106A4 */ .word	EnRecepgirl_Destroy
/* 000438 0x80C106A8 */ .word	EnRecepgirl_Update
/* 000439 0x80C106AC */ .word	EnRecepgirl_Draw
glabel D_80C106B0
/* 000440 0x80C106B0 */ .word	0x0600F8F0
/* 000441 0x80C106B4 */ .word	0x0600FCF0
/* 000442 0x80C106B8 */ .word	0x060100F0
/* 000443 0x80C106BC */ .word	0x0600FCF0
glabel D_80C106C0
/* 000444 0x80C106C0 */ .word	0x801F0006
/* 000445 0x80C106C4 */ .word	0x305403E8
glabel D_80C106C8
/* 000446 0x80C106C8 */ .word	0x00000000
/* 000447 0x80C106CC */ .word	0x00000000
