.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnBoj01_Init
/* 000000 0x809C3D80 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x809C3D84 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x809C3D88 03E00008 */ jr	$ra
/* 000003 0x809C3D8C 00000000 */ nop

glabel EnBoj01_Destroy
/* 000004 0x809C3D90 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x809C3D94 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x809C3D98 03E00008 */ jr	$ra
/* 000007 0x809C3D9C 00000000 */ nop

glabel EnBoj01_Update
/* 000008 0x809C3DA0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x809C3DA4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x809C3DA8 03E00008 */ jr	$ra
/* 000011 0x809C3DAC 00000000 */ nop

glabel EnBoj01_Draw
/* 000012 0x809C3DB0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x809C3DB4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x809C3DB8 03E00008 */ jr	$ra
/* 000015 0x809C3DBC 00000000 */ nop
