#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"
#include "objects/object_po_sisters/object_po_sisters.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, GlobalContext*);

// todo rename without en
#define ENPOSISTERS_GET_TYPE(thisx) (((thisx)->params >> 8) & 3)
#define ENPOSISTERS_GET_MEG_CLONE(thisx) (((thisx)->params >> 0xA) & 3)
#define ENPOSISTERS_GET_OBSERVER_FLAG(thisx) ((thisx)->params & 0x1000)

#define REALMEG 0

typedef enum EnPoSisterType {
    POSISTER_TYPE_MEG,   // purple
    POSISTER_TYPE_JO,    // red
    POSISTER_TYPE_BETH,  // blue
    POSISTER_TYPE_AMY,   // green
} EnPoSisterType;


typedef struct EnPoSisters {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnPoSistersActionFunc actionFunc;
    /* 0x018C */ u8 sisterType;
    /* 0x018D */ u8 megCloneNum;
    /* 0x018E */ u8 floatingBobbingTimer; // counts down from 32 to zero, reset
    /* 0x018F */ u8 zTargetTimer; // how many frames the player is z targeting, if zero -> invis
    /* 0x0190 */ u8 fireCount;
    /* 0x0191 */ u8 poSisterFlags;
    /* 0x0192 */ union {
                // stateTimer gets reused in different actionfuncs
                s16 stateTimer;  // generic name for resets
                s16 deathTimer;  // controls timings of the death cutscene, reset between the two stages
                s16 laughTimer;  // if observer, will laugh once in awhile
                s16 spinupTimer; // frames of spinning up (gaining speed) for attack (jo/beth/amy attack)
                s16 spinTimer;   // frames of spinning since spin attack starts, when zero checks collision
                s16 flinchTimer; // after being hit, 5 frames until deciding how to react to flinch
                s16 spinInvisibleTimer; // frames of spining away to invisible and back to visible
                s16 megSurroundTimer; // frames since meg attack starts
    };
    /* 0x0194 */ s16 inivisTimer;
    /* 0x0196 */ Vec3s jointTable[OBJECT_PO_SISTERS_LIMB_MAX];
    /* 0x01DE */ Vec3s morphTable[OBJECT_PO_SISTERS_LIMB_MAX];
    /* 0x0226 */ Color_RGBA8 color;
    /* 0x022C */ Vec3f fireLoc[8];
    /* 0x028C */ Vec3f limbPos[8];
    /* 0x02EC */ f32 megDistToPlayer;
    /* 0x02F0 */ f32 drawDmgEffAlpha;
    /* 0x02F4 */ f32 drawDmgEffScale;
    /* 0x02F8 */ LightNode* lightNode;
    /* 0x02FC */ LightInfo lightInfo;
    /* 0x030C */ ColliderCylinder collider;
    /* 0x0358 */ MtxF mtxf;
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
