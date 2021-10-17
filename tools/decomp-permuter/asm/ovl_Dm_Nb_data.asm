.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Nb_InitVars
/* 000196 0x80C1E1E0 */ .word	0x02A00400
/* 000197 0x80C1E1E4 */ .word	0x00000009
/* 000198 0x80C1E1E8 */ .word	0x00040000
/* 000199 0x80C1E1EC */ .word	0x000001FC
/* 000200 0x80C1E1F0 */ .word	DmNb_Init
/* 000201 0x80C1E1F4 */ .word	DmNb_Destroy
/* 000202 0x80C1E1F8 */ .word	DmNb_Update
/* 000203 0x80C1E1FC */ .word	DmNb_Draw
glabel D_80C1E200
/* 000204 0x80C1E200 */ .word	0x06000990
/* 000205 0x80C1E204 */ .word	0x3F800000
/* 000206 0x80C1E208 */ .word	0x0000FFFF
/* 000207 0x80C1E20C */ .word	0x00000000
glabel D_80C1E210
/* 000208 0x80C1E210 */ .word	0x00000000
/* 000209 0x80C1E214 */ .word	0x00000000
/* 000210 0x80C1E218 */ .word	0x00000000
/* 000211 0x80C1E21C */ .word	0x00000000
/* 000212 0x80C1E220 */ .word	0x00000000
/* 000213 0x80C1E224 */ .word	0x00000000
/* 000214 0x80C1E228 */ .word	0x00000000
/* 000215 0x80C1E22C */ .word	0x00000000
