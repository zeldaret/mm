#ifndef Z_EFF_KAMEJIMA_WAVE_H
#define Z_EFF_KAMEJIMA_WAVE_H

#include "global.h"

struct EffKamejimaWave;

typedef void (*EffKamejimaWaveActionFunc)(struct EffKamejimaWave* this, GlobalContext* globalCtx);

typedef struct EffKamejimaWave {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x8];
    /* 0x014C */ EffKamejimaWaveActionFunc actionFunc;
} EffKamejimaWave; // size = 0x150

extern const ActorInit Eff_Kamejima_Wave_InitVars;

#endif // Z_EFF_KAMEJIMA_WAVE_H
