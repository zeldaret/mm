#ifndef Z_EN_BEE_H
#define Z_EN_BEE_H

#include "global.h"
#include "assets/objects/object_bee/object_bee.h"

struct EnBee;

typedef void (*EnBeeActionFunc)(struct EnBee*, PlayState*);

typedef struct EnBee {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s morphTable[OBJECT_BEE_LIMB_MAX];
    /* 0x1C4 */ Vec3s jointTable[OBJECT_BEE_LIMB_MAX];
    /* 0x200 */ EnBeeActionFunc actionFunc;
    /* 0x204 */ s16 attackDelayTimer;
    /* 0x206 */ s16 sfxHitTimer;
    /* 0x208 */ s16 isHostile;  // unused
    /* 0x20C */ s32 targetYaw;
    /* 0x210 */ s32 flightHoverOffset;
    /* 0x214 */ s32 destinationIndex;
    /* 0x218 */ s32 instanceId;
    /* 0x21C */ Vec3f moveToDestinations[2];
    /* 0x234 */ UNK_TYPE1 pad234[8];
    /* 0x23C */ ColliderCylinder collider;
} EnBee; // size = 0x288

extern const ActorInit En_Bee_InitVars;

#endif // Z_EN_BEE_H
