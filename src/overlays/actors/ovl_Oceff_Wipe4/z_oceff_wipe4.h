#ifndef Z_OCEFF_WIPE4_H
#define Z_OCEFF_WIPE4_H

#include "global.h"

struct OceffWipe4;

typedef struct OceffWipe4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} OceffWipe4; // size = 0x148

extern const ActorInit Oceff_Wipe4_InitVars;

#endif // Z_OCEFF_WIPE4_H
