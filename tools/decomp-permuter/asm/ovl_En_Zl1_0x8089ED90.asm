.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnZl1_Init
/* 000000 0x8089ED90 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x8089ED94 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x8089ED98 03E00008 */ jr	$ra
/* 000003 0x8089ED9C 00000000 */ nop

glabel EnZl1_Destroy
/* 000004 0x8089EDA0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x8089EDA4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x8089EDA8 03E00008 */ jr	$ra
/* 000007 0x8089EDAC 00000000 */ nop

glabel EnZl1_Update
/* 000008 0x8089EDB0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x8089EDB4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x8089EDB8 03E00008 */ jr	$ra
/* 000011 0x8089EDBC 00000000 */ nop

glabel EnZl1_Draw
/* 000012 0x8089EDC0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x8089EDC4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x8089EDC8 03E00008 */ jr	$ra
/* 000015 0x8089EDCC 00000000 */ nop
