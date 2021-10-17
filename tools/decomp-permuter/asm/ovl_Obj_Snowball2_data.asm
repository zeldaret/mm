.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Snowball2_InitVars
/* 001704 0x80B3A8C0 */ .word	0x01F90600
/* 001705 0x80B3A8C4 */ .word	0x00800000
/* 001706 0x80B3A8C8 */ .word	0x00EF0000
/* 001707 0x80B3A8CC */ .word	0x000001B4
/* 001708 0x80B3A8D0 */ .word	ObjSnowball2_Init
/* 001709 0x80B3A8D4 */ .word	ObjSnowball2_Destroy
/* 001710 0x80B3A8D8 */ .word	ObjSnowball2_Update
/* 001711 0x80B3A8DC */ .word	ObjSnowball2_Draw
glabel D_80B3A8E0
/* 001712 0x80B3A8E0 */ .word	0x00000000
/* 001713 0x80B3A8E4 */ .word	0x00400000
/* 001714 0x80B3A8E8 */ .word	0x00020000
/* 001715 0x80B3A8EC */ .word	0x0583FFBE
/* 001716 0x80B3A8F0 */ .word	0x00000000
/* 001717 0x80B3A8F4 */ .word	0x19010100
/* 001718 0x80B3A8F8 */ .word	0x00000000
/* 001719 0x80B3A8FC */ .word	0x00000000
/* 001720 0x80B3A900 */ .word	0x000F0064
glabel D_80B3A904
/* 001721 0x80B3A904 */ .word	0x0A090939
/* 001722 0x80B3A908 */ .word	0x20000000
/* 001723 0x80B3A90C */ .word	0x00000001
/* 001724 0x80B3A910 */ .word	D_80B3A8E0
glabel D_80B3A914
/* 001725 0x80B3A914 */ .word	0xFAFAFAFF
glabel D_80B3A918
/* 001726 0x80B3A918 */ .word	0xB4B4B4FF
glabel D_80B3A91C
/* 001727 0x80B3A91C */ .word	0x060072F0
/* 001728 0x80B3A920 */ .word	0x060077D0
/* 001729 0x80B3A924 */ .word	0x06007C60
/* 001730 0x80B3A928 */ .word	0x06007C60
glabel D_80B3A92C
/* 001731 0x80B3A92C */ .word	0x00000000
/* 001732 0x80B3A930 */ .word	0x3E99999A
/* 001733 0x80B3A934 */ .word	0x00000000
glabel D_80B3A938
/* 001734 0x80B3A938 */ .word	0x00000000
glabel D_80B3A93C
/* 001735 0x80B3A93C */ .word	0xB874F830
/* 001736 0x80B3A940 */ .word	0xB878B1E0
/* 001737 0x80B3A944 */ .word	0xB0FC07D0
/* 001738 0x80B3A948 */ .word	0xB1000064
/* 001739 0x80B3A94C */ .word	0xB1040064
/* 001740 0x80B3A950 */ .word	0x48580019
/* 001741 0x80B3A954 */ .word	0x00000000
/* 001742 0x80B3A958 */ .word	0x00000000
/* 001743 0x80B3A95C */ .word	0x00000000
