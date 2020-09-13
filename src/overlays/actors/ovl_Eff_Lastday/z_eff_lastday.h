#ifndef Z_EFF_LASTDAY_H
#define Z_EFF_LASTDAY_H

#include <global.h>

struct EffLastday;

typedef struct EffLastday {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14];
} EffLastday; // size = 0x158

extern const ActorInit Eff_Lastday_InitVars;

#endif // Z_EFF_LASTDAY_H
