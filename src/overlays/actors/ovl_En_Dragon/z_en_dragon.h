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
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ char unk_254[0x48];
    /* 0x29C */ Vec3f unk_29C;
    /* 0x2A8 */ char unk_2A8[0x6];
    /* 0x2AE */ s16 unk_2AE;
    /* 0x2B0 */ char unk_2B0[0x2];
    /* 0x2B2 */ s16 unk_2B2;
    /* 0x2B4 */ s16 unk_2B4;
    /* 0x2B6 */ s16 unk_2B6;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ char unk_2BC[0x2];
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ char unk_2C0[0xA];
    /* 0x2CA */ s16 unk_2CA;
    /* 0x2CC */ s16 unk_2CC;
    /* 0x2CE */ char unk_2CE[0x2];
    /* 0x2D0 */ f32 unk_2D0;
    /* 0x2D4 */ f32 unk_2D4;
    /* 0x2D8 */ char unk_2D8[0x4];
    /* 0x2DC */ ColliderJntSph unk_2DC;
    /* 0x2FC */ ColliderJntSphElement unk_2FC[8];
} EnDragon; // size = 0x4FC

extern const ActorInit En_Dragon_InitVars;

#endif // Z_EN_DRAGON_H
