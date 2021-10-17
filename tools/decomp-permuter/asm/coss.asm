.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel coss
/* 018560 0x80092260 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 018561 0x80092264 AFA40018 */ sw	$a0, 0X18($sp)
/* 018562 0x80092268 00802825 */ move	$a1, $a0
/* 018563 0x8009226C 24A44000 */ addiu	$a0, $a1, 0X4000
/* 018564 0x80092270 AFBF0014 */ sw	$ra, 0X14($sp)
/* 018565 0x80092274 308EFFFF */ andi	$t6, $a0, 0XFFFF
/* 018566 0x80092278 0C022144 */ jal	sins
/* 018567 0x8009227C 01C02025 */ move	$a0, $t6
/* 018568 0x80092280 8FBF0014 */ lw	$ra, 0X14($sp)
/* 018569 0x80092284 27BD0018 */ addiu	$sp, $sp, 0X18
/* 018570 0x80092288 03E00008 */ jr	$ra
/* 018571 0x8009228C 00000000 */ nop
