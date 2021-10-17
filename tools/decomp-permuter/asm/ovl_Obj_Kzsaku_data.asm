.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Kzsaku_InitVars
/* 000212 0x80C08DD0 */ .word	0x028A0600
/* 000213 0x80C08DD4 */ .word	0x00000030
/* 000214 0x80C08DD8 */ .word	0x02600000
/* 000215 0x80C08DDC */ .word	0x0000016C
/* 000216 0x80C08DE0 */ .word	ObjKzsaku_Init
/* 000217 0x80C08DE4 */ .word	ObjKzsaku_Destroy
/* 000218 0x80C08DE8 */ .word	ObjKzsaku_Update
/* 000219 0x80C08DEC */ .word	ObjKzsaku_Draw
