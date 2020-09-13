#ifndef Z_OCEFF_WIPE7_H
#define Z_OCEFF_WIPE7_H

#include <global.h>

struct OceffWipe7;

typedef struct OceffWipe7 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} OceffWipe7; // size = 0x148

extern const ActorInit Oceff_Wipe7_InitVars;

#endif // Z_OCEFF_WIPE7_H
