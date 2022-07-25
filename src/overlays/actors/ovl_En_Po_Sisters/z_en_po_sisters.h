#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"
#include "objects/object_po_sisters/object_po_sisters.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, PlayState*);

#define ENPOSISTERS_GET_OBSERVER_FLAG(thisx) ((thisx)->params & 0x1000)
#define ENPOSISTERS_GET_MEG_CLONE_ID(thisx) (((thisx)->params >> 0xA) & 3)
#define ENPOSISTERS_GET_TYPE(thisx) (((thisx)->params >> 8) & 3)

#define ENPOSISTERS_PARAMS(observerFlag, megClone, type) (((observerFlag) << 0xC) | ((megClone & 3) << 0xA) | ((type & 3) << 8))

typedef enum {
    /* 0 */ POSISTER_TYPE_MEG,   // purple
    /* 1 */ POSISTER_TYPE_JO,    // red
    /* 2 */ POSISTER_TYPE_BETH,  // blue
    /* 3 */ POSISTER_TYPE_AMY,   // green
} EnPoSisterType;

typedef enum {
    /* 0 */ POSISTER_MEG_REAL,
    /* 1 */ POSISTER_MEG_CLONE1,
    /* 2 */ POSISTER_MEG_CLONE2,
    /* 3 */ POSISTER_MEG_CLONE3,
} EnPoSisterMegCloneID;

typedef struct EnPoSisters {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnPoSistersActionFunc actionFunc;
    /* 0x18C */ u8 type;
    /* 0x18D */ u8 megCloneId;
    /* 0x18E */ u8 floatingBobbingTimer; // counts down from 32 to zero, reset
    /* 0x18F */ u8 zTargetTimer; // how many frames the player is z targeting, if zero -> invis
    /* 0x190 */ u8 fireCount;
    /* 0x191 */ u8 poSisterFlags;
    /* 0x192 */ union {
                s16 stateTimer; // generic name for resets
                s16 spinTimer; // frames of spinning since spin attack starts, when zero checks collision
                s16 fleeTimer; // after being hit, 5 frames of flying away
                s16 deathTimer; // (incr) controls timings of the death cutscene, reset between the two stages
                s16 laughTimer; // if observer, will laugh once in awhile
                s16 spinupTimer; // frames of spinning up (gaining speed) for attack (jo/beth/amy attack)
                s16 megSurroundTimer; // frames of meg circling the player menacingly until spin attack
                s16 spinInvisibleTimer; // frames of spining away to invisible and back to visible
                s16 idleFlyingAnimationCounter; // count: animations completed since entering actionFunc
    };
    /* 0x194 */ union {
                s16 invisibleTimer; // frames until coming back to fight from invisible (all combat variants)
                s16 megAttackTimer; // delay until meg spin attacks player (negative frames counting up to 0) 
                s16 megClonesRemaining; // positive count of meg clones remaining
    };
    /* 0x196 */ Vec3s jointTable[POSISTERS_LIMB_MAX];
    /* 0x1DE */ Vec3s morphTable[POSISTERS_LIMB_MAX];
    /* 0x226 */ Color_RGBA8 color;
    /* 0x22C */ Vec3f firePos[8];
    /* 0x28C */ Vec3f limbPos[8]; // passed to Actor_DrawDamageEffects
    /* 0x2EC */ f32 megDistToPlayer;
    /* 0x2F0 */ f32 drawDmgEffAlpha;
    /* 0x2F4 */ f32 drawDmgEffScale;
    /* 0x2F8 */ LightNode* lightNode;
    /* 0x2FC */ LightInfo lightInfo;
    /* 0x30C */ ColliderCylinder collider;
    /* 0x358 */ MtxF mtxf;
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
