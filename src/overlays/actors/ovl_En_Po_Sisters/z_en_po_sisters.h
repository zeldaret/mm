#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, GlobalContext*);

#define ENPOSISTERS_GET_300(thisx) (((thisx)->params >> 8) & 3)
#define ENPOSISTERS_GET_C00(thisx) (((thisx)->params >> 0xA) & 3)
#define ENPOSISTERS_GET_1000(thisx) ((thisx)->params & 0x1000)

typedef struct EnPoSisters {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnPoSistersActionFunc actionFunc;
    /* 0x018C */ u8 unk_18C;
    /* 0x018D */ u8 unk_18D;
    /* 0x018E */ u8 unk_18E;
    /* 0x018F */ u8 unk_18F;
    /* 0x0190 */ u8 unk_190;
    /* 0x0191 */ u8 unk_191;
    /* 0x0192 */ s16 unk_192;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ Vec3s jointTable[12];
    /* 0x01DE */ Vec3s morphTable[12];
    /* 0x0226 */ u8 unk_226;
    /* 0x0227 */ u8 unk_227;
    /* 0x0228 */ u8 unk_228;
    /* 0x0229 */ u8 unk_229;
    /* 0x022C */ Vec3f unk_22C[8];
    /* 0x028C */ Vec3f limbPos[8];
    /* 0x02EC */ f32 unk_2EC;
    /* 0x02F0 */ f32 drawDmgEffAlpha;
    /* 0x02F4 */ f32 drawDmgEffScale;
    /* 0x02F8 */ LightNode* lightNode;
    /* 0x02FC */ LightInfo lightInfo;
    /* 0x030C */ ColliderCylinder collider;
    /* 0x0358 */ MtxF unk_358;
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
