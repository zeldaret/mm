.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80931410
/* 000780 0x80931410 */ .word	0x0A110900
/* 000781 0x80931414 */ .word	0x20010000
/* 000782 0x80931418 */ .word	0x00000000
/* 000783 0x8093141C */ .word	0xF7CFFFFF
/* 000784 0x80931420 */ .word	0x00040000
/* 000785 0x80931424 */ .word	0xF7CFFFFF
/* 000786 0x80931428 */ .word	0x00000000
/* 000787 0x8093142C */ .word	0x01010000
/* 000788 0x80931430 */ .word	0x000B001C
/* 000789 0x80931434 */ .word	0x00000000
/* 000790 0x80931438 */ .word	0x00000000
glabel En_Tubo_Trap_InitVars
/* 000791 0x8093143C */ .word	0x008D0600
/* 000792 0x80931440 */ .word	0x00000000
/* 000793 0x80931444 */ .word	0x00030000
/* 000794 0x80931448 */ .word	0x000001A4
/* 000795 0x8093144C */ .word	EnTuboTrap_Init
/* 000796 0x80931450 */ .word	EnTuboTrap_Destroy
/* 000797 0x80931454 */ .word	EnTuboTrap_Update
/* 000798 0x80931458 */ .word	EnTuboTrap_Draw
glabel D_8093145C
/* 000799 0x8093145C */ .word	0xC85800C5
/* 000800 0x80931460 */ .word	0xB0FC0FA0
/* 000801 0x80931464 */ .word	0xB1000064
/* 000802 0x80931468 */ .word	0x31040064
glabel D_8093146C
/* 000803 0x8093146C */ .word	0x28282819
/* 000804 0x80931470 */ .word	0x1C000000
/* 000805 0x80931474 */ .word	0x00000000
/* 000806 0x80931478 */ .word	0x00000000
/* 000807 0x8093147C */ .word	0x00000000
