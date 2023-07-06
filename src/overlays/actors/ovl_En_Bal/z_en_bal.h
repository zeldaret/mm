#ifndef Z_EN_BAL_H
#define Z_EN_BAL_H

#include "global.h"
#include "z64snap.h"
#include "objects/object_bal/object_bal.h"

#define EN_BAL_GET_LOCATION(thisx) ((thisx)->params & 0xFF)

struct EnBal;

typedef void (*EnBalActionFunc)(struct EnBal*, PlayState*);

typedef struct EnBal {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ EnBalActionFunc actionFunc;
    /* 0x190 */ ColliderJntSph collider;
    /* 0x1B0 */ ColliderJntSphElement colliderElement;
    /* 0x1F0 */ Vec3f balloonScale;
    /* 0x1FC */ s32 eyeTexIndex;
    /* 0x200 */ Vec3s jointTable[TINGLE_LIMB_MAX];
    /* 0x2C6 */ Vec3s morphTable[TINGLE_LIMB_MAX];
    /* 0x38C */ Vec3s headRot;
    /* 0x392 */ Vec3s torsoRot;
    /* 0x398 */ s16 eyeTimer;
    /* 0x39A */ s16 forceEyesShut;
    /* 0x39C */ s16 watchTarget;
    /* 0x39E */ s16 skyFloatPhase;
    /* 0x3A0 */ s16 lastMessageId;
    /* 0x3A2 */ char pad3A2[2];
    /* 0x3A4 */ s16 lastBalloonAction;
    /* 0x3A6 */ s16 idleAnimStage;
    /* 0x3A8 */ s16 timer;
    /* 0x3AA */ char pad3AA[2]; 
    /* 0x3AC */ s16 mapId;
    /* 0x3AE */ s16 location;    
    /* 0x3B0 */ s16 inflateEarly;
    /* 0x3B2 */ u8 isTalking;
} EnBal; /* size = 0x3B4 */

typedef enum EnBalLocation {
    /* 0x0 */ EN_BAL_LOC_CLOCK_TOWN,
    /* 0x1 */ EN_BAL_LOC_WOODFALL,
    /* 0x2 */ EN_BAL_LOC_SNOWHEAD,
    /* 0x3 */ EN_BAL_LOC_ROMANI_RANCH,
    /* 0x4 */ EN_BAL_LOC_GREAT_BAY,
    /* 0x5 */ EN_BAL_LOC_STONE_TOWER,
} EnBalLocation;
 
#endif // Z_EN_BAL_H
