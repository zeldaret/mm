#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, PlayState*);

#define ENPOSISTERS_GET_300(thisx) (((thisx)->params >> 8) & 3)
#define ENPOSISTERS_GET_C00(thisx) (((thisx)->params >> 0xA) & 3)
#define ENPOSISTERS_GET_1000(thisx) ((thisx)->params & 0x1000)

typedef struct EnPoSisters {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnPoSistersActionFunc actionFunc;
    /* 0x18C */ u8 unk_18C;
    /* 0x18D */ u8 unk_18D;
    /* 0x18E */ u8 unk_18E;
    /* 0x18F */ u8 unk_18F;
    /* 0x190 */ u8 unk_190;
    /* 0x191 */ u8 unk_191;
    /* 0x192 */ s16 unk_192;
    /* 0x194 */ s16 unk_194;
    /* 0x196 */ Vec3s jointTable[12];
    /* 0x1DE */ Vec3s morphTable[12];
    /* 0x226 */ u8 unk_226;
    /* 0x227 */ u8 unk_227;
    /* 0x228 */ u8 unk_228;
    /* 0x229 */ u8 unk_229;
    /* 0x22C */ Vec3f unk_22C[8];
    /* 0x28C */ Vec3f limbPos[8];
    /* 0x2EC */ f32 unk_2EC;
    /* 0x2F0 */ f32 drawDmgEffAlpha;
    /* 0x2F4 */ f32 drawDmgEffScale;
    /* 0x2F8 */ LightNode* lightNode;
    /* 0x2FC */ LightInfo lightInfo;
    /* 0x30C */ ColliderCylinder collider;
    /* 0x358 */ MtxF unk_358;
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
