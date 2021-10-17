.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel actorInitVarFuncs
/* 287656 0x801BE960 */ .word	IChain_Apply_u8
/* 287657 0x801BE964 */ .word	IChain_Apply_s8
/* 287658 0x801BE968 */ .word	IChain_Apply_u16
/* 287659 0x801BE96C */ .word	IChain_Apply_s16
/* 287660 0x801BE970 */ .word	IChain_Apply_u32
/* 287661 0x801BE974 */ .word	IChain_Apply_s32
/* 287662 0x801BE978 */ .word	IChain_Apply_f32
/* 287663 0x801BE97C */ .word	IChain_Apply_f32div1000
/* 287664 0x801BE980 */ .word	IChain_Apply_Vec3f
/* 287665 0x801BE984 */ .word	IChain_Apply_Vec3fdiv1000
/* 287666 0x801BE988 */ .word	IChain_Apply_Vec3s
/* 287667 0x801BE98C */ .word	0x00000000
