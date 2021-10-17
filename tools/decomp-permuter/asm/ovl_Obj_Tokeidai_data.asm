.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Tokeidai_InitVars
/* 002188 0x80AB49C0 */ .word	0x019C0600
/* 002189 0x80AB49C4 */ .word	0x00000030
/* 002190 0x80AB49C8 */ .word	0x018C0000
/* 002191 0x80AB49CC */ .word	0x00000178
/* 002192 0x80AB49D0 */ .word	ObjTokeidai_Init
/* 002193 0x80AB49D4 */ .word	ObjTokeidai_Destroy
/* 002194 0x80AB49D8 */ .word	ObjTokeidai_Update
/* 002195 0x80AB49DC */ .word	ObjTokeidai_Draw
glabel D_80AB49E0
/* 002196 0x80AB49E0 */ .word	0xC8580064
/* 002197 0x80AB49E4 */ .word	0xB0FC0FA0
/* 002198 0x80AB49E8 */ .word	0xB1000CE4
/* 002199 0x80AB49EC */ .word	0x30FC044C
