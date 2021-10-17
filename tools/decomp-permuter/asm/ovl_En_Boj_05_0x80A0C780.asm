.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnBoj05_Init
/* 000000 0x80A0C780 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x80A0C784 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x80A0C788 03E00008 */ jr	$ra
/* 000003 0x80A0C78C 00000000 */ nop

glabel EnBoj05_Destroy
/* 000004 0x80A0C790 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x80A0C794 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x80A0C798 03E00008 */ jr	$ra
/* 000007 0x80A0C79C 00000000 */ nop

glabel EnBoj05_Update
/* 000008 0x80A0C7A0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x80A0C7A4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x80A0C7A8 03E00008 */ jr	$ra
/* 000011 0x80A0C7AC 00000000 */ nop

glabel EnBoj05_Draw
/* 000012 0x80A0C7B0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x80A0C7B4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x80A0C7B8 03E00008 */ jr	$ra
/* 000015 0x80A0C7BC 00000000 */ nop
