.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel StartHeap_Alloc
/* 007004 0x80086DD0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007005 0x80086DD4 00802825 */ move	$a1, $a0
/* 007006 0x80086DD8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007007 0x80086DDC 3C04800A */ lui	$a0, %hi(startHeap)
/* 007008 0x80086DE0 0C021CC9 */ jal	__osMalloc
/* 007009 0x80086DE4 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007010 0x80086DE8 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007011 0x80086DEC 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007012 0x80086DF0 03E00008 */ jr	$ra
/* 007013 0x80086DF4 00000000 */ nop

glabel StartHeap_AllocR
/* 007014 0x80086DF8 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007015 0x80086DFC 00802825 */ move	$a1, $a0
/* 007016 0x80086E00 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007017 0x80086E04 3C04800A */ lui	$a0, %hi(startHeap)
/* 007018 0x80086E08 0C021D02 */ jal	__osMallocR
/* 007019 0x80086E0C 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007020 0x80086E10 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007021 0x80086E14 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007022 0x80086E18 03E00008 */ jr	$ra
/* 007023 0x80086E1C 00000000 */ nop

glabel StartHeap_Realloc
/* 007024 0x80086E20 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007025 0x80086E24 00A03025 */ move	$a2, $a1
/* 007026 0x80086E28 00802825 */ move	$a1, $a0
/* 007027 0x80086E2C AFA40018 */ sw	$a0, 0X18($sp)
/* 007028 0x80086E30 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007029 0x80086E34 3C04800A */ lui	$a0, %hi(startHeap)
/* 007030 0x80086E38 0C021D79 */ jal	__osRealloc
/* 007031 0x80086E3C 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007032 0x80086E40 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007033 0x80086E44 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007034 0x80086E48 03E00008 */ jr	$ra
/* 007035 0x80086E4C 00000000 */ nop

glabel StartHeap_Free
/* 007036 0x80086E50 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007037 0x80086E54 00802825 */ move	$a1, $a0
/* 007038 0x80086E58 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007039 0x80086E5C 3C04800A */ lui	$a0, %hi(startHeap)
/* 007040 0x80086E60 0C021D3B */ jal	__osFree
/* 007041 0x80086E64 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007042 0x80086E68 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007043 0x80086E6C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007044 0x80086E70 03E00008 */ jr	$ra
/* 007045 0x80086E74 00000000 */ nop

glabel StartHeap_Calloc
/* 007046 0x80086E78 00803025 */ move	$a2, $a0
/* 007047 0x80086E7C 00C50019 */ multu	$a2, $a1
/* 007048 0x80086E80 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 007049 0x80086E84 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007050 0x80086E88 3C04800A */ lui	$a0, %hi(startHeap)
/* 007051 0x80086E8C 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007052 0x80086E90 00002812 */ mflo	$a1
/* 007053 0x80086E94 AFA5001C */ sw	$a1, 0X1C($sp)
/* 007054 0x80086E98 0C021CC9 */ jal	__osMalloc
/* 007055 0x80086E9C 00000000 */ nop
/* 007056 0x80086EA0 8FA5001C */ lw	$a1, 0X1C($sp)
/* 007057 0x80086EA4 10400004 */ beqz	$v0, .L80086EB8
/* 007058 0x80086EA8 00402025 */ move	$a0, $v0
/* 007059 0x80086EAC 0C02258C */ jal	bzero
/* 007060 0x80086EB0 AFA20024 */ sw	$v0, 0X24($sp)
/* 007061 0x80086EB4 8FA40024 */ lw	$a0, 0X24($sp)
.L80086EB8:
/* 007062 0x80086EB8 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007063 0x80086EBC 27BD0028 */ addiu	$sp, $sp, 0X28
/* 007064 0x80086EC0 00801025 */ move	$v0, $a0
/* 007065 0x80086EC4 03E00008 */ jr	$ra
/* 007066 0x80086EC8 00000000 */ nop

glabel StartHeap_AnalyzeArena
/* 007067 0x80086ECC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007068 0x80086ED0 AFA5001C */ sw	$a1, 0X1C($sp)
/* 007069 0x80086ED4 00802825 */ move	$a1, $a0
/* 007070 0x80086ED8 AFA40018 */ sw	$a0, 0X18($sp)
/* 007071 0x80086EDC AFBF0014 */ sw	$ra, 0X14($sp)
/* 007072 0x80086EE0 00C03825 */ move	$a3, $a2
/* 007073 0x80086EE4 3C04800A */ lui	$a0, %hi(startHeap)
/* 007074 0x80086EE8 8FA6001C */ lw	$a2, 0X1C($sp)
/* 007075 0x80086EEC 0C021DC5 */ jal	__osAnalyzeArena
/* 007076 0x80086EF0 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007077 0x80086EF4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007078 0x80086EF8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007079 0x80086EFC 03E00008 */ jr	$ra
/* 007080 0x80086F00 00000000 */ nop

glabel StartHeap_CheckArena
/* 007081 0x80086F04 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007082 0x80086F08 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007083 0x80086F0C 3C04800A */ lui	$a0, %hi(startHeap)
/* 007084 0x80086F10 0C021DF1 */ jal	__osCheckArena
/* 007085 0x80086F14 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007086 0x80086F18 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007087 0x80086F1C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007088 0x80086F20 03E00008 */ jr	$ra
/* 007089 0x80086F24 00000000 */ nop

glabel StartHeap_InitArena
/* 007090 0x80086F28 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007091 0x80086F2C 00A03025 */ move	$a2, $a1
/* 007092 0x80086F30 00802825 */ move	$a1, $a0
/* 007093 0x80086F34 AFA40018 */ sw	$a0, 0X18($sp)
/* 007094 0x80086F38 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007095 0x80086F3C 3C04800A */ lui	$a0, %hi(startHeap)
/* 007096 0x80086F40 0C021C83 */ jal	__osMallocInit
/* 007097 0x80086F44 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007098 0x80086F48 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007099 0x80086F4C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007100 0x80086F50 03E00008 */ jr	$ra
/* 007101 0x80086F54 00000000 */ nop

glabel StartHeap_Cleanup
/* 007102 0x80086F58 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007103 0x80086F5C AFBF0014 */ sw	$ra, 0X14($sp)
/* 007104 0x80086F60 3C04800A */ lui	$a0, %hi(startHeap)
/* 007105 0x80086F64 0C021CBF */ jal	__osMallocCleanup
/* 007106 0x80086F68 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007107 0x80086F6C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007108 0x80086F70 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007109 0x80086F74 03E00008 */ jr	$ra
/* 007110 0x80086F78 00000000 */ nop

glabel StartHeap_IsInitialized
/* 007111 0x80086F7C 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007112 0x80086F80 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007113 0x80086F84 3C04800A */ lui	$a0, %hi(startHeap)
/* 007114 0x80086F88 0C021CC7 */ jal	__osMallocIsInitalized
/* 007115 0x80086F8C 2484CD20 */ addiu	$a0, $a0, %lo(startHeap)
/* 007116 0x80086F90 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007117 0x80086F94 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007118 0x80086F98 03E00008 */ jr	$ra
/* 007119 0x80086F9C 00000000 */ nop
