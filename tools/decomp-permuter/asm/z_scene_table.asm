.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel SceneTable_LookupEntrance
/* 143872 0x801322C0 AFA40000 */ sw	$a0, 0X0($sp)
/* 143873 0x801322C4 3084FFFF */ andi	$a0, $a0, 0XFFFF
/* 143874 0x801322C8 00047242 */ srl	$t6, $a0, 9
/* 143875 0x801322CC 000E7880 */ sll	$t7, $t6, 2
/* 143876 0x801322D0 01EE7823 */ subu	$t7, $t7, $t6
/* 143877 0x801322D4 000F7880 */ sll	$t7, $t7, 2
/* 143878 0x801322D8 3C03801C */ lui	$v1, %hi(gSceneEntranceTable + 0x4)
/* 143879 0x801322DC 006F1821 */ addu	$v1, $v1, $t7
/* 143880 0x801322E0 8C635724 */ lw	$v1, %lo(gSceneEntranceTable + 0x4)($v1)
/* 143881 0x801322E4 0004C102 */ srl	$t8, $a0, 4
/* 143882 0x801322E8 3319001F */ andi	$t9, $t8, 0X1F
/* 143883 0x801322EC 00194080 */ sll	$t0, $t9, 2
/* 143884 0x801322F0 00684821 */ addu	$t1, $v1, $t0
/* 143885 0x801322F4 8D250000 */ lw	$a1, 0X0($t1)
/* 143886 0x801322F8 308A000F */ andi	$t2, $a0, 0XF
/* 143887 0x801322FC 000A5880 */ sll	$t3, $t2, 2
/* 143888 0x80132300 01651021 */ addu	$v0, $t3, $a1
/* 143889 0x80132304 03E00008 */ jr	$ra
/* 143890 0x80132308 00000000 */ nop

glabel SceneTable_LookupEntranceScene
/* 143891 0x8013230C 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 143892 0x80132310 AFA40018 */ sw	$a0, 0X18($sp)
/* 143893 0x80132314 3084FFFF */ andi	$a0, $a0, 0XFFFF
/* 143894 0x80132318 AFBF0014 */ sw	$ra, 0X14($sp)
/* 143895 0x8013231C 0C04C8B0 */ jal	SceneTable_LookupEntrance
/* 143896 0x80132320 00000000 */ nop
/* 143897 0x80132324 80420000 */ lb	$v0, 0X0($v0)
/* 143898 0x80132328 8FBF0014 */ lw	$ra, 0X14($sp)
/* 143899 0x8013232C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 143900 0x80132330 03E00008 */ jr	$ra
/* 143901 0x80132334 00000000 */ nop

glabel SceneTable_LookupEntranceAbsoluteScene
/* 143902 0x80132338 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 143903 0x8013233C AFA40018 */ sw	$a0, 0X18($sp)
/* 143904 0x80132340 3084FFFF */ andi	$a0, $a0, 0XFFFF
/* 143905 0x80132344 AFBF0014 */ sw	$ra, 0X14($sp)
/* 143906 0x80132348 0C04C8B0 */ jal	SceneTable_LookupEntrance
/* 143907 0x8013234C 00000000 */ nop
/* 143908 0x80132350 80430000 */ lb	$v1, 0X0($v0)
/* 143909 0x80132354 8FBF0014 */ lw	$ra, 0X14($sp)
/* 143910 0x80132358 04610003 */ bgez	$v1, .L80132368
/* 143911 0x8013235C 00602025 */ move	$a0, $v1
/* 143912 0x80132360 10000001 */ b	.L80132368
/* 143913 0x80132364 00032023 */ negu	$a0, $v1
.L80132368:
/* 143914 0x80132368 00801025 */ move	$v0, $a0
/* 143915 0x8013236C 03E00008 */ jr	$ra
/* 143916 0x80132370 27BD0018 */ addiu	$sp, $sp, 0X18

glabel func_80132374
/* 143917 0x80132374 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 143918 0x80132378 AFA40018 */ sw	$a0, 0X18($sp)
/* 143919 0x8013237C 3084FFFF */ andi	$a0, $a0, 0XFFFF
/* 143920 0x80132380 AFBF0014 */ sw	$ra, 0X14($sp)
/* 143921 0x80132384 0C04C8B0 */ jal	SceneTable_LookupEntrance
/* 143922 0x80132388 00000000 */ nop
/* 143923 0x8013238C 80420001 */ lb	$v0, 0X1($v0)
/* 143924 0x80132390 8FBF0014 */ lw	$ra, 0X14($sp)
/* 143925 0x80132394 27BD0018 */ addiu	$sp, $sp, 0X18
/* 143926 0x80132398 03E00008 */ jr	$ra
/* 143927 0x8013239C 00000000 */ nop

glabel func_801323A0
/* 143928 0x801323A0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 143929 0x801323A4 AFA40018 */ sw	$a0, 0X18($sp)
/* 143930 0x801323A8 3084FFFF */ andi	$a0, $a0, 0XFFFF
/* 143931 0x801323AC AFBF0014 */ sw	$ra, 0X14($sp)
/* 143932 0x801323B0 0C04C8B0 */ jal	SceneTable_LookupEntrance
/* 143933 0x801323B4 00000000 */ nop
/* 143934 0x801323B8 94420002 */ lhu	$v0, 0X2($v0)
/* 143935 0x801323BC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 143936 0x801323C0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 143937 0x801323C4 03E00008 */ jr	$ra
/* 143938 0x801323C8 00000000 */ nop
/* 143939 0x801323CC 00000000 */ nop
