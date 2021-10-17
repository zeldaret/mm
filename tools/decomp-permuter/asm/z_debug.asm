.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel static_context_init
/* 069192 0x800E93E0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 069193 0x800E93E4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 069194 0x800E93E8 0C021B74 */ jal	StartHeap_Alloc
/* 069195 0x800E93EC 240415D4 */ li	$a0, 0X15D4
/* 069196 0x800E93F0 3C03801F */ lui	$v1, %hi(gStaticContext)
/* 069197 0x800E93F4 24633F60 */ addiu	$v1, $v1, %lo(gStaticContext)
/* 069198 0x800E93F8 AC620000 */ sw	$v0, 0X0($v1)
/* 069199 0x800E93FC A0400000 */ sb	$zero, 0X0($v0)
/* 069200 0x800E9400 8C6F0000 */ lw	$t7, 0X0($v1)
/* 069201 0x800E9404 00001025 */ move	$v0, $zero
/* 069202 0x800E9408 240415C0 */ li	$a0, 0X15C0
/* 069203 0x800E940C A1E00001 */ sb	$zero, 0X1($t7)
/* 069204 0x800E9410 8C780000 */ lw	$t8, 0X0($v1)
/* 069205 0x800E9414 A3000002 */ sb	$zero, 0X2($t8)
/* 069206 0x800E9418 8C790000 */ lw	$t9, 0X0($v1)
/* 069207 0x800E941C AF200004 */ sw	$zero, 0X4($t9)
/* 069208 0x800E9420 8C680000 */ lw	$t0, 0X0($v1)
/* 069209 0x800E9424 A1000003 */ sb	$zero, 0X3($t0)
.L800E9428:
/* 069210 0x800E9428 8C690000 */ lw	$t1, 0X0($v1)
/* 069211 0x800E942C 01225021 */ addu	$t2, $t1, $v0
/* 069212 0x800E9430 A5400014 */ sh	$zero, 0X14($t2)
/* 069213 0x800E9434 8C6B0000 */ lw	$t3, 0X0($v1)
/* 069214 0x800E9438 01626021 */ addu	$t4, $t3, $v0
/* 069215 0x800E943C A5800016 */ sh	$zero, 0X16($t4)
/* 069216 0x800E9440 8C6D0000 */ lw	$t5, 0X0($v1)
/* 069217 0x800E9444 01A27021 */ addu	$t6, $t5, $v0
/* 069218 0x800E9448 A5C00018 */ sh	$zero, 0X18($t6)
/* 069219 0x800E944C 8C6F0000 */ lw	$t7, 0X0($v1)
/* 069220 0x800E9450 01E2C021 */ addu	$t8, $t7, $v0
/* 069221 0x800E9454 24420008 */ addiu	$v0, $v0, 0X8
/* 069222 0x800E9458 1444FFF3 */ bne	$v0, $a0, .L800E9428
/* 069223 0x800E945C A700001A */ sh	$zero, 0X1A($t8)
/* 069224 0x800E9460 8FBF0014 */ lw	$ra, 0X14($sp)
/* 069225 0x800E9464 27BD0018 */ addiu	$sp, $sp, 0X18
/* 069226 0x800E9468 03E00008 */ jr	$ra
/* 069227 0x800E946C 00000000 */ nop
