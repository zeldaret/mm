.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osAfterPreNMI
/* 013740 0x8008D710 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 013741 0x8008D714 AFBF0014 */ sw	$ra, 0X14($sp)
/* 013742 0x8008D718 0C025944 */ jal	__osSpSetPc
/* 013743 0x8008D71C 00002025 */ move	$a0, $zero
/* 013744 0x8008D720 8FBF0014 */ lw	$ra, 0X14($sp)
/* 013745 0x8008D724 27BD0018 */ addiu	$sp, $sp, 0X18
/* 013746 0x8008D728 03E00008 */ jr	$ra
/* 013747 0x8008D72C 00000000 */ nop
