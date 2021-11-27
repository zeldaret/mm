#ifndef Z_OCEFF_STORM_H
#define Z_OCEFF_STORM_H

#include "global.h"

struct OceffStorm;

typedef void (*OceffStormActionFunc)(struct OceffStorm*, GlobalContext*);

typedef struct OceffStorm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x8];
    /* 0x014C */ OceffStormActionFunc actionFunc;
} OceffStorm; // size = 0x150

extern const ActorInit Oceff_Storm_InitVars;

#endif // Z_OCEFF_STORM_H
