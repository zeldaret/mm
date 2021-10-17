.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Armos_InitVars
/* 000868 0x809A5B90 */ .word	0x01050600
/* 000869 0x809A5B94 */ .word	0x04000010
/* 000870 0x809A5B98 */ .word	0x00300000
/* 000871 0x809A5B9C */ .word	0x00000274
/* 000872 0x809A5BA0 */ .word	ObjArmos_Init
/* 000873 0x809A5BA4 */ .word	ObjArmos_Destroy
/* 000874 0x809A5BA8 */ .word	ObjArmos_Update
/* 000875 0x809A5BAC */ .word	ObjArmos_Draw
glabel D_809A5BB0
/* 000876 0x809A5BB0 */ .word	0x0001FFFF
/* 000877 0x809A5BB4 */ .word	0x00000000
glabel D_809A5BB8
/* 000878 0x809A5BB8 */ .word	0x00000000
/* 000879 0x809A5BBC */ .word	0x0001FFFF
glabel D_809A5BC0
/* 000880 0x809A5BC0 */ .word	0xB0FC0FA0
/* 000881 0x809A5BC4 */ .word	0xB1000078
/* 000882 0x809A5BC8 */ .word	0xB10400FA
/* 000883 0x809A5BCC */ .word	0xB874F060
/* 000884 0x809A5BD0 */ .word	0x4858000A
/* 000885 0x809A5BD4 */ .word	0x00000000
/* 000886 0x809A5BD8 */ .word	0x00000000
/* 000887 0x809A5BDC */ .word	0x00000000
