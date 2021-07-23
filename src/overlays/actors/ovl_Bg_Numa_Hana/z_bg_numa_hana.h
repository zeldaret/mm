#ifndef Z_BG_NUMA_HANA_H
#define Z_BG_NUMA_HANA_H

#include "global.h"

struct BgNumaHana;

typedef struct BgNumaHana {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1FC];
} BgNumaHana; // size = 0x340

extern const ActorInit Bg_Numa_Hana_InitVars;

#endif // Z_BG_NUMA_HANA_H
