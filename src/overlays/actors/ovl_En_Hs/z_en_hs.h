#ifndef Z_EN_HS_H
#define Z_EN_HS_H

#include "global.h"
#include "objects/object_hs/object_hs.h"

struct EnHs;

typedef void (*EnHsActionFunc)(struct EnHs*, GlobalContext*);

#define HS_GET_EXIT_INDEX(thisx) ((thisx)->params & 0xF)

#define HS_TYPE_UNK1 1

// params mystery: Vanilla grog is 0xFE01
//   0xFE00 space is never checked in Grog code
//   at the same time, type UNK1 is only checked directly with params == 1, no &F
//   so HS_TYPE_UNK1 is never valid and is unused, as 0xFE00 is still present even if its not doing anything else

// The count of [chicks following the player]   is stored in [this->actor.home.rot.z] (incremented by 2)
// The count of [chicks transformed into adult] is stored in [this->actor.home.rot.x] (incremented by 2)

typedef struct EnHs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ Vec3s jointTable[OBJECT_HS_LIMB_MAX];
    /* 0x0234 */ Vec3s morphTable[OBJECT_HS_LIMB_MAX];
    /* 0x0294 */ Vec3s headRot;
    /* 0x029A */ Vec3s unkRot29A; // probably not chest, as chest is same limb as lower body
    /* 0x02A0 */ u16 unkStateFlags2A0;
    /* 0x02A2 */ s16 stateTimer;
    /* 0x02A4 */ Vec3f nwcPos[20]; // actual position are even values, odds are read but never set (?)
    /* 0x0394 */ EnHsActionFunc actionFunc;
} EnHs; // size = 0x398

extern const ActorInit En_Hs_InitVars;

#endif // Z_EN_HS_H
