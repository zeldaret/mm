#ifndef Z_EN_LOOK_NUTS_H
#define Z_EN_LOOK_NUTS_H

#include "global.h"
#include "objects/object_dnk/object_dnk.h"

struct EnLookNuts;

typedef void (*EnLookNutsActionFunc)(struct EnLookNuts*, GlobalContext*);

#define LOOKNUTS_GET_SPAWN_INDEX(thisx) (((thisx)->params >> 0xC) & 0xF)
#define LOOKNUTS_GET_SCENE_FLAG(thisx) ((thisx)->params & 0x7F)
#define LOOKNUTS_GET_PATROL_LOCATION(thisx) (((thisx)->params >> 0x7) & 0x1F)

typedef struct EnLookNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[OBJECT_DNK_LIMB_MAX];
    /* 0x01CA */ Vec3s morphTable[OBJECT_DNK_LIMB_MAX];
    /* 0x020C */ EnLookNutsActionFunc actionFunc;
    /* 0x0210 */ Path *path;
    /* 0x0214 */ s16 currentPathIndex; // Index for the point where the deku guard is in its path 
    /* 0x0216 */ s16 eyeState;
    /* 0x0218 */ s16 blinkTimer; 
    /* 0x021A */ s16 eventTimer; // Timer to trigger when another event within the actor will happen
    /* 0x021C */ s16 state;
    /* 0x021E */ s16 switchFlag;
    /* 0x0220 */ s16 pathLocation; // Determines path that a guard will patrol
    /* 0x0222 */ s16 isPlayerDetected;
    /* 0x0224 */ s16 waitTimer; // Timer for how long the deku guard will take a break for
    /* 0x0226 */ s16 spawnIndex;
    /* 0x0228 */ UNK_TYPE4 pad228; // Unused necessary padding
    /* 0x022C */ Vec3f headRotation;
    /* 0x0238 */ Vec3f headRotTarget; // Target value for head rotation
    /* 0x0244 */ ColliderCylinder collider;
} EnLookNuts; // size = 0x290

extern const ActorInit En_Look_Nuts_InitVars;

#endif // Z_EN_LOOK_NUTS_H
