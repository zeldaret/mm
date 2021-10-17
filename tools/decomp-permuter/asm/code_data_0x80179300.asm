.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D1570
/* 306860 0x801D1570 */ .word	0x3F800000
/* 306861 0x801D1574 */ .word	0x3F800000
/* 306862 0x801D1578 */ .word	0x40000000
/* 306863 0x801D157C */ .word	0x40C00000
/* 306864 0x801D1580 */ .word	0x41C00000
/* 306865 0x801D1584 */ .word	0x42F00000
/* 306866 0x801D1588 */ .word	0x44340000
/* 306867 0x801D158C */ .word	0x459D8000
/* 306868 0x801D1590 */ .word	0x471D8000
/* 306869 0x801D1594 */ .word	0x48B13000
/* 306870 0x801D1598 */ .word	0x4A5D7C00
/* 306871 0x801D159C */ .word	0x4C184540
/* 306872 0x801D15A0 */ .word	0x4DE467E0
/* 306873 0x801D15A4 */ .word	0x00000000
/* 306874 0x801D15A8 */ .word	0x00000000
/* 306875 0x801D15AC */ .word	0x00000000
