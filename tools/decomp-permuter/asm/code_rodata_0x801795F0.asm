.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel Math3D_Normalize_min_length
/* 321948 0x801E0130 */ .word	0x3C03126F
glabel D_801E0134
/* 321949 0x801E0134 */ .word	0x3C03126F
glabel D_801E0138
/* 321950 0x801E0138 */ .word	0x3C03126F
glabel D_801E013C
/* 321951 0x801E013C */ .word	0x3C03126F
glabel D_801E0140
/* 321952 0x801E0140 */ .word	0x3C03126F
glabel Math3D_AngleBetweenVectors_min_length
/* 321953 0x801E0144 */ .word	0x3C03126F
glabel D_801E0148
/* 321954 0x801E0148 */ .word	0x46FFFE00
glabel D_801E014C
/* 321955 0x801E014C */ .word	0x46FFFE00
glabel Math3D_UnitNormalVector_min_length
/* 321956 0x801E0150 */ .word	0x3C03126F
glabel Math3D_NormalizedDistanceFromPlane_min_length
/* 321957 0x801E0154 */ .word	0x3C03126F
glabel D_801E0158
/* 321958 0x801E0158 */ .word	0x3F19999A
glabel D_801E015C
/* 321959 0x801E015C */ .word	0x3C03126F
glabel D_801E0160
/* 321960 0x801E0160 */ .word	0x3C03126F
glabel D_801E0164
/* 321961 0x801E0164 */ .word	0x3C03126F
glabel D_801E0168
/* 321962 0x801E0168 */ .word	0x3C03126F
glabel D_801E016C
/* 321963 0x801E016C */ .word	0x3C03126F
glabel D_801E0170
/* 321964 0x801E0170 */ .word	0x3C03126F
glabel D_801E0174
/* 321965 0x801E0174 */ .word	0x3C03126F
glabel D_801E0178
/* 321966 0x801E0178 */ .word	0x3C03126F
glabel D_801E017C
/* 321967 0x801E017C */ .word	0x3C03126F
glabel D_801E0180
/* 321968 0x801E0180 */ .word	0x3C03126F
glabel D_801E0184
/* 321969 0x801E0184 */ .word	0x3C03126F
glabel D_801E0188
/* 321970 0x801E0188 */ .word	0x3C03126F
glabel D_801E018C
/* 321971 0x801E018C */ .word	0x3C03126F
glabel D_801E0190
/* 321972 0x801E0190 */ .word	0x3C03126F
glabel D_801E0194
/* 321973 0x801E0194 */ .word	0x3C03126F
glabel D_801E0198
/* 321974 0x801E0198 */ .word	0x3C03126F
glabel D_801E019C
/* 321975 0x801E019C */ .word	0x3C03126F
glabel D_801E01A0
/* 321976 0x801E01A0 */ .word	0x3C03126F
glabel D_801E01A4
/* 321977 0x801E01A4 */ .word	0x3C03126F
glabel D_801E01A8
/* 321978 0x801E01A8 */ .word	0x3C03126F
glabel D_801E01AC
/* 321979 0x801E01AC */ .word	0x3C03126F
glabel D_801E01B0
/* 321980 0x801E01B0 */ .word	0x3C03126F
glabel D_801E01B4
/* 321981 0x801E01B4 */ .word	0x3C03126F
glabel D_801E01B8
/* 321982 0x801E01B8 */ .word	0x3C03126F
glabel D_801E01BC
/* 321983 0x801E01BC */ .word	0x7E967699
glabel D_801E01C0
/* 321984 0x801E01C0 */ .word	0x7E967699
glabel D_801E01C4
/* 321985 0x801E01C4 */ .word	0x3C03126F
glabel Math3D_ColSphereSphereIntersectAndDistance_min_intersect
/* 321986 0x801E01C8 */ .word	0x3C03126F
glabel D_801E01CC
/* 321987 0x801E01CC */ .word	0x3C03126F
glabel D_801E01D0
/* 321988 0x801E01D0 */ .word	0x3C03126F
glabel D_801E01D4
/* 321989 0x801E01D4 */ .word	0x46FFFE00
/* 321990 0x801E01D8 */ .word	0x00000000
/* 321991 0x801E01DC */ .word	0x00000000
