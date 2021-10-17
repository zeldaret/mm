.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097A3E0
/* 000228 0x8097A3E0 */ .word	0x0000000A
/* 000229 0x8097A3E4 */ .word	func_8097A050
glabel D_8097A3E8
/* 000230 0x8097A3E8 */ .word	0x040378F0
/* 000231 0x8097A3EC */ .word	0x04037DF0
/* 000232 0x8097A3F0 */ .word	0x040382F0
/* 000233 0x8097A3F4 */ .word	0x040387F0
/* 000234 0x8097A3F8 */ .word	0x04038CF0
/* 000235 0x8097A3FC */ .word	0x040391F0
/* 000236 0x8097A400 */ .word	0x040396F0
/* 000237 0x8097A404 */ .word	0x04039BF0
/* 000238 0x8097A408 */ .word	0x00000000
/* 000239 0x8097A40C */ .word	0x00000000
glabel D_8097A410
/* 000240 0x8097A410 */ .word	0x3B03126F
/* 000241 0x8097A414 */ .word	0x00000000
/* 000242 0x8097A418 */ .word	0x00000000
/* 000243 0x8097A41C */ .word	0x00000000
glabel effectSsGSplashOverlayInfo
/* 000244 0x8097A420 */ .word	0x00000390
/* 000245 0x8097A424 */ .word	0x00000030
/* 000246 0x8097A428 */ .word	0x00000010
/* 000247 0x8097A42C */ .word	0x00000000
/* 000248 0x8097A430 */ .word	0x0000000D
glabel effectSsGSplashOverlayRelocations
/* 000249 0x8097A434 */ .word	0x4500004C
/* 000250 0x8097A438 */ .word	0x46000054
/* 000251 0x8097A43C */ .word	0x45000050
/* 000252 0x8097A440 */ .word	0x46000058
/* 000253 0x8097A444 */ .word	0x450001D0
/* 000254 0x8097A448 */ .word	0x4600022C
/* 000255 0x8097A44C */ .word	0x450001E0
/* 000256 0x8097A450 */ .word	0x4600026C
/* 000257 0x8097A454 */ .word	0x450001EC
/* 000258 0x8097A458 */ .word	0x460002AC
/* 000259 0x8097A45C */ .word	0x450002FC
/* 000260 0x8097A460 */ .word	0x46000324
/* 000261 0x8097A464 */ .word	0x82000004
/* 000262 0x8097A468 */ .word	0x00000000
glabel effectSsGSplashOverlayInfoOffset
/* 000263 0x8097A46C */ .word	0x00000050
