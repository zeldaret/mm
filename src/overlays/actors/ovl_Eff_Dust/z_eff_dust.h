#ifndef Z_EFF_DUST_H
#define Z_EFF_DUST_H

#include "global.h"

struct EffDust;

typedef void (*EffDustActionFunc)(struct EffDust*, PlayState*);

typedef struct EffDust {
    /* 0x000 */ Actor actor;
    /* 0x144 */ f32 distanceTraveled[64]; // For each particle. Normalized. From 0.0f to 1.0f
    /* 0x244 */ Vec3f initialPositions[64]; // Array of position for each dust particle.
    /* 0x544 */ u8 index;
    /* 0x545 */ u8 life; // Only considered if actor.params is 2, 3 or 4.
    /* 0x548 */ f32 dx; // Normalized. 0.0f to 1.0f
    /* 0x54C */ f32 dy; // Normalized. 0.0f to 1.0f
    /* 0x550 */ f32 dz; // Normalized. 0.0f to 1.0f
    /* 0x554 */ f32 scalingFactor;
    /* 0x558 */ EffDustActionFunc actionFunc;
    /* 0x55C */ ActorFunc drawFunc;
} EffDust; // size = 0x560

typedef enum {
    /* 0x0 */ EFF_DUST_TYPE_0,
    /* 0x1 */ EFF_DUST_TYPE_1,
    /* 0x2 */ EFF_DUST_TYPE_2,
    /* 0x3 */ EFF_DUST_TYPE_3,
    /* 0x4 */ EFF_DUST_TYPE_4,
    /* 0x5 */ EFF_DUST_TYPE_5
} EffDustType;

extern const ActorInit Eff_Dust_InitVars;

#endif // Z_EFF_DUST_H
