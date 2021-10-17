.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E0230
/* 322012 0x801E0230 */ .word	0x50524F54
/* 322013 0x801E0234 */ .word	0x4F204100
glabel D_801E0238
/* 322014 0x801E0238 */ .word	0x41000000
glabel D_801E023C
/* 322015 0x801E023C */ .word	0x43000000
glabel D_801E0240
/* 322016 0x801E0240 */ .word	0x44284E45
/* 322017 0x801E0244 */ .word	0x57290000
glabel D_801E0248
/* 322018 0x801E0248 */ .word	0x42206F72
/* 322019 0x801E024C */ .word	0x20440000
glabel D_801E0250
/* 322020 0x801E0250 */ .word	0x554E4B4E
/* 322021 0x801E0254 */ .word	0x4F574E00
glabel D_801E0258
/* 322022 0x801E0258 */ .word	0x2E2E2F73
/* 322023 0x801E025C */ .word	0x79735F66
/* 322024 0x801E0260 */ .word	0x6C617368
/* 322025 0x801E0264 */ .word	0x726F6D2E
/* 322026 0x801E0268 */ .word	0x63000000
glabel D_801E026C
/* 322027 0x801E026C */ .word	0x7379735F
/* 322028 0x801E0270 */ .word	0x666C6173
/* 322029 0x801E0274 */ .word	0x68726F6D
/* 322030 0x801E0278 */ .word	0x00000000
/* 322031 0x801E027C */ .word	0x00000000
