.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objJgameLightOverlayInfo
/* 000920 0x80C16150 */ .word	0x000008B0
/* 000921 0x80C16154 */ .word	0x00000590
/* 000922 0x80C16158 */ .word	0x00000020
/* 000923 0x80C1615C */ .word	0x00000000
/* 000924 0x80C16160 */ .word	0x0000001D
glabel objJgameLightOverlayRelocations
/* 000925 0x80C16164 */ .word	0x4500005C
/* 000926 0x80C16168 */ .word	0x46000064
/* 000927 0x80C1616C */ .word	0x450001E0
/* 000928 0x80C16170 */ .word	0x460001E4
/* 000929 0x80C16174 */ .word	0x45000200
/* 000930 0x80C16178 */ .word	0x46000204
/* 000931 0x80C1617C */ .word	0x45000280
/* 000932 0x80C16180 */ .word	0x46000284
/* 000933 0x80C16184 */ .word	0x450002B0
/* 000934 0x80C16188 */ .word	0x460002B4
/* 000935 0x80C1618C */ .word	0x45000320
/* 000936 0x80C16190 */ .word	0x46000324
/* 000937 0x80C16194 */ .word	0x440004FC
/* 000938 0x80C16198 */ .word	0x44000508
/* 000939 0x80C1619C */ .word	0x44000514
/* 000940 0x80C161A0 */ .word	0x4500067C
/* 000941 0x80C161A4 */ .word	0x46000680
/* 000942 0x80C161A8 */ .word	0x450006AC
/* 000943 0x80C161AC */ .word	0x460006B0
/* 000944 0x80C161B0 */ .word	0x450006FC
/* 000945 0x80C161B4 */ .word	0x46000700
/* 000946 0x80C161B8 */ .word	0x82000010
/* 000947 0x80C161BC */ .word	0x82000014
/* 000948 0x80C161C0 */ .word	0x82000018
/* 000949 0x80C161C4 */ .word	0x8200001C
/* 000950 0x80C161C8 */ .word	0x8200049C
/* 000951 0x80C161CC */ .word	0x820004F4
/* 000952 0x80C161D0 */ .word	0x8200051C
/* 000953 0x80C161D4 */ .word	0x82000574
/* 000954 0x80C161D8 */ .word	0x00000000
glabel objJgameLightOverlayInfoOffset
/* 000955 0x80C161DC */ .word	0x00000090
