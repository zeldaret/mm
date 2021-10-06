#ifndef Z_DM_STK_H
#define Z_DM_STK_H

#include "global.h"

struct DmStk;

typedef void (*DmStkActionFunc)(struct DmStk*, GlobalContext*);

typedef struct DmStk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ char unk_188[0x108];
    /* 0x0290 */ DmStkActionFunc actionFunc;
    /* 0x0294 */ ColliderCylinder collider;
    /* 0x02E0 */ s16 unk_2E0;
    /* 0x02E4 */ s32 unk_2E4;
    /* 0x02E8 */ u32 unk_2E8;
    /* 0x02EC */ u32 unk_2EC;
    /* 0x02F0 */ u32 unk_2F0;
    /* 0x02F4 */ s32 unk_2F4;
    /* 0x02F8 */ s32 unk_2F8;
    /* 0x02FC */ s32 unk_2FC;
    /* 0x0300 */ f32 unk_300;
    /* 0x0304 */ Vec3f unk_304;
    /* 0x0310 */ Vec3f unk_310;
    /* 0x031C */ char unk31C[0xC];
    /* 0x0328 */ u16 unk_328;
    /* 0x032A */ u16 unk_32A;
    /* 0x032C */ u8 unk_32C;
    /* 0x032D */ u8 unk_32D;
    /* 0x032E */ u8 unk_32E;
    /* 0x032F */ u8 unk_32F;
    /* 0x0330 */ s32 unk_330;
    /* 0x0334 */ u8 unk_334;
    /* 0x0335 */ u8 unk_335;
    /* 0x0336 */ s8 unk_336;
    /* 0x0337 */ s8 unk_337;
    /* 0x0338 */ s8 unk_338;
    /* 0x0339 */ u8 unk_339;
    /* 0x033A */ u8 unk_33A;
    /* 0x033B */ u8 unk_33B;
} DmStk; // size = 0x33C

extern const ActorInit Dm_Stk_InitVars;

#endif // Z_DM_STK_H
