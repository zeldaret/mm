.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnFirefly2_Init
/* 000000 0x80A560C0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x80A560C4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x80A560C8 03E00008 */ jr	$ra
/* 000003 0x80A560CC 00000000 */ nop

glabel EnFirefly2_Destroy
/* 000004 0x80A560D0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x80A560D4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x80A560D8 03E00008 */ jr	$ra
/* 000007 0x80A560DC 00000000 */ nop

glabel EnFirefly2_Update
/* 000008 0x80A560E0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x80A560E4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x80A560E8 03E00008 */ jr	$ra
/* 000011 0x80A560EC 00000000 */ nop

glabel EnFirefly2_Draw
/* 000012 0x80A560F0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x80A560F4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x80A560F8 03E00008 */ jr	$ra
/* 000015 0x80A560FC 00000000 */ nop
