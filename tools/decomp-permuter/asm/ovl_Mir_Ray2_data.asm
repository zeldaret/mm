.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Mir_Ray2_InitVars
/* 000240 0x80AF4330 */ .word	0x01D00700
/* 000241 0x80AF4334 */ .word	0x00000030
/* 000242 0x80AF4338 */ .word	0x00870000
/* 000243 0x80AF433C */ .word	0x000001C0
/* 000244 0x80AF4340 */ .word	MirRay2_Init
/* 000245 0x80AF4344 */ .word	MirRay2_Destroy
/* 000246 0x80AF4348 */ .word	MirRay2_Update
/* 000247 0x80AF434C */ .word	MirRay2_Draw
glabel D_80AF4350
/* 000248 0x80AF4350 */ .word	0x00000000
/* 000249 0x80AF4354 */ .word	0x00200000
/* 000250 0x80AF4358 */ .word	0x00000000
/* 000251 0x80AF435C */ .word	0x00000000
/* 000252 0x80AF4360 */ .word	0x00000000
/* 000253 0x80AF4364 */ .word	0x01000000
/* 000254 0x80AF4368 */ .word	0x00000000
/* 000255 0x80AF436C */ .word	0x00000000
/* 000256 0x80AF4370 */ .word	0x00320064
glabel D_80AF4374
/* 000257 0x80AF4374 */ .word	0x0A210000
/* 000258 0x80AF4378 */ .word	0x00000000
/* 000259 0x80AF437C */ .word	0x00000001
/* 000260 0x80AF4380 */ .word	D_80AF4350
/* 000261 0x80AF4384 */ .word	0x00000000
/* 000262 0x80AF4388 */ .word	0x00000000
/* 000263 0x80AF438C */ .word	0x00000000
