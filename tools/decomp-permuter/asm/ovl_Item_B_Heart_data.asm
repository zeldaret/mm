.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Item_B_Heart_InitVars
/* 000220 0x808BD160 */ .word	0x003A0900
/* 000221 0x808BD164 */ .word	0x00000000
/* 000222 0x808BD168 */ .word	0x00960000
/* 000223 0x808BD16C */ .word	0x0000016C
/* 000224 0x808BD170 */ .word	ItemBHeart_Init
/* 000225 0x808BD174 */ .word	ItemBHeart_Destroy
/* 000226 0x808BD178 */ .word	ItemBHeart_Update
/* 000227 0x808BD17C */ .word	ItemBHeart_Draw
glabel D_808BD180
/* 000228 0x808BD180 */ .word	0xC8580000
/* 000229 0x808BD184 */ .word	0xB0FC0FA0
/* 000230 0x808BD188 */ .word	0xB1000320
/* 000231 0x808BD18C */ .word	0x31040320
