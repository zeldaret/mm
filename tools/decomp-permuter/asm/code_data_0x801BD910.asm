.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel initialGameStateInfo
/* 286612 0x801BD910 */ .word	0x00000000
/* 286613 0x801BD914 */ .word	0x00000000
/* 286614 0x801BD918 */ .word	0x00000000
/* 286615 0x801BD91C */ .word	0x00000000
/* 286616 0x801BD920 */ .word	0x00000000
/* 286617 0x801BD924 */ .word	0x00000000
/* 286618 0x801BD928 */ .word	TitleSetup_Init
/* 286619 0x801BD92C */ .word	TitleSetup_Destroy
/* 286620 0x801BD930 */ .word	0x00000000
/* 286621 0x801BD934 */ .word	0x00000000
/* 286622 0x801BD938 */ .word	0x00000000
/* 286623 0x801BD93C */ .word	0x000000A4
glabel D_801BD940
/* 286624 0x801BD940 */ .word	0x00000000
/* 286625 0x801BD944 */ .word	0x00C7ADF0
/* 286626 0x801BD948 */ .word	0x00C7E2D0
/* 286627 0x801BD94C */ .word	func_80800910
/* 286628 0x801BD950 */ .word	Opening_SetupForTitleCutscene
/* 286629 0x801BD954 */ .word	0x00000000
/* 286630 0x801BD958 */ .word	func_80801B4C
/* 286631 0x801BD95C */ .word	func_80801B28
/* 286632 0x801BD960 */ .word	0x00000000
/* 286633 0x801BD964 */ .word	0x00000000
/* 286634 0x801BD968 */ .word	0x00000000
/* 286635 0x801BD96C */ .word	0x00000280
glabel titleGameStateInfo
/* 286636 0x801BD970 */ .word	0x00000000
/* 286637 0x801BD974 */ .word	_codeSegmentRomEnd
/* 286638 0x801BD978 */ .word	0x00C7ADF0
/* 286639 0x801BD97C */ .word	Title_UpdateCounters
/* 286640 0x801BD980 */ .word	func_80800910
/* 286641 0x801BD984 */ .word	0x00000000
/* 286642 0x801BD988 */ .word	Title_Init
/* 286643 0x801BD98C */ .word	Title_Destroy
/* 286644 0x801BD990 */ .word	0x00000000
/* 286645 0x801BD994 */ .word	0x00000000
/* 286646 0x801BD998 */ .word	0x00000000
/* 286647 0x801BD99C */ .word	0x00000248
glabel mainGameStateInfo
/* 286648 0x801BD9A0 */ .word	0x00000000
/* 286649 0x801BD9A4 */ .word	0x00000000
/* 286650 0x801BD9A8 */ .word	0x00000000
/* 286651 0x801BD9AC */ .word	0x00000000
/* 286652 0x801BD9B0 */ .word	0x00000000
/* 286653 0x801BD9B4 */ .word	0x00000000
/* 286654 0x801BD9B8 */ .word	Play_Init
/* 286655 0x801BD9BC */ .word	Play_Fini
/* 286656 0x801BD9C0 */ .word	0x00000000
/* 286657 0x801BD9C4 */ .word	0x00000000
/* 286658 0x801BD9C8 */ .word	0x00000000
/* 286659 0x801BD9CC */ .word	0x00019258
glabel openingGameStateInfo
/* 286660 0x801BD9D0 */ .word	0x00000000
/* 286661 0x801BD9D4 */ .word	0x00C7E2D0
/* 286662 0x801BD9D8 */ .word	0x00C7E4F0
/* 286663 0x801BD9DC */ .word	Opening_SetupForTitleCutscene
/* 286664 0x801BD9E0 */ .word	func_80804010
/* 286665 0x801BD9E4 */ .word	0x00000000
/* 286666 0x801BD9E8 */ .word	Opening_Init
/* 286667 0x801BD9EC */ .word	Opening_Destroy
/* 286668 0x801BD9F0 */ .word	0x00000000
/* 286669 0x801BD9F4 */ .word	0x00000000
/* 286670 0x801BD9F8 */ .word	0x00000000
/* 286671 0x801BD9FC */ .word	0x00000210
glabel fileChooseGameStateInfo
/* 286672 0x801BDA00 */ .word	0x00000000
/* 286673 0x801BDA04 */ .word	0x00C7E4F0
/* 286674 0x801BDA08 */ .word	0x00C8F360
/* 286675 0x801BDA0C */ .word	func_80804010
/* 286676 0x801BDA10 */ .word	Daytelop_UpdateState
/* 286677 0x801BDA14 */ .word	0x00000000
/* 286678 0x801BDA18 */ .word	FileChoose_Init
/* 286679 0x801BDA1C */ .word	FileChoose_Destroy
/* 286680 0x801BDA20 */ .word	0x00000000
/* 286681 0x801BDA24 */ .word	0x00000000
/* 286682 0x801BDA28 */ .word	0x00000000
/* 286683 0x801BDA2C */ .word	0x00024558
glabel daytelopGameStateInfo
/* 286684 0x801BDA30 */ .word	0x00000000
/* 286685 0x801BDA34 */ .word	0x00C8F360
/* 286686 0x801BDA38 */ .word	0x00C90550
/* 286687 0x801BDA3C */ .word	Daytelop_UpdateState
/* 286688 0x801BDA40 */ .word	func_808160A0
/* 286689 0x801BDA44 */ .word	0x00000000
/* 286690 0x801BDA48 */ .word	Daytelop_Init
/* 286691 0x801BDA4C */ .word	Daytelop_Destroy
/* 286692 0x801BDA50 */ .word	0x00000000
/* 286693 0x801BDA54 */ .word	0x00000000
/* 286694 0x801BDA58 */ .word	0x00000000
/* 286695 0x801BDA5C */ .word	0x00000248
glabel graphNumGameStates
/* 286696 0x801BDA60 */ .word	0x00000007
/* 286697 0x801BDA64 */ .word	0x00000000
/* 286698 0x801BDA68 */ .word	0x00000000
/* 286699 0x801BDA6C */ .word	0x00000000
