.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80099400
/* 025832 0x80099400 */ .word	0x3FF00000
/* 025833 0x80099404 */ .word	0x00000000
/* 025834 0x80099408 */ .word	0xBFC55554
/* 025835 0x8009940C */ .word	0xBC83656D
/* 025836 0x80099410 */ .word	0x3F8110ED
/* 025837 0x80099414 */ .word	0x3804C2A0
/* 025838 0x80099418 */ .word	0xBF29F6FF
/* 025839 0x8009941C */ .word	0xEEA56814
/* 025840 0x80099420 */ .word	0x3EC5DBDF
/* 025841 0x80099424 */ .word	0x0E314BFE
glabel D_80099428
/* 025842 0x80099428 */ .word	0x3FD45F30
/* 025843 0x8009942C */ .word	0x6DC9C883
glabel D_80099430
/* 025844 0x80099430 */ .word	0x400921FB
/* 025845 0x80099434 */ .word	0x50000000
glabel D_80099438
/* 025846 0x80099438 */ .word	0x3E6110B4
/* 025847 0x8009943C */ .word	0x611A6263
glabel D_80099440
/* 025848 0x80099440 */ .word	0x00000000
/* 025849 0x80099444 */ .word	0x00000000
/* 025850 0x80099448 */ .word	0x00000000
/* 025851 0x8009944C */ .word	0x00000000
