#ifndef Z_EN_RU_H
#define Z_EN_RU_H

#include "global.h"
#include "objects/object_ru2/object_ru2.h"

#define RU_GET_PATH_INDEX(thisx) ((thisx->params & 0x7E00) >> 9)

#define RU_PATH_INDEX_NONE 0x3F

struct EnRu;

typedef void (*EnRuActionFunc)(struct EnRu*, PlayState*);

#define RU_BODYPARTSPOS_COUNT 15

typedef struct EnRu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnRuActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ UNK_TYPE1 pad1D8[0x4];
    /* 0x1DC */ Path* path; // path is prepared in EnRu_Init, but unused after
    /* 0x1E0 */ UNK_TYPE1 pad1E0[0x4];
    /* 0x1E4 */ Vec3f leftFootPos;
    /* 0x1F0 */ Vec3f rightFootPos;
    /* 0x1FC */ u8 isLeftFootGrounded;
    /* 0x1FD */ u8 isRightFootGrounded;
    /* 0x1FE */ Vec3s jointTable[RU2_LIMB_MAX];
    /* 0x288 */ Vec3s morphTable[RU2_LIMB_MAX];
    /* 0x312 */ Vec3s trackTarget;
    /* 0x318 */ Vec3s headRot;
    /* 0x31E */ Vec3s torsoRot;
    /* 0x324 */ UNK_TYPE1 pad324[0x12];
    /* 0x336 */ s16 fidgetTableY[RU2_LIMB_MAX];
    /* 0x364 */ s16 fidgetTableZ[RU2_LIMB_MAX];
    /* 0x394 */ Vec3f bodyPartsPos[RU_BODYPARTSPOS_COUNT];
    /* 0x348 */ UNK_TYPE1 padUNK[6];
    /* 0x44E */ s16 eyeState;
    /* 0x450 */ s16 blinkTimer;
} EnRu; // size = 0x454

#endif // Z_EN_RU_H
