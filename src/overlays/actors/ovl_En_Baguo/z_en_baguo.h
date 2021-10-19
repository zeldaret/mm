#ifndef Z_EN_BAGUO_H
#define Z_EN_BAGUO_H

#include "global.h"

struct EnBaguo;

typedef void (*EnBaguoActionFunc)(struct EnBaguo*, GlobalContext*);

/**
 * When a Nejiron explodes, rock particles fly out from where it exploded.
 * This struct governs how these rock particles behave.
 */
typedef struct NejironParticle {
    /* 0x00 */ u8 isVisible;
    /* 0x04 */ Vec3f position;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f acceleration;
    /* 0x28 */ Vec3s rotation;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 timer;
} NejironParticle; // size = 0x38

typedef enum {
    /* 0x0 */ NEJIRON_ACTION_INACTIVE,   // The Nejiron is either underground or emerging from underground
    /* 0x1 */ NEJIRON_ACTION_ACTIVE,     // The Nejiron is above ground and actively chasing the player
    /* 0x2 */ NEJIRON_ACTION_RETREATING, // The Nejiron is burrowing back underground
    /* 0x3 */ NEJIRON_ACTION_EXPLODING   // The Nejiron has detonated
} NejironAction;

/**
 * These directions are relative to the Nejiron.
 */
typedef enum {
    /* 0x0 */ NEJIRON_DIRECTION_RIGHT,
    /* 0x1 */ NEJIRON_DIRECTION_LEFT
} NejironRollDirection;

typedef struct EnBaguo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[3];
    /* 0x19A */ Vec3s morphTable[3];
    /* 0x1AC */ EnBaguoActionFunc actionFunc;
    /* 0x1B0 */ s16 eyeIndex;
    /* 0x1B2 */ s16 blinkTimer;
    /* 0x1B4 */ s16 timer;
    /* 0x1B6 */ s16 action;
    /* 0x1B8 */ s16 zRollDirection;
    /* 0x1BC */ f32 maxDistanceFromHome;
    /* 0x1C0 */ u8 hardHitFlag;
    /* 0x1C4 */ Vec3f currentRotation;
    /* 0x1D0 */ Vec3f targetRotation;
    /* 0x1DC */ ColliderJntSph collider;
    /* 0x1FC */ ColliderJntSphElement colliderElements[1];
    /* 0x23C */ NejironParticle particles[30];
} EnBaguo; // size = 0x8CC

extern const ActorInit En_Baguo_InitVars;

#endif // Z_EN_BAGUO_H
