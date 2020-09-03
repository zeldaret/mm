#ifndef Z_OCEFF_WIPE5_H
#define Z_OCEFF_WIPE5_H

#include <global.h>

struct OceffWipe5;

typedef struct OceffWipe5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} OceffWipe5; // size = 0x148

extern const ActorInit Oceff_Wipe5_InitVars;

#endif // Z_OCEFF_WIPE5_H
