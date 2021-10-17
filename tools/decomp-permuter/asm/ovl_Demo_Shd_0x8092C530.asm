.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel DemoShd_Init
/* 000000 0x8092C530 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x8092C534 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x8092C538 03E00008 */ jr	$ra
/* 000003 0x8092C53C 00000000 */ nop

glabel DemoShd_Destroy
/* 000004 0x8092C540 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x8092C544 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x8092C548 03E00008 */ jr	$ra
/* 000007 0x8092C54C 00000000 */ nop

glabel DemoShd_Update
/* 000008 0x8092C550 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x8092C554 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x8092C558 03E00008 */ jr	$ra
/* 000011 0x8092C55C 00000000 */ nop

glabel DemoShd_Draw
/* 000012 0x8092C560 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x8092C564 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x8092C568 03E00008 */ jr	$ra
/* 000015 0x8092C56C 00000000 */ nop
