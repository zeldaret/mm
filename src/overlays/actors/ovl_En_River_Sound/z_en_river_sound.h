#ifndef Z_EN_RIVER_SOUND_H
#define Z_EN_RIVER_SOUND_H

#include "global.h"

struct EnRiverSound;

typedef struct EnRiverSound {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 playSound;
    /* 0x145 */ u8 soundFreqIndex;
    /* 0x146 */ u8 pathCount;
    /* 0x148 */ Vec3s* pathPoints;
} EnRiverSound; // size = 0x14C

extern const ActorInit En_River_Sound_InitVars;

#endif // Z_EN_RIVER_SOUND_H
