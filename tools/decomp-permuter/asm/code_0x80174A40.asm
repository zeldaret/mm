.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel Graph_GfxPlusOne
/* 211936 0x80174A40 24820008 */ addiu	$v0, $a0, 0X8
/* 211937 0x80174A44 03E00008 */ jr	$ra
/* 211938 0x80174A48 00000000 */ nop

glabel Graph_BranchDlist
/* 211939 0x80174A4C 3C0EDE01 */ lui	$t6, 0xDE01
/* 211940 0x80174A50 AC8E0000 */ sw	$t6, 0X0($a0)
/* 211941 0x80174A54 AC850004 */ sw	$a1, 0X4($a0)
/* 211942 0x80174A58 00A01025 */ move	$v0, $a1
/* 211943 0x80174A5C 03E00008 */ jr	$ra
/* 211944 0x80174A60 00000000 */ nop

glabel Graph_DlistAlloc
/* 211945 0x80174A64 8C820000 */ lw	$v0, 0X0($a0)
/* 211946 0x80174A68 24A50007 */ addiu	$a1, $a1, 0X7
/* 211947 0x80174A6C 2401FFF8 */ li	$at, -0X8
/* 211948 0x80174A70 00A12824 */ and	$a1, $a1, $at
/* 211949 0x80174A74 24430008 */ addiu	$v1, $v0, 0X8
/* 211950 0x80174A78 3C0EDE01 */ lui	$t6, 0xDE01
/* 211951 0x80174A7C 00653021 */ addu	$a2, $v1, $a1
/* 211952 0x80174A80 AC460004 */ sw	$a2, 0X4($v0)
/* 211953 0x80174A84 AC4E0000 */ sw	$t6, 0X0($v0)
/* 211954 0x80174A88 AC860000 */ sw	$a2, 0X0($a0)
/* 211955 0x80174A8C 00601025 */ move	$v0, $v1
/* 211956 0x80174A90 03E00008 */ jr	$ra
/* 211957 0x80174A94 00000000 */ nop
/* 211958 0x80174A98 00000000 */ nop
/* 211959 0x80174A9C 00000000 */ nop
