#ifndef Z_EN_JG_H
#define Z_EN_JG_H

#include "global.h"
#include "objects/object_jg/object_jg.h"

#define EN_JG_IS_IN_GORON_SHRINE(thisx) ((thisx)->params & 0x1)
#define EN_JG_GET_PATH(thisx) (((thisx)->params & 0xFC00) >> 10)

struct EnJg;

typedef void (*EnJgActionFunc)(struct EnJg*, GlobalContext*);

typedef struct EnJg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Actor* shrineGoron;
    /* 0x148 */ Actor* icePoly;
    /* 0x14C */ ColliderCylinder collider;
    /* 0x198 */ SkelAnime skelAnime;
    /* 0x1DC */ EnJgActionFunc actionFunc;
    /* 0x1E0 */ Path* path;
    /* 0x1E4 */ s32 currentPoint;
    /* 0x1E8 */ Actor* drum;
    /* 0x1EC */ Vec3s unusedRotation1; // probably meant to be a head rotation to look at the player
    /* 0x1F2 */ Vec3s unusedRotation2; // probably meant to be a body rotation to look at the player
    /* 0x1F8 */ Vec3s jointTable[GORON_ELDER_LIMB_MAX];
    /* 0x2CA */ Vec3s morphTable[GORON_ELDER_LIMB_MAX];
    /* 0x39C */ s16 rootRotationWhenTalking;
    /* 0x39E */ s16 animationIndex;
    /* 0x3A0 */ s16 action;
    /* 0x3A2 */ s16 freezeTimer;
    /* 0x3A4 */ Vec3f breathPos;
    /* 0x3B0 */ Vec3f breathVelocity;
    /* 0x3BC */ Vec3f breathAccel;
    /* 0x3C8 */ s16 cutscene;
    /* 0x3CA */ u8 cutsceneAnimationIndex;
    /* 0x3CB */ u8 csAction;
    /* 0x3CC */ u16 flags;
    /* 0x3CE */ u16 textId;
    /* 0x3D0 */ u8 focusedShrineGoronParam;
} EnJg; // size = 0x3D4

extern const ActorInit En_Jg_InitVars;

#endif // Z_EN_JG_H
