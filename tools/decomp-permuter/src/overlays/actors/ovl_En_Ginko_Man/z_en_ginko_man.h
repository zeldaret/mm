#ifndef Z_EN_GINKO_MAN_H
#define Z_EN_GINKO_MAN_H

#include <global.h>

struct EnGinkoMan;

typedef struct EnGinkoMan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x124];
} EnGinkoMan; // size = 0x268

extern const ActorInit En_Ginko_Man_InitVars;

#endif // Z_EN_GINKO_MAN_H
