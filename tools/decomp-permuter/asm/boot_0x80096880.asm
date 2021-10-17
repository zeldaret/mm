.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80096880
/* 023048 0x80096880 00C01825 */ move	$v1, $a2
/* 023049 0x80096884 00801025 */ move	$v0, $a0
/* 023050 0x80096888 10C00006 */ beqz	$a2, .L800968A4
/* 023051 0x8009688C 24C6FFFF */ addiu	$a2, $a2, -0X1
.L80096890:
/* 023052 0x80096890 00C01825 */ move	$v1, $a2
/* 023053 0x80096894 A0450000 */ sb	$a1, 0X0($v0)
/* 023054 0x80096898 24420001 */ addiu	$v0, $v0, 0X1
/* 023055 0x8009689C 14C0FFFC */ bnez	$a2, .L80096890
/* 023056 0x800968A0 24C6FFFF */ addiu	$a2, $a2, -0X1
.L800968A4:
/* 023057 0x800968A4 03E00008 */ jr	$ra
/* 023058 0x800968A8 00801025 */ move	$v0, $a0
/* 023059 0x800968AC 00000000 */ nop
