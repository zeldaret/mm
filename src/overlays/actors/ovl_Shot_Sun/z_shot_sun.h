#ifndef Z_SHOT_SUN_H
#define Z_SHOT_SUN_H

#include "global.h"

struct ShotSun;

typedef void (*ShotSunActionFunc)(struct ShotSun* this, GlobalContext* globalCtx);

typedef struct ShotSun {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ ShotSunActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0xC];
} ShotSun; // size = 0x1A0

extern const ActorInit Shot_Sun_InitVars;

#endif // Z_SHOT_SUN_H
