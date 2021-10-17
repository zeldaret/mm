.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Mure_InitVars
/* 000932 0x808D8760 */ .word	0x004F0700
/* 000933 0x808D8764 */ .word	0x00000000
/* 000934 0x808D8768 */ .word	0x00010000
/* 000935 0x808D876C */ .word	0x000001A4
/* 000936 0x808D8770 */ .word	ObjMure_Init
/* 000937 0x808D8774 */ .word	ObjMure_Destroy
/* 000938 0x808D8778 */ .word	ObjMure_Update
/* 000939 0x808D877C */ .word	0x00000000
glabel D_808D8780
/* 000940 0x808D8780 */ .word	0x44C80000
/* 000941 0x808D8784 */ .word	0x44C80000
/* 000942 0x808D8788 */ .word	0x447A0000
/* 000943 0x808D878C */ .word	0x447A0000
/* 000944 0x808D8790 */ .word	0x447A0000
/* 000945 0x808D8794 */ .word	0x0000000C
/* 000946 0x808D8798 */ .word	0x00000009
/* 000947 0x808D879C */ .word	0x00000008
/* 000948 0x808D87A0 */ .word	0x00000000
/* 000949 0x808D87A4 */ .word	0x00900000
/* 000950 0x808D87A8 */ .word	0x00170016
/* 000951 0x808D87AC */ .word	0x00150000
/* 000952 0x808D87B0 */ .word	0x00000002
/* 000953 0x808D87B4 */ .word	0xFFFF0000
/* 000954 0x808D87B8 */ .word	0xFFFF0000
/* 000955 0x808D87BC */ .word	0xB0FC04B0
/* 000956 0x808D87C0 */ .word	0xB10000C8
/* 000957 0x808D87C4 */ .word	0x310404B0
/* 000958 0x808D87C8 */ .word	0x00000000
/* 000959 0x808D87CC */ .word	0x00000000
/* 000960 0x808D87D0 */ .word	func_808D82CC
/* 000961 0x808D87D4 */ .word	func_808D82CC
/* 000962 0x808D87D8 */ .word	func_808D84F4
/* 000963 0x808D87DC */ .word	0x00000000
