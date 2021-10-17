.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801BC240
/* 285152 0x801BC240 */ .word	0xFD700000
/* 285153 0x801BC244 */ .word	0x04076C40
/* 285154 0x801BC248 */ .word	0xF5700000
/* 285155 0x801BC24C */ .word	0x07094250
/* 285156 0x801BC250 */ .word	0xE6000000
/* 285157 0x801BC254 */ .word	0x00000000
/* 285158 0x801BC258 */ .word	0xF3000000
/* 285159 0x801BC25C */ .word	0x073FF100
/* 285160 0x801BC260 */ .word	0xE7000000
/* 285161 0x801BC264 */ .word	0x00000000
/* 285162 0x801BC268 */ .word	0xF5701000
/* 285163 0x801BC26C */ .word	0x00094250
/* 285164 0x801BC270 */ .word	0xF2000000
/* 285165 0x801BC274 */ .word	0x0007C07C
/* 285166 0x801BC278 */ .word	0xFCFF9604
/* 285167 0x801BC27C */ .word	0xFFFDFFF8
/* 285168 0x801BC280 */ .word	0xDF000000
/* 285169 0x801BC284 */ .word	0x00000000
glabel D_801BC288
/* 285170 0x801BC288 */ .word	0x01003006
/* 285171 0x801BC28C */ .word	D_801BC210
/* 285172 0x801BC290 */ .word	0x05000204
/* 285173 0x801BC294 */ .word	0x00000000
/* 285174 0x801BC298 */ .word	0xDF000000
/* 285175 0x801BC29C */ .word	0x00000000
