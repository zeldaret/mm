.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel EnBoj04_Init
/* 000000 0x809CB200 AFA40000 */ sw	$a0, 0X0($sp)
/* 000001 0x809CB204 AFA50004 */ sw	$a1, 0X4($sp)
/* 000002 0x809CB208 03E00008 */ jr	$ra
/* 000003 0x809CB20C 00000000 */ nop

glabel EnBoj04_Destroy
/* 000004 0x809CB210 AFA40000 */ sw	$a0, 0X0($sp)
/* 000005 0x809CB214 AFA50004 */ sw	$a1, 0X4($sp)
/* 000006 0x809CB218 03E00008 */ jr	$ra
/* 000007 0x809CB21C 00000000 */ nop

glabel EnBoj04_Update
/* 000008 0x809CB220 AFA40000 */ sw	$a0, 0X0($sp)
/* 000009 0x809CB224 AFA50004 */ sw	$a1, 0X4($sp)
/* 000010 0x809CB228 03E00008 */ jr	$ra
/* 000011 0x809CB22C 00000000 */ nop

glabel EnBoj04_Draw
/* 000012 0x809CB230 AFA40000 */ sw	$a0, 0X0($sp)
/* 000013 0x809CB234 AFA50004 */ sw	$a1, 0X4($sp)
/* 000014 0x809CB238 03E00008 */ jr	$ra
/* 000015 0x809CB23C 00000000 */ nop
