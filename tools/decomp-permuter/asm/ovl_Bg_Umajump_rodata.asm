.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgUmajumpOverlayInfo
/* 000572 0x8091A820 */ .word	0x000008C0
/* 000573 0x8091A824 */ .word	0x00000030
/* 000574 0x8091A828 */ .word	0x00000000
/* 000575 0x8091A82C */ .word	0x00000000
/* 000576 0x8091A830 */ .word	0x00000017
glabel bgUmajumpOverlayRelocations
/* 000577 0x8091A834 */ .word	0x45000158
/* 000578 0x8091A838 */ .word	0x46000164
/* 000579 0x8091A83C */ .word	0x450001C8
/* 000580 0x8091A840 */ .word	0x460001D4
/* 000581 0x8091A844 */ .word	0x45000208
/* 000582 0x8091A848 */ .word	0x4600020C
/* 000583 0x8091A84C */ .word	0x450002A4
/* 000584 0x8091A850 */ .word	0x460002AC
/* 000585 0x8091A854 */ .word	0x450002B4
/* 000586 0x8091A858 */ .word	0x460002B8
/* 000587 0x8091A85C */ .word	0x4500040C
/* 000588 0x8091A860 */ .word	0x46000414
/* 000589 0x8091A864 */ .word	0x4500050C
/* 000590 0x8091A868 */ .word	0x46000514
/* 000591 0x8091A86C */ .word	0x45000510
/* 000592 0x8091A870 */ .word	0x46000518
/* 000593 0x8091A874 */ .word	0x45000534
/* 000594 0x8091A878 */ .word	0x46000538
/* 000595 0x8091A87C */ .word	0x45000618
/* 000596 0x8091A880 */ .word	0x4600061C
/* 000597 0x8091A884 */ .word	0x82000010
/* 000598 0x8091A888 */ .word	0x82000014
/* 000599 0x8091A88C */ .word	0x82000018
/* 000600 0x8091A890 */ .word	0x00000000
/* 000601 0x8091A894 */ .word	0x00000000
/* 000602 0x8091A898 */ .word	0x00000000
glabel bgUmajumpOverlayInfoOffset
/* 000603 0x8091A89C */ .word	0x00000080
