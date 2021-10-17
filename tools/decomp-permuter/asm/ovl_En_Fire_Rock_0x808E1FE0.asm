.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnFireRock_Init
/* 000000 0x808E1FE0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x808E1FE4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x808E1FE8 03E00008 */ jr	$ra
/* 000003 0x808E1FEC 00000000 */ nop

glabel EnFireRock_Destroy
/* 000004 0x808E1FF0 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x808E1FF4 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x808E1FF8 03E00008 */ jr	$ra
/* 000007 0x808E1FFC 00000000 */ nop

glabel EnFireRock_Update
/* 000008 0x808E2000 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x808E2004 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x808E2008 03E00008 */ jr	$ra
/* 000011 0x808E200C 00000000 */ nop

glabel EnFireRock_Draw
/* 000012 0x808E2010 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x808E2014 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x808E2018 03E00008 */ jr	$ra
/* 000015 0x808E201C 00000000 */ nop
