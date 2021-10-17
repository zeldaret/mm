.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Firefly_InitVars
/* 001880 0x8087B450 */ .word	0x000C0500
/* 001881 0x8087B454 */ .word	0x00005005
/* 001882 0x8087B458 */ .word	0x000B0000
/* 001883 0x8087B45C */ .word	0x00000374
/* 001884 0x8087B460 */ .word	EnFirefly_Init
/* 001885 0x8087B464 */ .word	EnFirefly_Destroy
/* 001886 0x8087B468 */ .word	EnFirefly_Update
/* 001887 0x8087B46C */ .word	EnFirefly_Draw
glabel enFireflyCollisionInit
/* 001888 0x8087B470 */ .word	0x03110939
/* 001889 0x8087B474 */ .word	0x10040000
/* 001890 0x8087B478 */ .word	0x00000000
/* 001891 0x8087B47C */ .word	0xF7CFFFFF
/* 001892 0x8087B480 */ .word	0x01080000
/* 001893 0x8087B484 */ .word	0xF7CFFFFF
/* 001894 0x8087B488 */ .word	0x00000000
/* 001895 0x8087B48C */ .word	0x09010100
/* 001896 0x8087B490 */ .word	0x01000000
/* 001897 0x8087B494 */ .word	0x03E80000
glabel D_8087B498
/* 001898 0x8087B498 */ .word	0x000F0064
glabel D_8087B49C
/* 001899 0x8087B49C */ .word	0x0100000A
/* 001900 0x8087B4A0 */ .word	0x000A0A00
glabel enFireflyDamageTable
/* 001901 0x8087B4A4 */ .word	0x10010001
/* 001902 0x8087B4A8 */ .word	0x01010001
/* 001903 0x8087B4AC */ .word	0x01010122
/* 001904 0x8087B4B0 */ .word	0x32420101
/* 001905 0x8087B4B4 */ .word	0x01021050
/* 001906 0x8087B4B8 */ .word	0x00000101
/* 001907 0x8087B4BC */ .word	0x01000000
/* 001908 0x8087B4C0 */ .word	0x00000001
glabel enFireflyInitVars
/* 001909 0x8087B4C4 */ .word	0xC8580005
/* 001910 0x8087B4C8 */ .word	0xB874FE0C
/* 001911 0x8087B4CC */ .word	0x801F0002
/* 001912 0x8087B4D0 */ .word	0x30540FA0
glabel D_8087B4D4
/* 001913 0x8087B4D4 */ .word	0xFFFF64FF
glabel D_8087B4D8
/* 001914 0x8087B4D8 */ .word	0xFF320000
glabel D_8087B4DC
/* 001915 0x8087B4DC */ .word	0x64C8FFFF
glabel D_8087B4E0
/* 001916 0x8087B4E0 */ .word	0x0000FF00
glabel D_8087B4E4
/* 001917 0x8087B4E4 */ .word	0x00000000
/* 001918 0x8087B4E8 */ .word	0x3F000000
/* 001919 0x8087B4EC */ .word	0x00000000
glabel D_8087B4F0
/* 001920 0x8087B4F0 */ .word	0x00000000
/* 001921 0x8087B4F4 */ .word	0x3F000000
/* 001922 0x8087B4F8 */ .word	0x00000000
/* 001923 0x8087B4FC */ .word	0x00000000
