#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, GlobalContext*);

#define ENPOSISTERS_GET_TYPE(thisx) (((thisx)->params >> 8) & 3)
#define ENPOSISTERS_GET_MEG_CLONE(thisx) (((thisx)->params >> 0xA) & 3)
#define ENPOSISTERS_GET_1000(thisx) ((thisx)->params & 0x1000)

#define REALMEG 0

typedef enum EnPoSisterType {
    POSISTER_TYPE_MEG,   // purple
    POSISTER_TYPE_JO,    // red
    POSISTER_TYPE_BETH,  // blue
    POSISTER_TYPE_AMY,   // green
} EnPoSisterType;

// stateTimer gets reused:
// in the death actionfunc it counts frames up to actionfunc changes
// when spinning back into reality, it counts frames of the animation

typedef struct EnPoSisters {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnPoSistersActionFunc actionFunc;
    /* 0x018C */ u8 sisterType;
    /* 0x018D */ u8 megCloneNum;
    /* 0x018E */ u8 unk_18E; // timer, start at 32
    /* 0x018F */ u8 unk_18F; // timer, based on targeting from player?
    /* 0x0190 */ u8 unk_190; // count of 22C?
    /* 0x0191 */ u8 flags191;
    /* 0x0192 */ s16 stateTimer;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ Vec3s jointTable[12];
    /* 0x01DE */ Vec3s morphTable[12];
    /* 0x0226 */ Color_RGBA8 color;
    /* 0x022C */ Vec3f unk_22C[8]; // uh... these are used in draw
    /* 0x028C */ Vec3f unk_28C[8];
    /* 0x02EC */ f32 megDistToPlayer;
    /* 0x02F0 */ f32 unk_2F0;
    /* 0x02F4 */ f32 unk_2F4;
    /* 0x02F8 */ LightNode* lightNode;
    /* 0x02FC */ LightInfo lightInfo;
    /* 0x030C */ ColliderCylinder collider;
    /* 0x0358 */ MtxF mtxf;
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
