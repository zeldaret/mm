#ifndef Z_EN_TWIG_H
#define Z_EN_TWIG_H

#include <global.h>

struct EnTwig;

typedef struct EnTwig {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x48];
} EnTwig; // size = 0x18C

extern const ActorInit En_Twig_InitVars;

#endif // Z_EN_TWIG_H
