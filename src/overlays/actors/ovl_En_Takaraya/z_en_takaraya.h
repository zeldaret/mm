#ifndef Z_EN_TAKARAYA_H
#define Z_EN_TAKARAYA_H

#include <global.h>

struct EnTakaraya;

typedef struct EnTakaraya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x178];
} EnTakaraya; // size = 0x2BC

extern const ActorInit En_Takaraya_InitVars;

#endif // Z_EN_TAKARAYA_H
