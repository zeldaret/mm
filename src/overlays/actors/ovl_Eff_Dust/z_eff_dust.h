#ifndef Z_EFF_DUST_H
#define Z_EFF_DUST_H

#include <global.h>

struct EffDust;

typedef void (*EffDustActionFunc)(struct EffDust*, GlobalContext*);
typedef void (*EffDustDrawFunc)(Actor*, GlobalContext*);

typedef struct EffDust {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ f32 distanceTraveled[64]; // For each particle. Normalized. From 0.0f to 1.0f
    /* 0x024C */ Vec3f initialPositions[64]; // Array of position for each dust particle.
    /* 0x0544 */ u8 index;
    /* 0x0545 */ u8 life; // Only considered if actor.params is 2, 3 or 4.
    /* 0x0548 */ f32 dx; // Normalized. 0.0f to 1.0f
    /* 0x054C */ f32 dy; // Normalized. 0.0f to 1.0f
    /* 0x0550 */ f32 dz; // Normalized. 0.0f to 1.0f
    /* 0x0554 */ f32 scalingFactor;
    /* 0x0558 */ EffDustActionFunc actionFunc;
    /* 0x055C */ EffDustDrawFunc drawFunc;
} EffDust; // size = 0x560

extern const ActorInit Eff_Dust_InitVars;

#endif // Z_EFF_DUST_H
