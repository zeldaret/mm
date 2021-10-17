.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Zoraegg_InitVars
/* 002272 0x80B33910 */ .word	0x01F50700
/* 002273 0x80B33914 */ .word	0x00000010
/* 002274 0x80B33918 */ .word	0x01CE0000
/* 002275 0x80B3391C */ .word	0x000001FC
/* 002276 0x80B33920 */ .word	EnZoraegg_Init
/* 002277 0x80B33924 */ .word	EnZoraegg_Destroy
/* 002278 0x80B33928 */ .word	EnZoraegg_Update
/* 002279 0x80B3392C */ .word	EnZoraegg_Draw
glabel D_80B33930
/* 002280 0x80B33930 */ .word	0x01C901CA
/* 002281 0x80B33934 */ .word	0x01CB01CC
/* 002282 0x80B33938 */ .word	0x01CD01CE
/* 002283 0x80B3393C */ .word	0x01D00000
glabel D_80B33940
/* 002284 0x80B33940 */ .word	0x3F800000
/* 002285 0x80B33944 */ .word	0x3F89999A
/* 002286 0x80B33948 */ .word	0x3F933333
/* 002287 0x80B3394C */ .word	0x3F89999A
glabel D_80B33950
/* 002288 0x80B33950 */ .word	0x06003430
/* 002289 0x80B33954 */ .word	0x06004430
/* 002290 0x80B33958 */ .word	0x06004830
/* 002291 0x80B3395C */ .word	0x00000000
