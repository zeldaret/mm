.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Kbt_InitVars
/* 000892 0x80B34B20 */ .word	0x01F60400
/* 000893 0x80B34B24 */ .word	0x00000009
/* 000894 0x80B34B28 */ .word	0x01CF0000
/* 000895 0x80B34B2C */ .word	0x0000028C
/* 000896 0x80B34B30 */ .word	EnKbt_Init
/* 000897 0x80B34B34 */ .word	EnKbt_Destroy
/* 000898 0x80B34B38 */ .word	EnKbt_Update
/* 000899 0x80B34B3C */ .word	EnKbt_Draw
glabel D_80B34B40
/* 000900 0x80B34B40 */ .word	0x00000200
/* 000901 0x80B34B44 */ .word	0x02000000
/* 000902 0x80B34B48 */ .word	0x00000002
/* 000903 0x80B34B4C */ .word	0x02000000
glabel D_80B34B50
/* 000904 0x80B34B50 */ .word	0x06000670
/* 000905 0x80B34B54 */ .word	0x06001674
/* 000906 0x80B34B58 */ .word	0x06002084
/* 000907 0x80B34B5C */ .word	0x06000FE8
/* 000908 0x80B34B60 */ .word	0x06001940
/* 000909 0x80B34B64 */ .word	0x0600E7BC
/* 000910 0x80B34B68 */ .word	0x0600F0C8
/* 000911 0x80B34B6C */ .word	0x06002710
/* 000912 0x80B34B70 */ .word	0x06002DE0
/* 000913 0x80B34B74 */ .word	0x06003414
/* 000914 0x80B34B78 */ .word	0x06003D24
/* 000915 0x80B34B7C */ .word	0x06001BF4
/* 000916 0x80B34B80 */ .word	0x06002084
glabel D_80B34B84
/* 000917 0x80B34B84 */ .word	0x43FA0000
/* 000918 0x80B34B88 */ .word	0x43FA0000
/* 000919 0x80B34B8C */ .word	0x00000000
glabel D_80B34B90
/* 000920 0x80B34B90 */ .word	0x0600A5B8
/* 000921 0x80B34B94 */ .word	0x0600ADB8
glabel D_80B34B98
/* 000922 0x80B34B98 */ .word	0x0600B5B8
/* 000923 0x80B34B9C */ .word	0x0600BDB8
/* 000924 0x80B34BA0 */ .word	0x0600C5B8
/* 000925 0x80B34BA4 */ .word	0x0600CDB8
/* 000926 0x80B34BA8 */ .word	0x0600D5B8
/* 000927 0x80B34BAC */ .word	0x00000000
