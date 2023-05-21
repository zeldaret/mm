#ifndef Z_EN_GRASSHOPPER_H
#define Z_EN_GRASSHOPPER_H

#include "global.h"
#include "objects/object_grasshopper/object_grasshopper.h"

#define EN_GRASSHOPPER_GET_TYPE(thisx) ((thisx)->params)

#define EN_GRASSHOPPER_PARAMS(type) (type)

struct EnGrasshopper;

typedef void (*EnGrasshopperActionFunc)(struct EnGrasshopper*, PlayState*);

typedef enum EnGrasshopperType {
    /* -1 */ EN_GRASSHOPPER_TYPE_UNUSED_NORMAL = -1, // Acts exactly like EN_GRASSHOPPER_TYPE_NORMAL
    /*  0 */ EN_GRASSHOPPER_TYPE_NORMAL,
    /*  1 */ EN_GRASSHOPPER_TYPE_GROWS_WHEN_SPAWNED, // Spawned by EnEncount1
    /*  2 */ EN_GRASSHOPPER_TYPE_WOODFALL_TEMPLE_FINAL_ROOM,
    /*  3 */ EN_GRASSHOPPER_TYPE_WOODFALL,
} EnGrasshopperType;

typedef struct EnGrasshopperEffect {
    /* 0x00 */ u8 isEnabled;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ f32 yaw;
    /* 0x20 */ Vec3f scale;
    /* 0x2C */ s16 timer;
    /* 0x2E */ s16 lightningIndex;
} EnGrasshopperEffect; // size = 0x30

#define EN_GRASSHOPPER_EFFECT_COUNT 100

typedef struct EnGrasshopper {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[DRAGONFLY_LIMB_MAX];
    /* 0x0218 */ Vec3s morphTable[DRAGONFLY_LIMB_MAX];
    /* 0x02A8 */ EnGrasshopperActionFunc actionFunc;
    /* 0x02AC */ u8 decision;
    /* 0x02AD */ u8 shouldTurn;
    /* 0x02AE */ UNK_TYPE1 unk_2AE[2];
    /* 0x02B0 */ s16 timer;
    /* 0x02B2 */ s16 waitTimer;
    /* 0x02B4 */ s16 postBankTimer;
    /* 0x02B6 */ s16 drawDmgEffTimer;
    /* 0x02B8 */ s16 drawDmgEffType;
    /* 0x02BC */ f32 drawDmgEffScale;
    /* 0x02C0 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x02C4 */ Vec3f bodyPartsPos[12];
    /* 0x0354 */ s16 bodyPartsPosIndex;
    /* 0x0356 */ s16 splashCount;
    /* 0x0358 */ s16 action;
    /* 0x035A */ s16 index; // Has a minor effect on speed for some reason.
    /* 0x035C */ s16 bankState;
    /* 0x035E */ s16 type;
    /* 0x0360 */ f32 dragonflyScale;
    /* 0x0364 */ f32 rotationalVelocity;
    /* 0x0368 */ f32 endFrame;
    /* 0x036C */ f32 approachSpeed;
    /* 0x0370 */ f32 baseFlyHeight;
    /* 0x0374 */ f32 targetPosY;
    /* 0x0376 */ Vec3s targetRot;
    /* 0x0380 */ Vec3f flyingHomePos;
    /* 0x038C */ s16 bobPhase;
    /* 0x038E */ UNK_TYPE1 unk_38E[0x26];
    /* 0x03B4 */ Vec3f targetApproachPos;
    /* 0x03C0 */ Vec3f tailTipPos;
    /* 0x03CC */ Vec3f effectBasePos;
    /* 0x03D8 */ Vec3f shadowBodyPartsPos[DRAGONFLY_LIMB_MAX];
    /* 0x04F8 */ f32 waterSurface;
    /* 0x04FC */ Vec3f damagedVelocity;
    /* 0x0508 */ Vec3s targetBankRot;
    /* 0x0510 */ ColliderJntSph collider;
    /* 0x0530 */ ColliderJntSphElement colliderElements[2];
    /* 0x0570 */ EnGrasshopperEffect effects[EN_GRASSHOPPER_EFFECT_COUNT];
} EnGrasshopper; // size = 0x1870

#endif // Z_EN_GRASSHOPPER_H
