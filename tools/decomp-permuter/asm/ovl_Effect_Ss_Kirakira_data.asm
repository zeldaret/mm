.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel effectSparkleOverlayInfo
/* 000368 0x80977FC0 */ .word	0x00000001
/* 000369 0x80977FC4 */ .word	EffectSparkle_Init
/* 000370 0x80977FC8 */ .word	0x00000000
/* 000371 0x80977FCC */ .word	0x00000000
glabel D_80977FD0
/* 000372 0x80977FD0 */ .word	0x461C4000
glabel D_80977FD4
/* 000373 0x80977FD4 */ .word	0x3ECCCCCD
glabel D_80977FD8
/* 000374 0x80977FD8 */ .word	0x3E4CCCCD
glabel D_80977FDC
/* 000375 0x80977FDC */ .word	0x3ECCCCCD
glabel D_80977FE0
/* 000376 0x80977FE0 */ .word	0x3E4CCCCD
glabel D_80977FE4
/* 000377 0x80977FE4 */ .word	0x3F733333
glabel D_80977FE8
/* 000378 0x80977FE8 */ .word	0x3E4CCCCD
glabel D_80977FEC
/* 000379 0x80977FEC */ .word	0x3E4CCCCD
glabel effectSsKirakiraOverlayInfo
/* 000380 0x80977FF0 */ .word	0x000005C0
/* 000381 0x80977FF4 */ .word	0x00000010
/* 000382 0x80977FF8 */ .word	0x00000020
/* 000383 0x80977FFC */ .word	0x00000000
/* 000384 0x80978000 */ .word	0x00000019
glabel effectSsKirakiraOverlayRelocations
/* 000385 0x80978004 */ .word	0x45000010
/* 000386 0x80978008 */ .word	0x46000020
/* 000387 0x8097800C */ .word	0x450000A4
/* 000388 0x80978010 */ .word	0x460000B0
/* 000389 0x80978014 */ .word	0x450000A0
/* 000390 0x80978018 */ .word	0x460000AC
/* 000391 0x8097801C */ .word	0x450000EC
/* 000392 0x80978020 */ .word	0x460000F0
/* 000393 0x80978024 */ .word	0x4500017C
/* 000394 0x80978028 */ .word	0x46000180
/* 000395 0x8097802C */ .word	0x450003CC
/* 000396 0x80978030 */ .word	0x460003D0
/* 000397 0x80978034 */ .word	0x450003D4
/* 000398 0x80978038 */ .word	0x460003D8
/* 000399 0x8097803C */ .word	0x450003F0
/* 000400 0x80978040 */ .word	0x460003F4
/* 000401 0x80978044 */ .word	0x450003FC
/* 000402 0x80978048 */ .word	0x4600040C
/* 000403 0x8097804C */ .word	0x45000470
/* 000404 0x80978050 */ .word	0x46000474
/* 000405 0x80978054 */ .word	0x4500048C
/* 000406 0x80978058 */ .word	0x460004AC
/* 000407 0x8097805C */ .word	0x450004B4
/* 000408 0x80978060 */ .word	0x460004C0
/* 000409 0x80978064 */ .word	0x82000004
/* 000410 0x80978068 */ .word	0x00000000
glabel effectSsKirakiraOverlayInfoOffset
/* 000411 0x8097806C */ .word	0x00000080
