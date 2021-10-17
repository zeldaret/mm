.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Jg_Gakki_InitVars
/* 000120 0x80B963C0 */ .word	0x02260600
/* 000121 0x80B963C4 */ .word	0x00000020
/* 000122 0x80B963C8 */ .word	0x01F80000
/* 000123 0x80B963CC */ .word	0x000001D4
/* 000124 0x80B963D0 */ .word	ObjJgGakki_Init
/* 000125 0x80B963D4 */ .word	ObjJgGakki_Destroy
/* 000126 0x80B963D8 */ .word	ObjJgGakki_Update
/* 000127 0x80B963DC */ .word	ObjJgGakki_Draw
