#ifndef Z_EN_SNOWMAN_H
#define Z_EN_SNOWMAN_H

#include "global.h"

struct EnSnowman;

typedef void (*EnSnowmanActionFunc)(struct EnSnowman*, GlobalContext*);

typedef struct EnSnowman {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime bodySkelAnime;
    /* 0x188 */ SkelAnime snowPileSkelAnime;
    /* 0x1CC */ Vec3s bodyJointTable[12];
    /* 0x214 */ Vec3s bodyMorphTable[12];
    /* 0x25C */ Vec3s snowPileJointTable[3];
    /* 0x26E */ Vec3s snowPileMorphTable[3];
    /* 0x280 */ EnSnowmanActionFunc actionFunc;
    /* 0x284 */ char unk_284[0x6];
    /* 0x28A */ s8 unk_28A;
    /* 0x28B */ char unk_28B[0x1];
    /* 0x28C */ s16 unk_28C;
    /* 0x28E */ char unk_28E[0x6];
    /* 0x294 */ f32 unk_294;
    /* 0x298 */ char unk_298[0x4];
    /* 0x29C */ f32 unk_29C;
    /* 0x2A0 */ char unk_2A0[0x8C];
    /* 0x32C */ ColliderCylinder unk_32C;
} EnSnowman; // size = 0x378

extern const ActorInit En_Snowman_InitVars;

#endif // Z_EN_SNOWMAN_H
