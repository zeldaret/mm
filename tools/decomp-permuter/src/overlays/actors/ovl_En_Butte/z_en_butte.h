#ifndef Z_EN_BUTTE_H
#define Z_EN_BUTTE_H

#include <global.h>

struct EnButte;

typedef struct EnButte {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x11C];
} EnButte; // size = 0x260

extern const ActorInit En_Butte_InitVars;

#endif // Z_EN_BUTTE_H
