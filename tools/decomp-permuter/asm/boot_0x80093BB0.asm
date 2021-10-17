.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80093BB0
/* 020180 0x80093BB0 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 020181 0x80093BB4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 020182 0x80093BB8 AFA40020 */ sw	$a0, 0X20($sp)
/* 020183 0x80093BBC AFA50024 */ sw	$a1, 0X24($sp)
/* 020184 0x80093BC0 0C023078 */ jal	__osPiGetAccess
/* 020185 0x80093BC4 AFA60028 */ sw	$a2, 0X28($sp)
/* 020186 0x80093BC8 8FA40020 */ lw	$a0, 0X20($sp)
/* 020187 0x80093BCC 8FA50024 */ lw	$a1, 0X24($sp)
/* 020188 0x80093BD0 0C024FFC */ jal	func_80093FF0
/* 020189 0x80093BD4 8FA60028 */ lw	$a2, 0X28($sp)
/* 020190 0x80093BD8 0C023089 */ jal	__osPiRelAccess
/* 020191 0x80093BDC AFA2001C */ sw	$v0, 0X1C($sp)
/* 020192 0x80093BE0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 020193 0x80093BE4 8FA2001C */ lw	$v0, 0X1C($sp)
/* 020194 0x80093BE8 27BD0020 */ addiu	$sp, $sp, 0X20
/* 020195 0x80093BEC 03E00008 */ jr	$ra
/* 020196 0x80093BF0 00000000 */ nop
/* 020197 0x80093BF4 00000000 */ nop
/* 020198 0x80093BF8 00000000 */ nop
/* 020199 0x80093BFC 00000000 */ nop
