#ifndef Z_EN_GUARD_NUTS_H
#define Z_EN_GUARD_NUTS_H

#include "global.h"
#include "objects/object_dnk/object_dnk.h"

struct EnGuardNuts;

typedef void (*EnGuardNutsActionFunc)(struct EnGuardNuts*, GlobalContext*);

typedef struct EnGuardNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_DNK_LIMB_MAX];
    /* 0x1CA */ Vec3s morphTable[OBJECT_DNK_LIMB_MAX];
    /* 0x20C */ EnGuardNutsActionFunc actionFunc;
    /* 0x210 */ s16 unk210;
    /* 0x212 */ s16 unk212;
    /* 0x214 */ s16 unk214;
    /* 0x218 */ s32 animIndex;
    /* 0x21C */ s16 unk21C;
    /* 0x21E */ s16 unk21E;
    /* 0x220 */ s32 textId;
    /* 0x224 */ u8 unk224;
    /* 0x228 */ Vec3f unk228;
    /* 0x234 */ s16 unk234;
    /* 0x236 */ s16 unk236;
    /* 0x238 */ s16 unk238;
    /* 0x23A */ s16 unk23A;
    /* 0x23C */ s16 unk23C;
    /* 0x240 */ f32 animeFrameCount;
    /* 0x244 */ ColliderCylinder collider;
} EnGuardNuts; // size = 0x290

extern const ActorInit En_Guard_Nuts_InitVars;

#endif // Z_EN_GUARD_NUTS_H
