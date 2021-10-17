.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Smork_InitVars
/* 000764 0x80A3E270 */ .word	0x01570600
/* 000765 0x80A3E274 */ .word	0x00000030
/* 000766 0x80A3E278 */ .word	0x016D0000
/* 000767 0x80A3E27C */ .word	0x000001C8
/* 000768 0x80A3E280 */ .word	ObjSmork_Init
/* 000769 0x80A3E284 */ .word	ObjSmork_Destroy
/* 000770 0x80A3E288 */ .word	ObjSmork_Update
/* 000771 0x80A3E28C */ .word	ObjSmork_Draw
glabel D_80A3E290
/* 000772 0x80A3E290 */ .word	0xFA7F1405
/* 000773 0x80A3E294 */ .word	0x012D0000
/* 000774 0x80A3E298 */ .word	0xFF75F469
/* 000775 0x80A3E29C */ .short	0x0000
/* 000775 0x80A3E29C */ .byte	0x00
glabel D_80A3E29F
/* 000775 0x80A3E29C */ .byte	0x00
/* 000776 0x80A3E2A0 */ .word	0x000008D5
/* 000777 0x80A3E2A4 */ .word	0x025B0000
/* 000778 0x80A3E2A8 */ .word	0x020003CC
/* 000779 0x80A3E2AC */ .short	0x4D44
/* 000779 0x80A3E2AC */ .byte	0x34
glabel D_80A3E2AF
/* 000779 0x80A3E2AC */ .byte	0xFF
/* 000780 0x80A3E2B0 */ .word	0x00001BAC
/* 000781 0x80A3E2B4 */ .word	0x012D0000
/* 000782 0x80A3E2B8 */ .word	0x0200E9D0
/* 000783 0x80A3E2BC */ .short	0x0000
/* 000783 0x80A3E2BC */ .byte	0x00
glabel D_80A3E2BF
/* 000783 0x80A3E2BC */ .byte	0x00
/* 000784 0x80A3E2C0 */ .word	0xFBAD08D5
/* 000785 0x80A3E2C4 */ .word	0x00000000
/* 000786 0x80A3E2C8 */ .word	0x00000400
/* 000787 0x80A3E2CC */ .word	0x00000000
/* 000788 0x80A3E2D0 */ .word	0x05811405
/* 000789 0x80A3E2D4 */ .word	0x012D0000
/* 000790 0x80A3E2D8 */ .word	0x048BF469
/* 000791 0x80A3E2DC */ .word	0x00000000
/* 000792 0x80A3E2E0 */ .word	0x045308D5
/* 000793 0x80A3E2E4 */ .word	0x00000000
/* 000794 0x80A3E2E8 */ .word	0x04000400
/* 000795 0x80A3E2EC */ .word	0x00000000
/* 000796 0x80A3E2F0 */ .word	0x00000000
/* 000797 0x80A3E2F4 */ .word	0x00000000
/* 000798 0x80A3E2F8 */ .word	0x0200103A
/* 000799 0x80A3E2FC */ .word	0x2621197E
