#ifndef Z_EN_TOTO_H
#define Z_EN_TOTO_H

#include <global.h>

struct EnToto;

typedef struct EnToto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x188];
} EnToto; // size = 0x2CC

extern const ActorInit En_Toto_InitVars;

#endif // Z_EN_TOTO_H
