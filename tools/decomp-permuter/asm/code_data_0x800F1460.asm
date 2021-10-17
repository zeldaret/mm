.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel actorCutscenesGlobalCutscenes
/* 286556 0x801BD830 */ .word	0xFF9CFFFF
/* 286557 0x801BD834 */ .word	0xFFFFFFFF
/* 286558 0x801BD838 */ .word	0xFFFFFFFF
/* 286559 0x801BD83C */ .word	0xFFFFFFFF
/* 286560 0x801BD840 */ .word	0xFF9CFFFF
/* 286561 0x801BD844 */ .word	0xFFFFFFFF
/* 286562 0x801BD848 */ .word	0xFFFFFFFF
/* 286563 0x801BD84C */ .word	0xFFFFFFFF
/* 286564 0x801BD850 */ .word	0xFF9CFFFF
/* 286565 0x801BD854 */ .word	0xFFFFFFFF
/* 286566 0x801BD858 */ .word	0xFFFFFFFF
/* 286567 0x801BD85C */ .word	0xFFFFFFFF
/* 286568 0x801BD860 */ .word	0x0002FFFF
/* 286569 0x801BD864 */ .word	0xFFE7FFFF
/* 286570 0x801BD868 */ .word	0xFFFFFFFF
/* 286571 0x801BD86C */ .word	0x00000020
/* 286572 0x801BD870 */ .word	0x7FFDFFFF
/* 286573 0x801BD874 */ .word	0xFFFFFFFF
/* 286574 0x801BD878 */ .word	0xFFFFFFFF
/* 286575 0x801BD87C */ .word	0xFFFF00FF
/* 286576 0x801BD880 */ .word	0x7FFCFFFF
/* 286577 0x801BD884 */ .word	0xFFFFFFFF
/* 286578 0x801BD888 */ .word	0xFFFFFFFF
/* 286579 0x801BD88C */ .word	0xFFFF00FF
/* 286580 0x801BD890 */ .word	0x7FFEFFFE
/* 286581 0x801BD894 */ .word	0xFFF2FFFF
/* 286582 0x801BD898 */ .word	0xFFFF00FF
/* 286583 0x801BD89C */ .word	0xFFFF0020
/* 286584 0x801BD8A0 */ .word	0x0000FFFF
/* 286585 0x801BD8A4 */ .word	0xFFFFFFFF
/* 286586 0x801BD8A8 */ .word	0xFFFF00FF
/* 286587 0x801BD8AC */ .word	0xFFFF0020
glabel actorCutsceneCurrent
/* 286588 0x801BD8B0 */ .short	0xFFFF
glabel actorCutsceneCurrentLength
/* 286588 0x801BD8B0 */ .short	0x0000
glabel actorCutsceneEnding
/* 286589 0x801BD8B4 */ .short	0xFFFF
glabel actorCutsceneCurrentCamera
/* 286589 0x801BD8B4 */ .short	0x0000
glabel actorCutsceneCurrentCutsceneActor
/* 286590 0x801BD8B8 */ .word	0x00000000
glabel actorCutsceneStartMethod
/* 286591 0x801BD8BC */ .word	0x00000000
glabel actorCutscenesGlobalCtxt
/* 286592 0x801BD8C0 */ .word	0x00000000
glabel actorCutsceneReturnCamera
/* 286593 0x801BD8C4 */ .short	0x0000
glabel D_801BD8C6
/* 286593 0x801BD8C4 */ .short	0x0000
/* 286594 0x801BD8C8 */ .word	0x00000000
/* 286595 0x801BD8CC */ .word	0x00000000
