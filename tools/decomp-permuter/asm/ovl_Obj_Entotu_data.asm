.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Entotu_InitVars
/* 000828 0x80A353F0 */ .word	0x014D0600
/* 000829 0x80A353F4 */ .word	0x00000030
/* 000830 0x80A353F8 */ .word	0x016D0000
/* 000831 0x80A353FC */ .word	0x000001C8
/* 000832 0x80A35400 */ .word	ObjEntotu_Init
/* 000833 0x80A35404 */ .word	ObjEntotu_Destroy
/* 000834 0x80A35408 */ .word	ObjEntotu_Update
/* 000835 0x80A3540C */ .word	ObjEntotu_Draw
glabel D_80A35410
/* 000836 0x80A35410 */ .word	0xFA7F1405
/* 000837 0x80A35414 */ .word	0x012D0000
/* 000838 0x80A35418 */ .word	0xFF75F469
/* 000839 0x80A3541C */ .short	0x0000
/* 000839 0x80A3541C */ .byte	0x00
glabel D_80A3541F
/* 000839 0x80A3541C */ .byte	0x00
/* 000840 0x80A35420 */ .word	0x000008D5
/* 000841 0x80A35424 */ .word	0x025B0000
/* 000842 0x80A35428 */ .word	0x020003CC
/* 000843 0x80A3542C */ .short	0x4D44
/* 000843 0x80A3542C */ .byte	0x34
glabel D_80A3542F
/* 000843 0x80A3542C */ .byte	0xFF
/* 000844 0x80A35430 */ .word	0x00001BAC
/* 000845 0x80A35434 */ .word	0x012D0000
/* 000846 0x80A35438 */ .word	0x0200E9D0
/* 000847 0x80A3543C */ .short	0x0000
/* 000847 0x80A3543C */ .byte	0x00
glabel D_80A3543F
/* 000847 0x80A3543C */ .byte	0x00
/* 000848 0x80A35440 */ .word	0xFBAD08D5
/* 000849 0x80A35444 */ .word	0x00000000
/* 000850 0x80A35448 */ .word	0x00000400
/* 000851 0x80A3544C */ .word	0x00000000
/* 000852 0x80A35450 */ .word	0x05811405
/* 000853 0x80A35454 */ .word	0x012D0000
/* 000854 0x80A35458 */ .word	0x048BF469
/* 000855 0x80A3545C */ .word	0x00000000
/* 000856 0x80A35460 */ .word	0x045308D5
/* 000857 0x80A35464 */ .word	0x00000000
/* 000858 0x80A35468 */ .word	0x04000400
/* 000859 0x80A3546C */ .word	0x00000000
/* 000860 0x80A35470 */ .word	0x00000000
/* 000861 0x80A35474 */ .word	0x00000000
/* 000862 0x80A35478 */ .word	0x0200103A
/* 000863 0x80A3547C */ .word	0x2621197E
