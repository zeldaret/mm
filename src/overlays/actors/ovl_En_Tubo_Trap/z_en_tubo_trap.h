#ifndef _Z_EN_TUBO_TRAP_H_
#define _Z_EN_TUBO_TRAP_H_

#include <global.h>

struct EnTuboTrap;

typedef struct EnTuboTrap {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} EnTuboTrap; // size = 0x1A4

extern const ActorInit En_Tubo_Trap_InitVars;

#endif
