#ifndef Z_EN_RU_H
#define Z_EN_RU_H

#include "global.h"
#include "objects/object_ru2/object_ru2.h"

#define RU_GET_PATH(thisx) ((thisx->params & 0x7E00) >> 9)

struct EnRu;

typedef void (*EnRuActionFunc)(struct EnRu*, PlayState*);

typedef struct EnRu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnRuActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ UNK_TYPE1 pad1D8[0x4];
    /* 0x1DC */ Path* path;
    /* 0x1E0 */ UNK_TYPE1 pad1E0[0x4];
    /* 0x1E4 */ Vec3f vec1E4LeftFoot;
    /* 0x1F0 */ Vec3f vec1F0RightFoot;
    /* 0x1FC */ u8 isFloorAbove1;
    /* 0x1FD */ u8 isFloorAbove2;
    /* 0x1FE */ Vec3s jointTable[RU2_LIMB_MAX];
    /* 0x288 */ Vec3s morphTable[RU2_LIMB_MAX];
    /* 0x312 */ Vec3s trackTarget;
    /* 0x318 */ Vec3s headRot;
    /* 0x31E */ Vec3s torsoRot;
    /* 0x324 */ UNK_TYPE1 pad324[0x12];
    /* 0x336 */ s16 limbRotTableY[RU2_LIMB_MAX];
    /* 0x364 */ s16 limbRotTableZ[RU2_LIMB_MAX];
    /* 0x364 */ UNK_TYPE1 pad392[0x2];
    /* 0x394 */ Vec3f bodyPartsPos[0xF]; // why is this not RU2_LIMB_MAX? F is the size of the shadow tho...
    /* 0x348 */ UNK_TYPE1 padUNK[6];
    /* 0x44E */ s16 eyeState;
    /* 0x450 */ s16 blinkTimer;

} EnRu; // size = 0x454

extern const ActorInit En_Ru_InitVars;

#endif // Z_EN_RU_H
