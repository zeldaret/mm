#ifndef _Z_EFF_KAMEJIMA_WAVE_H_
#define _Z_EFF_KAMEJIMA_WAVE_H_

#include <global.h>

struct EffKamejimaWave;

typedef struct EffKamejimaWave {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC];
} EffKamejimaWave; // size = 0x150

extern const ActorInit Eff_Kamejima_Wave_InitVars;

#endif
