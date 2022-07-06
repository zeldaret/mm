#ifndef Z_EFF_KAMEJIMA_WAVE_H
#define Z_EFF_KAMEJIMA_WAVE_H

#include "global.h"

struct EffKamejimaWave;

typedef void (*EffKamejimaWaveActionFunc)(struct EffKamejimaWave*, PlayState*);

typedef struct EffKamejimaWave {
    /* 0x000 */ Actor actor;
    /* 0x144 */ f32 scaleOffset;                         /* inferred */
    /* 0x148 */ UNK_TYPE1 pad148[4];
    /* 0x14C */ EffKamejimaWaveActionFunc actionFunc;
} EffKamejimaWave; // size = 0x150

extern const ActorInit Eff_Kamejima_Wave_InitVars;

#endif // Z_EFF_KAMEJIMA_WAVE_H
