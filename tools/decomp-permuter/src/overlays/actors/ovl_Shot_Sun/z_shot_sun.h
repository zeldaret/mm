#ifndef Z_SHOT_SUN_H
#define Z_SHOT_SUN_H

#include <global.h>

struct ShotSun;

typedef struct ShotSun {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
} ShotSun; // size = 0x1A0

extern const ActorInit Shot_Sun_InitVars;

#endif // Z_SHOT_SUN_H
