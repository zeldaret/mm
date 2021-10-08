#ifndef Z_OCEFF_WIPE6_H
#define Z_OCEFF_WIPE6_H

#include "global.h"

struct OceffWipe6;

typedef struct OceffWipe6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 counter;
} OceffWipe6; // size = 0x148

extern const ActorInit Oceff_Wipe6_InitVars;

#endif // Z_OCEFF_WIPE6_H
