#ifndef Z_OCEFF_WIPE2_H
#define Z_OCEFF_WIPE2_H

#include <global.h>

struct OceffWipe2;

typedef struct OceffWipe2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} OceffWipe2; // size = 0x148

extern const ActorInit Oceff_Wipe2_InitVars;

#endif // Z_OCEFF_WIPE2_H
