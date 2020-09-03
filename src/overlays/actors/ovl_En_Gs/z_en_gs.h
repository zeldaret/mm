#ifndef Z_EN_GS_H
#define Z_EN_GS_H

#include <global.h>

struct EnGs;

typedef struct EnGs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xDC];
} EnGs; // size = 0x220

extern const ActorInit En_Gs_InitVars;

#endif // Z_EN_GS_H
