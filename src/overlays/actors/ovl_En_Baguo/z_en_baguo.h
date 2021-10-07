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
    /* 0x00 */ u8 visible;
    /* 0x04 */ Vec3f position;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f acceleration;
    /* 0x28 */ Vec3s rotation;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 timer;
} NejironParticle; // size = 0x38

typedef struct EnBaguo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[3];
    /* 0x19A */ Vec3s morphTable[3];
    /* 0x1AC */ EnBaguoActionFunc actionFunc;
    /* 0x1B0 */ s16 eyeIndex;
    /* 0x1B2 */ s16 blinkTimer;
    /* 0x1B4 */ s16 timer;
    /* 0x1B6 */ s16 state;
    /* 0x1B8 */ s16 zRollDirection; // 0 when rolling to its right, 1 when rolling to its left
    /* 0x1BC */ f32 maxDistanceFromHome;
    /* 0x1C0 */ u8 hardHitFlag;
    /* 0x1C4 */ Vec3f currentRollingRotation;
    /* 0x1D0 */ Vec3f targetRollingRotation;
    /* 0x1DC */ ColliderJntSph collider;
    /* 0x1FC */ ColliderJntSphElement colliderElements[1];
    /* 0x23C */ NejironParticle particles[30];
} EnBaguo; // size = 0x8CC

/**
 * NEJIRON_STATE_INACTIVE: The Nejiron is either underground or emerging from underground
 * NEJIRON_STATE_ACTIVE: The Nejiron is above ground and actively chasing the player
 * NEJIRON_STATE_RETREATING: The Nejiron is burrowing back underground
 * NEJIRON_STATE_EXPLODING: The Nejiron has detonated
 */ 
typedef enum {
    /* 0x0 */ NEJIRON_STATE_INACTIVE,
    /* 0x1 */ NEJIRON_STATE_ACTIVE,
    /* 0x2 */ NEJIRON_STATE_RETREATING,
    /* 0x3 */ NEJIRON_STATE_EXPLODING
} NejironState;

extern const ActorInit En_Baguo_InitVars;

#endif // Z_EN_BAGUO_H
