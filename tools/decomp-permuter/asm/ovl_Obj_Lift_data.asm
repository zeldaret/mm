.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Lift_InitVars
/* 000604 0x8093DD30 */ .word	0x00950100
/* 000605 0x8093DD34 */ .word	0x00000010
/* 000606 0x8093DD38 */ .word	0x00ED0000
/* 000607 0x8093DD3C */ .word	0x0000017C
/* 000608 0x8093DD40 */ .word	ObjLift_Init
/* 000609 0x8093DD44 */ .word	ObjLift_Destroy
/* 000610 0x8093DD48 */ .word	ObjLift_Update
/* 000611 0x8093DD4C */ .word	ObjLift_Draw
glabel D_8093DD50
/* 000612 0x8093DD50 */ .word	0x0000000A
/* 000613 0x8093DD54 */ .word	0x0014001E
/* 000614 0x8093DD58 */ .word	0x00280032
/* 000615 0x8093DD5C */ .word	0x003C0000
glabel D_8093DD60
/* 000616 0x8093DD60 */ .word	0x0078FF88
/* 000617 0x8093DD64 */ .word	0x00780000
/* 000618 0x8093DD68 */ .word	0x00780078
/* 000619 0x8093DD6C */ .word	0x0000FF88
/* 000620 0x8093DD70 */ .word	0x00000000
/* 000621 0x8093DD74 */ .word	0x00000078
/* 000622 0x8093DD78 */ .word	0xFF88FF88
/* 000623 0x8093DD7C */ .word	0xFF880000
/* 000624 0x8093DD80 */ .word	0xFF880078
glabel D_8093DD84
/* 000625 0x8093DD84 */ .word	0xB874FDA8
/* 000626 0x8093DD88 */ .word	0xB878C568
/* 000627 0x8093DD8C */ .word	0xB0FC0FA0
/* 000628 0x8093DD90 */ .word	0xB100015E
/* 000629 0x8093DD94 */ .word	0x3104015E
glabel D_8093DD98
/* 000630 0x8093DD98 */ .word	0x3DCCCCCD
/* 000631 0x8093DD9C */ .word	0x3D4CCCCD
glabel D_8093DDA0
/* 000632 0x8093DDA0 */ .word	0xC1900000
/* 000633 0x8093DDA4 */ .word	0xC1100000
/* 000634 0x8093DDA8 */ .word	0x00000000
/* 000635 0x8093DDAC */ .word	0x00000000
