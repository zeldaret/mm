#ifndef Z_EN_POH_H
#define Z_EN_POH_H

#include "global.h"

struct EnPoh;

typedef void (*EnPohActionFunc)(struct EnPoh*, GlobalContext*);

typedef struct EnPoh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnPohActionFunc actionFunc;
    /* 0x018C */ u8 unk_18C;
    /* 0x018D */ u8 unk_18D;
    /* 0x018E */ s16 unk_18E;
    /* 0x0190 */ s16 unk_190;
    /* 0x0192 */ s16 unk_192;
    /* 0x0194 */ u8 unk_194;
    /* 0x0195 */ u8 unk_195;
    /* 0x0196 */ u8 unk_196;
    /* 0x0197 */ u8 unk_197;
    /* 0x0198 */ u8 unk_198;
    /* 0x0199 */ u8 unk_199;
    /* 0x019A */ u8 unk_19A;
    /* 0x019B */ u8 unk_19B;
    /* 0x019C */ Vec3s jointTable[21];
    /* 0x021A */ Vec3s morphTable[21];
    /* 0x0298 */ f32 drawDmgEffAlpha;
    /* 0x029C */ f32 drawDmgEffScale;
    /* 0x02A0 */ Vec3f limbPos[10];
    /* 0x0318 */ LightNode* lightNode;
    /* 0x031C */ LightInfo lightInfo;
    /* 0x032C */ ColliderCylinder colliderCylinder;
    /* 0x0378 */ ColliderJntSph colliderSph;
    /* 0x0398 */ ColliderJntSphElement colliderSphElements[1];
    /* 0x03D8 */ MtxF unk_3D8;
} EnPoh; // size = 0x418

extern const ActorInit En_Poh_InitVars;

#endif // Z_EN_POH_H
