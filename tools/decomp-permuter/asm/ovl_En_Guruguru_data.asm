.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Guruguru_InitVars
/* 000860 0x80BC7960 */ .word	0x02480400
/* 000861 0x80BC7964 */ .word	0x00000019
/* 000862 0x80BC7968 */ .word	0x00FF0000
/* 000863 0x80BC796C */ .word	0x000002C4
/* 000864 0x80BC7970 */ .word	EnGuruguru_Init
/* 000865 0x80BC7974 */ .word	EnGuruguru_Destroy
/* 000866 0x80BC7978 */ .word	EnGuruguru_Update
/* 000867 0x80BC797C */ .word	EnGuruguru_Draw
glabel D_80BC7980
/* 000868 0x80BC7980 */ .word	0x292A292B
/* 000869 0x80BC7984 */ .word	0x292C292D
/* 000870 0x80BC7988 */ .word	0x292E292F
/* 000871 0x80BC798C */ .word	0x29302931
/* 000872 0x80BC7990 */ .word	0x29322933
/* 000873 0x80BC7994 */ .word	0x29342935
/* 000874 0x80BC7998 */ .word	0x2936294D
/* 000875 0x80BC799C */ .word	0x294E0000
glabel D_80BC79A0
/* 000876 0x80BC79A0 */ .word	0x0A000039
/* 000877 0x80BC79A4 */ .word	0x20010000
/* 000878 0x80BC79A8 */ .word	0x00000000
/* 000879 0x80BC79AC */ .word	0x00000000
/* 000880 0x80BC79B0 */ .word	0x00000000
/* 000881 0x80BC79B4 */ .word	0xF7CFFFFF
/* 000882 0x80BC79B8 */ .word	0x00000000
/* 000883 0x80BC79BC */ .word	0x00000100
/* 000884 0x80BC79C0 */ .word	0x000F0014
/* 000885 0x80BC79C4 */ .word	0x00000000
/* 000886 0x80BC79C8 */ .word	0x00000000
glabel D_80BC79CC
/* 000887 0x80BC79CC */ .word	0x06000B04
/* 000888 0x80BC79D0 */ .word	0x0600057C
glabel D_80BC79D4
/* 000889 0x80BC79D4 */ .word	0x00000000
glabel D_80BC79D8
/* 000890 0x80BC79D8 */ .word	0x3F800000
/* 000891 0x80BC79DC */ .word	0x3F800000
glabel D_80BC79E0
/* 000892 0x80BC79E0 */ .word	0x06005F20
/* 000893 0x80BC79E4 */ .word	0x06006320
glabel D_80BC79E8
/* 000894 0x80BC79E8 */ .word	0x06006720
/* 000895 0x80BC79EC */ .word	0x06006920
