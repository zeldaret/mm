#ifndef Z_EN_OSK_H
#define Z_EN_OSK_H

#include <global.h>

struct EnOsk;

typedef struct EnOsk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x120];
} EnOsk; // size = 0x264

extern const ActorInit En_Osk_InitVars;

#endif // Z_EN_OSK_H
