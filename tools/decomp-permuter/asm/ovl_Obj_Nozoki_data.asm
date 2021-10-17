.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Nozoki_InitVars
/* 001052 0x80BA3490 */ .word	0x02330700
/* 001053 0x80BA3494 */ .word	0x00000010
/* 001054 0x80BA3498 */ .word	0x00010000
/* 001055 0x80BA349C */ .word	0x00000164
/* 001056 0x80BA34A0 */ .word	ObjNozoki_Init
/* 001057 0x80BA34A4 */ .word	ObjNozoki_Destroy
/* 001058 0x80BA34A8 */ .word	ObjNozoki_Update
/* 001059 0x80BA34AC */ .word	0x00000000
glabel D_80BA34B0
/* 001060 0x80BA34B0 */ .word	0xC0580001
/* 001061 0x80BA34B4 */ .word	0x001F0000
glabel D_80BA34B8
/* 001062 0x80BA34B8 */ .word	0x023C026B
/* 001063 0x80BA34BC */ .word	0x023C023C
glabel D_80BA34C0
/* 001064 0x80BA34C0 */ .word	0x00000000
/* 001065 0x80BA34C4 */ .word	0x00000000
/* 001066 0x80BA34C8 */ .word	0xC48AC000
glabel D_80BA34CC
/* 001067 0x80BA34CC */ .word	0x00000000
/* 001068 0x80BA34D0 */ .word	0x00000000
/* 001069 0x80BA34D4 */ .word	0x42180000
glabel D_80BA34D8
/* 001070 0x80BA34D8 */ .word	0x42C80000
/* 001071 0x80BA34DC */ .word	0x461C3C00
/* 001072 0x80BA34E0 */ .word	0x461C3C00
glabel D_80BA34E4
/* 001073 0x80BA34E4 */ .word	0x3F000000
/* 001074 0x80BA34E8 */ .word	0x3E800000
/* 001075 0x80BA34EC */ .word	0x3F800000
glabel D_80BA34F0
/* 001076 0x80BA34F0 */ .word	0x00000000
/* 001077 0x80BA34F4 */ .word	0x00000000
/* 001078 0x80BA34F8 */ .word	0x42480000
glabel D_80BA34FC
/* 001079 0x80BA34FC */ .word	0x06000080
/* 001080 0x80BA3500 */ .word	0x0A0001A0
/* 001081 0x80BA3504 */ .word	0x06001230
/* 001082 0x80BA3508 */ .word	0x06001300
/* 001083 0x80BA350C */ .word	0x00000000
