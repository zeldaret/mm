#ifndef Z_EN_MKK_H
#define Z_EN_MKK_H

#include "global.h"

struct EnMkk;

typedef void (*EnMkkActionFunc)(struct EnMkk*, PlayState*);

typedef struct EnMkk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnMkkActionFunc actionFunc;
    /* 0x148 */ u8 unk148;
    /* 0x149 */ u8 unk149;
    /* 0x14A */ u8 unk14A;
    /* 0x14B */ u8 unk14B;
    /* 0x14C */ u8 unk14C;
    /* 0x14D */ char pad14D[1];
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ Vec3f unk154;
    /* 0x160 */ Vec3f unk160;
    /* 0x16C */ f32 unk16C;
    /* 0x170 */ f32 unk170;
    /* 0x174 */ char pad174[4];
    /* 0x178 */ f32 unk178;
    /* 0x17C */ ColliderSphere unk17C;
} EnMkk; // size = 0x1D4

struct _struct_D_80A4F7A4_0x10 {
    /* 0x00 */ s32 unk0;                            /* inferred */
    /* 0x04 */ s32 unk4;                            /* inferred */
    /* 0x08 */ Mtx *unk8;                           /* inferred */
    /* 0x0C */ s32 unkC;                            /* inferred */
};

extern const ActorInit En_Mkk_InitVars;

#endif // Z_EN_MKK_H
