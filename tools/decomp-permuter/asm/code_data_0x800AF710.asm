.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel sEffInfoTable
/* 270876 0x801AE330 */ .word	0x000004C4
/* 270877 0x801AE334 */ .word	EffectSpark_Init
/* 270878 0x801AE338 */ .word	EffectSpark_Destroy
/* 270879 0x801AE33C */ .word	EffectSpark_Update
/* 270880 0x801AE340 */ .word	EffectSpark_Draw
/* 270881 0x801AE344 */ .word	0x000001AC
/* 270882 0x801AE348 */ .word	EffectBlure_Init1
/* 270883 0x801AE34C */ .word	EffectBlure_Destroy
/* 270884 0x801AE350 */ .word	EffectBlure_Update
/* 270885 0x801AE354 */ .word	EffectBlure_Draw
/* 270886 0x801AE358 */ .word	0x000001AC
/* 270887 0x801AE35C */ .word	EffectBlure_Init2
/* 270888 0x801AE360 */ .word	EffectBlure_Destroy
/* 270889 0x801AE364 */ .word	EffectBlure_Update
/* 270890 0x801AE368 */ .word	EffectBlure_Draw
/* 270891 0x801AE36C */ .word	0x000001C8
/* 270892 0x801AE370 */ .word	EffectShieldParticle_Init
/* 270893 0x801AE374 */ .word	EffectShieldParticle_Destroy
/* 270894 0x801AE378 */ .word	EffectShieldParticle_Update
/* 270895 0x801AE37C */ .word	EffectShieldParticle_Draw
/* 270896 0x801AE380 */ .word	0x0000060C
/* 270897 0x801AE384 */ .word	EffectTireMark_Init
/* 270898 0x801AE388 */ .word	EffectTireMark_Destroy
/* 270899 0x801AE38C */ .word	EffectTireMark_Update
/* 270900 0x801AE390 */ .word	EffectTireMark_Draw
/* 270901 0x801AE394 */ .word	0x00000000
/* 270902 0x801AE398 */ .word	0x00000000
/* 270903 0x801AE39C */ .word	0x00000000
