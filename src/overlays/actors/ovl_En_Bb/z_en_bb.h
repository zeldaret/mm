#ifndef Z_EN_BB_H
#define Z_EN_BB_H

#include "global.h"
#include "objects/object_bb/object_bb.h"

#define EN_BB_GET_RIGHT_SHIFT_8_PARAM(thisx) (((thisx)->params >> 8) & 0xFF)

struct EnBb;

typedef void (*EnBbActionFunc)(struct EnBb*, GlobalContext*);

typedef struct EnBb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[BUBBLE_LIMB_MAX];
    /* 0x1E8 */ Vec3s morphTable[BUBBLE_LIMB_MAX];
    /* 0x248 */ EnBbActionFunc actionFunc;
    /* 0x24C */ s8 unk_24C;
    /* 0x24D */ u8 drawDmgEffType;
    /* 0x24E */ UNK_TYPE1 unk_24E[0x2];
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ s16 unk_252;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ f32 unk_258;
    /* 0x25C */ f32 unk_25C;
    /* 0x260 */ f32 unk_260;
    /* 0x264 */ f32 unk_264;
    /* 0x268 */ f32 unk_268;
    /* 0x26C */ f32 drawDmgEffAlpha;
    /* 0x270 */ f32 drawDmgEffScale;
    /* 0x274 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x278 */ Vec3f limbPos[5];
    /* 0x2B4 */ Vec3f unk_2B4[5];
    /* 0x2F0 */ Gfx* unk_2F0;
    /* 0x2F4 */ ColliderSphere collider;
} EnBb; // size = 0x34C

extern const ActorInit En_Bb_InitVars;

#endif // Z_EN_BB_H
