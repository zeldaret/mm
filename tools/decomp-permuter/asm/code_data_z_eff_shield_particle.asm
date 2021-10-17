.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel sEffectShieldParticleVertices
/* 270860 0x801AE2F0 */ .word	0xFFE0FFE0
/* 270861 0x801AE2F4 */ .word	0x00000000
/* 270862 0x801AE2F8 */ .word	0x00000400
/* 270863 0x801AE2FC */ .word	0xFFFFFFFF
/* 270864 0x801AE300 */ .word	0x00200020
/* 270865 0x801AE304 */ .word	0x00000000
/* 270866 0x801AE308 */ .word	0x04000000
/* 270867 0x801AE30C */ .word	0xFFFFFFFF
/* 270868 0x801AE310 */ .word	0xFFE00020
/* 270869 0x801AE314 */ .word	0x00000000
/* 270870 0x801AE318 */ .word	0x00000000
/* 270871 0x801AE31C */ .word	0xFFFFFFFF
/* 270872 0x801AE320 */ .word	0x0020FFE0
/* 270873 0x801AE324 */ .word	0x00000000
/* 270874 0x801AE328 */ .word	0x04000400
/* 270875 0x801AE32C */ .word	0xFFFFFFFF
