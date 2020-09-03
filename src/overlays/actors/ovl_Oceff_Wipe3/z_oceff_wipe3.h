#ifndef _Z_OCEFF_WIPE3_H_
#define _Z_OCEFF_WIPE3_H_

#include <global.h>

struct OceffWipe3;

typedef struct OceffWipe3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} OceffWipe3; // size = 0x148

extern const ActorInit Oceff_Wipe3_InitVars;

#endif
