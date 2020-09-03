#ifndef Z_EN_SNOWMAN_H
#define Z_EN_SNOWMAN_H

#include <global.h>

struct EnSnowman;

typedef struct EnSnowman {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x234];
} EnSnowman; // size = 0x378

extern const ActorInit En_Snowman_InitVars;

#endif // Z_EN_SNOWMAN_H
