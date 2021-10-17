.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Dinner_InitVars
/* 000076 0x80BEBA70 */ .word	0x02710600
/* 000077 0x80BEBA74 */ .word	0x00000020
/* 000078 0x80BEBA78 */ .word	0x02440000
/* 000079 0x80BEBA7C */ .word	0x00000148
/* 000080 0x80BEBA80 */ .word	ObjDinner_Init
/* 000081 0x80BEBA84 */ .word	ObjDinner_Destroy
/* 000082 0x80BEBA88 */ .word	ObjDinner_Update
/* 000083 0x80BEBA8C */ .word	ObjDinner_Draw
