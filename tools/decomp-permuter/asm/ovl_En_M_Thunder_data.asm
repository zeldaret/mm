.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_M_Thunder_InitVars
/* 001872 0x808B7100 */ .word	0x00350700
/* 001873 0x808B7104 */ .word	0x00000010
/* 001874 0x808B7108 */ .word	0x00010000
/* 001875 0x808B710C */ .word	0x000001C4
/* 001876 0x808B7110 */ .word	EnMThunder_Init
/* 001877 0x808B7114 */ .word	EnMThunder_Destroy
/* 001878 0x808B7118 */ .word	EnMThunder_Update
/* 001879 0x808B711C */ .word	EnMThunder_Draw
glabel D_808B7120
/* 001880 0x808B7120 */ .word	0x0A090000
/* 001881 0x808B7124 */ .word	0x10010000
/* 001882 0x808B7128 */ .word	0x02000000
/* 001883 0x808B712C */ .word	0x01000000
/* 001884 0x808B7130 */ .word	0x00000000
/* 001885 0x808B7134 */ .word	0xF7CFFFFF
/* 001886 0x808B7138 */ .word	0x00000000
/* 001887 0x808B713C */ .word	0x19010100
/* 001888 0x808B7140 */ .word	0x00C800C8
/* 001889 0x808B7144 */ .word	0x00000000
/* 001890 0x808B7148 */ .word	0x00000000
glabel D_808B714C
/* 001891 0x808B714C */ .word	0x01020304
glabel D_808B7150
/* 001892 0x808B7150 */ .word	0x01020304
glabel D_808B7154
/* 001893 0x808B7154 */ .word	0x182F182E
/* 001894 0x808B7158 */ .word	0x182F182E
glabel D_808B715C
/* 001895 0x808B715C */ .word	0x3DCCCCCD
/* 001896 0x808B7160 */ .word	0x3E19999A
/* 001897 0x808B7164 */ .word	0x3E4CCCCD
/* 001898 0x808B7168 */ .word	0x3E800000
/* 001899 0x808B716C */ .word	0x3E99999A
/* 001900 0x808B7170 */ .word	0x3E800000
/* 001901 0x808B7174 */ .word	0x3E4CCCCD
/* 001902 0x808B7178 */ .word	0x3E19999A
/* 001903 0x808B717C */ .word	0x00000000
