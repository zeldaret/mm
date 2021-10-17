.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E0200
/* 322000 0x801E0200 */ .word	0x3C03126F
glabel D_801E0204
/* 322001 0x801E0204 */ .word	0x3D088889
glabel D_801E0208
/* 322002 0x801E0208 */ .word	0x43360B61
glabel D_801E020C
/* 322003 0x801E020C */ .word	0x3B360B61
glabel D_801E0210
/* 322004 0x801E0210 */ .word	0x3DCCCCCD
glabel D_801E0214
/* 322005 0x801E0214 */ .word	0x3C03126F
glabel D_801E0218
/* 322006 0x801E0218 */ .word	0x3C23D70A
glabel D_801E021C
/* 322007 0x801E021C */ .word	0x43360B61
glabel D_801E0220
/* 322008 0x801E0220 */ .word	0x3B360B61
glabel D_801E0224
/* 322009 0x801E0224 */ .word	0x3DCCCCCD
glabel D_801E0228
/* 322010 0x801E0228 */ .word	0x3C03126F
/* 322011 0x801E022C */ .word	0x00000000
