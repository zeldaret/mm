#ifndef Z_EN_TWIG_H
#define Z_EN_TWIG_H

#include "global.h"

struct EnTwig;

typedef void (*EnTwigActionFunc)(struct EnTwig*, PlayState*);

typedef struct EnTwig {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ EnTwigActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x2C];
} EnTwig; // size = 0x18C

extern const ActorInit En_Twig_InitVars;

#endif // Z_EN_TWIG_H
