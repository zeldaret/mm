.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_8019AEC0
/* 251136 0x8019AEC0 20AF0020 */ addi	$t7, $a1, 0X20
.L8019AEC4:
/* 251137 0x8019AEC4 8CA80000 */ lw	$t0, 0X0($a1)
/* 251138 0x8019AEC8 8CA90004 */ lw	$t1, 0X4($a1)
/* 251139 0x8019AECC 8CAA0008 */ lw	$t2, 0X8($a1)
/* 251140 0x8019AED0 8CAB000C */ lw	$t3, 0XC($a1)
/* 251141 0x8019AED4 20A50010 */ addi	$a1, $a1, 0X10
/* 251142 0x8019AED8 AC880000 */ sw	$t0, 0X0($a0)
/* 251143 0x8019AEDC AC890004 */ sw	$t1, 0X4($a0)
/* 251144 0x8019AEE0 AC8A0008 */ sw	$t2, 0X8($a0)
/* 251145 0x8019AEE4 AC8B000C */ sw	$t3, 0XC($a0)
/* 251146 0x8019AEE8 14AFFFF6 */ bne	$a1, $t7, .L8019AEC4
/* 251147 0x8019AEEC 20840010 */ addi	$a0, $a0, 0X10
/* 251148 0x8019AEF0 03E00008 */ jr	$ra
/* 251149 0x8019AEF4 00000000 */ nop
/* 251150 0x8019AEF8 00000000 */ nop
/* 251151 0x8019AEFC 00000000 */ nop
