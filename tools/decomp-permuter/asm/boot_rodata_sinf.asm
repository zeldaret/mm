.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel P
/* 025712 0x80099220 */ .word	0x3FF00000
/* 025713 0x80099224 */ .word	0x00000000
/* 025714 0x80099228 */ .word	0xBFC55554
/* 025715 0x8009922C */ .word	0xBC83656D
/* 025716 0x80099230 */ .word	0x3F8110ED
/* 025717 0x80099234 */ .word	0x3804C2A0
/* 025718 0x80099238 */ .word	0xBF29F6FF
/* 025719 0x8009923C */ .word	0xEEA56814
/* 025720 0x80099240 */ .word	0x3EC5DBDF
/* 025721 0x80099244 */ .word	0x0E314BFE
glabel rpi
/* 025722 0x80099248 */ .word	0x3FD45F30
/* 025723 0x8009924C */ .word	0x6DC9C883
glabel pihi
/* 025724 0x80099250 */ .word	0x400921FB
/* 025725 0x80099254 */ .word	0x50000000
glabel pilo
/* 025726 0x80099258 */ .word	0x3E6110B4
/* 025727 0x8009925C */ .word	0x611A6263
glabel zero
/* 025728 0x80099260 */ .word	0x00000000
/* 025729 0x80099264 */ .word	0x00000000
/* 025730 0x80099268 */ .word	0x00000000
/* 025731 0x8009926C */ .word	0x00000000
