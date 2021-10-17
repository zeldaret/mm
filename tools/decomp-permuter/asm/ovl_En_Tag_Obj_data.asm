.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

/* 000036 0x80B12900 */ .word	0x0A000900
/* 000037 0x80B12904 */ .word	0x20010000
/* 000038 0x80B12908 */ .word	0x00000000
/* 000039 0x80B1290C */ .word	0x00000000
/* 000040 0x80B12910 */ .word	0x00000000
/* 000041 0x80B12914 */ .word	0xF7CFFFFF
/* 000042 0x80B12918 */ .word	0x00000000
/* 000043 0x80B1291C */ .word	0x00010000
/* 000044 0x80B12920 */ .word	0x0014001E
/* 000045 0x80B12924 */ .word	0x00000000
/* 000046 0x80B12928 */ .word	0x00000000
glabel En_Tag_Obj_InitVars
/* 000047 0x80B1292C */ .word	0x01E10600
/* 000048 0x80B12930 */ .word	0x00000000
/* 000049 0x80B12934 */ .word	0x00010000
/* 000050 0x80B12938 */ .word	0x00000198
/* 000051 0x80B1293C */ .word	EnTagObj_Init
/* 000052 0x80B12940 */ .word	EnTagObj_Destroy
/* 000053 0x80B12944 */ .word	EnTagObj_Update
/* 000054 0x80B12948 */ .word	0x00000000
/* 000055 0x80B1294C */ .word	0x00000000
