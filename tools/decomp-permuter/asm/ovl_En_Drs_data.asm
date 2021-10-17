.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Drs_InitVars
/* 000204 0x80C1E5C0 */ .word	0x02A10600
/* 000205 0x80C1E5C4 */ .word	0x00000000
/* 000206 0x80C1E5C8 */ .word	0x00180000
/* 000207 0x80C1E5CC */ .word	0x0000020C
/* 000208 0x80C1E5D0 */ .word	EnDrs_Init
/* 000209 0x80C1E5D4 */ .word	EnDrs_Destroy
/* 000210 0x80C1E5D8 */ .word	EnDrs_Update
/* 000211 0x80C1E5DC */ .word	0x00000000
glabel D_80C1E5E0
/* 000212 0x80C1E5E0 */ .word	0x01000039
/* 000213 0x80C1E5E4 */ .word	0x10010000
/* 000214 0x80C1E5E8 */ .word	0x01000000
/* 000215 0x80C1E5EC */ .word	0x00000000
/* 000216 0x80C1E5F0 */ .word	0x00000000
/* 000217 0x80C1E5F4 */ .word	0x00000000
/* 000218 0x80C1E5F8 */ .word	0x00000000
/* 000219 0x80C1E5FC */ .word	0x00000100
/* 000220 0x80C1E600 */ .word	0x0010003E
/* 000221 0x80C1E604 */ .word	0x00000000
/* 000222 0x80C1E608 */ .word	0x00000000
glabel D_80C1E60C
/* 000223 0x80C1E60C */ .word	0x00000000
/* 000224 0x80C1E610 */ .word	0x00000000
/* 000225 0x80C1E614 */ .word	0xFF000000
glabel D_80C1E618
/* 000226 0x80C1E618 */ .word	0x0600001C
/* 000227 0x80C1E61C */ .word	0x3F800000
/* 000228 0x80C1E620 */ .word	0x0000FFFF
/* 000229 0x80C1E624 */ .word	0x00000000
/* 000230 0x80C1E628 */ .word	0x00000000
/* 000231 0x80C1E62C */ .word	0x00000000
