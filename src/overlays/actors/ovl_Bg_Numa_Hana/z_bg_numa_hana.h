#ifndef Z_BG_NUMA_HANA_H
#define Z_BG_NUMA_HANA_H

#include "global.h"

struct BgNumaHana;

typedef void (*BgNumaHanaActionFunc)(struct BgNumaHana*, GlobalContext*);

typedef struct BgNumaHana {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xF0];
    /* 0x0234 */ BgNumaHanaActionFunc actionFunc;
    /* 0x0238 */ char unk_238[0x108];
} BgNumaHana; // size = 0x340

extern const ActorInit Bg_Numa_Hana_InitVars;

#endif // Z_BG_NUMA_HANA_H
