.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Warp_Uzu_InitVars
/* 000200 0x80A664A0 */ .word	0x01780600
/* 000201 0x80A664A4 */ .word	0x00000019
/* 000202 0x80A664A8 */ .word	0x01860000
/* 000203 0x80A664AC */ .word	0x00000194
/* 000204 0x80A664B0 */ .word	EnWarpUzu_Init
/* 000205 0x80A664B4 */ .word	EnWarpUzu_Destroy
/* 000206 0x80A664B8 */ .word	EnWarpUzu_Update
/* 000207 0x80A664BC */ .word	EnWarpUzu_Draw
glabel D_80A664C0
/* 000208 0x80A664C0 */ .word	0x00001939
/* 000209 0x80A664C4 */ .word	0x10010000
/* 000210 0x80A664C8 */ .word	0x01000000
/* 000211 0x80A664CC */ .word	0x00000000
/* 000212 0x80A664D0 */ .word	0x00000000
/* 000213 0x80A664D4 */ .word	0xF7CFFFFF
/* 000214 0x80A664D8 */ .word	0x00000000
/* 000215 0x80A664DC */ .word	0x00010100
/* 000216 0x80A664E0 */ .word	0x0019002B
/* 000217 0x80A664E4 */ .word	0xFFEC0000
/* 000218 0x80A664E8 */ .word	0x00000000
glabel D_80A664EC
/* 000219 0x80A664EC */ .word	0xB10005DC
/* 000220 0x80A664F0 */ .word	0xB104044C
/* 000221 0x80A664F4 */ .word	0xB0FC03E8
/* 000222 0x80A664F8 */ .word	0x48580064
glabel D_80A664FC
/* 000223 0x80A664FC */ .word	0x00000000
/* 000224 0x80A66500 */ .word	0x42540000
/* 000225 0x80A66504 */ .word	0xC1E80000
/* 000226 0x80A66508 */ .word	0x00000000
/* 000227 0x80A6650C */ .word	0x00000000
