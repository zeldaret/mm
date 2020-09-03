#ifndef Z_EN_TUBO_TRAP_H
#define Z_EN_TUBO_TRAP_H

#include <global.h>

struct EnTuboTrap;

typedef struct EnTuboTrap {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} EnTuboTrap; // size = 0x1A4

extern const ActorInit En_Tubo_Trap_InitVars;

#endif // Z_EN_TUBO_TRAP_H
