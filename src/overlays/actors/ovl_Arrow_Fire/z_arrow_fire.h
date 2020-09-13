#ifndef Z_ARROW_FIRE_H
#define Z_ARROW_FIRE_H

#include <global.h>

struct ArrowFire;

typedef struct ArrowFire {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x120];
} ArrowFire; // size = 0x264

extern const ActorInit Arrow_Fire_InitVars;

#endif // Z_ARROW_FIRE_H
