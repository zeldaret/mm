.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Aqua_InitVars
/* 000768 0x80ACC2A0 */ .word	0x01AF0700
/* 000769 0x80ACC2A4 */ .word	0x00000010
/* 000770 0x80ACC2A8 */ .word	0x00010000
/* 000771 0x80ACC2AC */ .word	0x0000019C
/* 000772 0x80ACC2B0 */ .word	ObjAqua_Init
/* 000773 0x80ACC2B4 */ .word	ObjAqua_Destroy
/* 000774 0x80ACC2B8 */ .word	ObjAqua_Update
/* 000775 0x80ACC2BC */ .word	ObjAqua_Draw
glabel D_80ACC2C0
/* 000776 0x80ACC2C0 */ .word	0x0A210000
/* 000777 0x80ACC2C4 */ .word	0x00010000
/* 000778 0x80ACC2C8 */ .word	0x00000000
/* 000779 0x80ACC2CC */ .word	0xF7CFFFFF
/* 000780 0x80ACC2D0 */ .word	0x00000000
/* 000781 0x80ACC2D4 */ .word	0x00000000
/* 000782 0x80ACC2D8 */ .word	0x00000000
/* 000783 0x80ACC2DC */ .word	0x19000000
/* 000784 0x80ACC2E0 */ .word	0x0006000A
/* 000785 0x80ACC2E4 */ .word	0x00000000
/* 000786 0x80ACC2E8 */ .word	0x00000000
glabel D_80ACC2EC
/* 000787 0x80ACC2EC */ .word	0xD0BC0000
/* 000788 0x80ACC2F0 */ .word	0xD0300000
/* 000789 0x80ACC2F4 */ .word	0xB874FC7C
/* 000790 0x80ACC2F8 */ .word	0xB878F060
/* 000791 0x80ACC2FC */ .word	0xB0FC0FA0
/* 000792 0x80ACC300 */ .word	0xB100012C
/* 000793 0x80ACC304 */ .word	0x3104012C
glabel D_80ACC308
/* 000794 0x80ACC308 */ .word	0x3A83126F
/* 000795 0x80ACC30C */ .word	0x3A378034
/* 000796 0x80ACC310 */ .word	0x3A83126F
glabel D_80ACC314
/* 000797 0x80ACC314 */ .word	0x3C0CE704
/* 000798 0x80ACC318 */ .word	0x3A51B717
/* 000799 0x80ACC31C */ .word	0x3C0CE704
glabel D_80ACC320
/* 000800 0x80ACC320 */ .word	0x3C23D70A
/* 000801 0x80ACC324 */ .word	0x3B2A64C3
/* 000802 0x80ACC328 */ .word	0x3C23D70A
/* 000803 0x80ACC32C */ .word	0x00000000
