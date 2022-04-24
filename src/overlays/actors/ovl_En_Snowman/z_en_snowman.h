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
    /* 0x284 */ char unk_284[0x4];
    /* 0x288 */ u8 unk_288;
    /* 0x299 */ s8 unk_289;
    /* 0x28A */ s8 unk_28A;
    /* 0x28B */ u8 drawDmgEffType;
    /* 0x28C */ s16 unk_28C;
    /* 0x28E */ s16 unk_28E;
    /* 0x290 */ s16 unk_290;
    /* 0x292 */ char unk_292[0x2];
    /* 0x294 */ f32 unk_294;
    /* 0x298 */ f32 unk_298;
    /* 0x29C */ f32 unk_29C;
    /* 0x2A0 */ f32 drawDmgEffAlpha;
    /* 0x2A4 */ f32 unk_2A4;
    /* 0x2A8 */ Vec3f unk_2A8;
    /* 0x2B4 */ Vec3f unk_2B4;
    /* 0x2C0 */ Vec3f limbPos[9];
    /* 0x32C */ ColliderCylinder unk_32C;
} EnSnowman; // size = 0x378

extern const ActorInit En_Snowman_InitVars;

#endif // Z_EN_SNOWMAN_H
