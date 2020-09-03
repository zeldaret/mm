#ifndef _Z_OCEFF_WIPE6_H_
#define _Z_OCEFF_WIPE6_H_

#include <global.h>

struct OceffWipe6;

typedef struct OceffWipe6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} OceffWipe6; // size = 0x148

extern const ActorInit Oceff_Wipe6_InitVars;

#endif
