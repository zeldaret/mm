#ifndef Z_EN_BBFALL_H
#define Z_EN_BBFALL_H

#include "global.h"

struct EnBbfall;

typedef void (*EnBbfallActionFunc)(struct EnBbfall*, GlobalContext*);

typedef struct EnBbfall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ EnBbfallActionFunc actionFunc;
    /* 0x24C */ u8 unk_24C;
    /* 0x24D */ s8 unk_24D;
    /* 0x24E */ s8 unk_24E;
    /* 0x24F */ u8 drawDmgEffType;
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ char unk_252[0x2];
    /* 0x254 */ f32 unk_254;
    /* 0x258 */ f32 unk_258;
    /* 0x25C */ f32 drawDmgEffAlpha;
    /* 0x260 */ f32 drawDmgEffScale;
    /* 0x264 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x268 */ Vec3f unk_268[6];
    /* 0x2B0 */ Vec3f bodyPartsPos[5];
    /* 0x2EC */ char unk_2EC[0x3C];
    /* 0x328 */ Gfx* unk_328;
    /* 0x32C */ char unk_32C[0x58];
    /* 0x384 */ ColliderJntSph collider;
    /* 0x3A4 */ ColliderJntSphElement colliderElements[3];
} EnBbfall; // size = 0x464

extern const ActorInit En_Bbfall_InitVars;

#endif // Z_EN_BBFALL_H
