.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnBoj02_Init
/* 000000 0x809C3E10 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x809C3E14 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x809C3E18 03E00008 */ jr	$ra
/* 000003 0x809C3E1C 00000000 */ nop

glabel EnBoj02_Destroy
/* 000004 0x809C3E20 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x809C3E24 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x809C3E28 03E00008 */ jr	$ra
/* 000007 0x809C3E2C 00000000 */ nop

glabel EnBoj02_Update
/* 000008 0x809C3E30 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x809C3E34 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x809C3E38 03E00008 */ jr	$ra
/* 000011 0x809C3E3C 00000000 */ nop

glabel EnBoj02_Draw
/* 000012 0x809C3E40 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x809C3E44 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x809C3E48 03E00008 */ jr	$ra
/* 000015 0x809C3E4C 00000000 */ nop
