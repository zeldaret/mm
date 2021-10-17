.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800981C0
/* 024664 0x800981C0 */ .word	0x3F3F0000
glabel dmamgrString800981C4
/* 024665 0x800981C4 */ .word	0x2E2E2F7A
/* 024666 0x800981C8 */ .word	0x5F737464
/* 024667 0x800981CC */ .word	0x5F646D61
/* 024668 0x800981D0 */ .word	0x2E630000
glabel dmamgrString800981D4
/* 024669 0x800981D4 */ .word	0x2E2E2F7A
/* 024670 0x800981D8 */ .word	0x5F737464
/* 024671 0x800981DC */ .word	0x5F646D61
/* 024672 0x800981E0 */ .word	0x2E630000
glabel dmamgrString800981E4
/* 024673 0x800981E4 */ .word	0x2E2E2F7A
/* 024674 0x800981E8 */ .word	0x5F737464
/* 024675 0x800981EC */ .word	0x5F646D61
/* 024676 0x800981F0 */ .word	0x2E630000
glabel dmamgrString800981F4
/* 024677 0x800981F4 */ .word	0x2E2E2F7A
/* 024678 0x800981F8 */ .word	0x5F737464
/* 024679 0x800981FC */ .word	0x5F646D61
/* 024680 0x80098200 */ .word	0x2E630000
glabel dmamgrThreadName
/* 024681 0x80098204 */ .word	0x646D616D
/* 024682 0x80098208 */ .word	0x67720000
/* 024683 0x8009820C */ .word	0x00000000
