#ifndef Z_EN_JC_MATO_H
#define Z_EN_JC_MATO_H

#include <global.h>

struct EnJcMato;

typedef struct EnJcMato {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} EnJcMato; // size = 0x1B0

extern const ActorInit En_Jc_Mato_InitVars;

#endif // Z_EN_JC_MATO_H
