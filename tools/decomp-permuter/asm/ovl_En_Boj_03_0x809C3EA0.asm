.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnBoj03_Init
/* 000000 0x809C3EA0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x809C3EA4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x809C3EA8 03E00008 */ jr	$ra
/* 000003 0x809C3EAC 00000000 */ nop

glabel EnBoj03_Destroy
/* 000004 0x809C3EB0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x809C3EB4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x809C3EB8 03E00008 */ jr	$ra
/* 000007 0x809C3EBC 00000000 */ nop

glabel EnBoj03_Update
/* 000008 0x809C3EC0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x809C3EC4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x809C3EC8 03E00008 */ jr	$ra
/* 000011 0x809C3ECC 00000000 */ nop

glabel EnBoj03_Draw
/* 000012 0x809C3ED0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x809C3ED4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x809C3ED8 03E00008 */ jr	$ra
/* 000015 0x809C3EDC 00000000 */ nop
