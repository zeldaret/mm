#ifndef Z_EN_BJI_01_H
#define Z_EN_BJI_01_H

#include <global.h>
#include "overlays/actors/ovl_Obj_Moon_Stone/z_obj_moon_stone.h"

struct EnBji01;

typedef void (*EnBji01ActionFunc)(struct EnBji01*, GlobalContext*);

typedef struct EnBji01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnBji01ActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s jointTable[0x10]; 
    /* 0x238 */ Vec3s morphTable[0x10];
    /* 0x298 */ s32 animationIndex;
    /* 0x29C */ s16 eyeTexIndex;
    /* 0x29E */ s16 blinkSeqIndex;
    /* 0x2A0 */ s16 blinkTimer;
    /* 0x2A2 */ s16 torsoZRotAdj;
    /* 0x2A4 */ s16 torsoXRotAdj;
    /* 0x2A6 */ s16 headZRotAdj;
    /* 0x2A8 */ s16 headXRotAdj;
    /* 0x2AA */ u16 textId;
    /* 0x2AC */ s16 cutscenes[1];
    /* 0x2B0 */ ObjMoonStone* moonsTear;

} EnBji01; // size = 0x2B4

extern const ActorInit En_Bji_01_InitVars;

#endif // Z_EN_BJI_01_H
