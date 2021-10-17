.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgF40FliftOverlayInfo
/* 000196 0x808D7860 */ .word	0x000002C0
/* 000197 0x808D7864 */ .word	0x00000030
/* 000198 0x808D7868 */ .word	0x00000020
/* 000199 0x808D786C */ .word	0x00000000
/* 000200 0x808D7870 */ .word	0x00000016
glabel bgF40FliftOverlayRelocations
/* 000201 0x808D7874 */ .word	0x45000014
/* 000202 0x808D7878 */ .word	0x46000018
/* 000203 0x808D787C */ .word	0x45000044
/* 000204 0x808D7880 */ .word	0x4600004C
/* 000205 0x808D7884 */ .word	0x450000F0
/* 000206 0x808D7888 */ .word	0x460000F8
/* 000207 0x808D788C */ .word	0x45000134
/* 000208 0x808D7890 */ .word	0x46000138
/* 000209 0x808D7894 */ .word	0x4500016C
/* 000210 0x808D7898 */ .word	0x46000170
/* 000211 0x808D789C */ .word	0x4500018C
/* 000212 0x808D78A0 */ .word	0x46000190
/* 000213 0x808D78A4 */ .word	0x450001E8
/* 000214 0x808D78A8 */ .word	0x460001F0
/* 000215 0x808D78AC */ .word	0x45000214
/* 000216 0x808D78B0 */ .word	0x46000218
/* 000217 0x808D78B4 */ .word	0x450001D4
/* 000218 0x808D78B8 */ .word	0x46000248
/* 000219 0x808D78BC */ .word	0x82000010
/* 000220 0x808D78C0 */ .word	0x82000014
/* 000221 0x808D78C4 */ .word	0x82000018
/* 000222 0x808D78C8 */ .word	0x8200001C
glabel bgF40FliftOverlayInfoOffset
/* 000223 0x808D78CC */ .word	0x00000070
