#ifndef Z_EN_RZ_H
#define Z_EN_RZ_H

#include "global.h"
#include "assets/objects/object_rz/object_rz.h"

#define EN_RZ_GET_PARAM_8000(thisx) ((thisx)->params & 0x8000)
#define EN_RZ_GET_PARAM_F(thisx) ((thisx)->params & 0xF)
#define EN_RZ_GET_PATH(thisx) (((thisx)->params & 0x7E00) >> 9)
#define EN_RZ_STATE_1 (1 << 0)
#define EN_RZ_STATE_2 (1 << 1)

struct EnRz;

typedef void (*EnRzActionFunc)(struct EnRz*, PlayState*);

typedef struct EnRz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_RZ_LIMB_MAX];
    /* 0x20C */ UNK_TYPE1 pad188[0x94];
    /* 0x2A0 */ Vec3s morphTable[OBJECT_RZ_LIMB_MAX];
    /* 0x324 */ UNK_TYPE1 pad2A0[0x94];
    /* 0x3B8 */ Path* path;
    /* 0x3BC */ s32 curPointIndex;
    /* 0x3C0 */ ColliderCylinder collider;
    /* 0x40C */ struct EnRz* sister;
    /* 0x410 */ s16 eyeIndex;
    /* 0x412 */ s16 blinkTimer;
    /* 0x414 */ Vec3f shadowPos;
    /* 0x420 */ u16 stateFlags;
    /* 0x422 */ s16 animIndex;
    /* 0x424 */ s16 timer;
    /* 0x426 */ u16 csAction;
    /* 0x428 */ u16 actionIndex;
    /* 0x42A */ s16 cutscenes[2];
    /* 0x430 */ EnRzActionFunc actionFunc;
} EnRz; // size = 0x434

extern const ActorInit En_Rz_InitVars;

#endif // Z_EN_RZ_H
