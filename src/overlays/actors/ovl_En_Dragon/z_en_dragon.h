#ifndef Z_EN_DRAGON_H
#define Z_EN_DRAGON_H

#include "global.h"

struct EnDragon;

typedef void (*EnDragonActionFunc)(struct EnDragon*, GlobalContext*);

typedef struct EnDragon {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ EnDragonActionFunc actionFunc;
    /* 0x24C */ char unk_24C[0x4];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ char unk_254[0x66];
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ char unk_2BC[0x18];
    /* 0x2D4 */ f32 unk_2D4;
    /* 0x2D8 */ char unk_2D8[0x4];
    /* 0x2DC */ ColliderJntSph unk_2DC;
    /* 0x2FC */ ColliderJntSphElement unk_2FC[8];
} EnDragon; // size = 0x4FC

extern const ActorInit En_Dragon_InitVars;

#endif // Z_EN_DRAGON_H
