#ifndef Z_EN_SI_H
#define Z_EN_SI_H

#include "global.h"

struct EnSi;

typedef void (*EnSiActionFunc)(struct EnSi*, PlayState*);

typedef struct EnSi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnSiActionFunc actionFunc;
    /* 0x148 */ ColliderSphere collider_sphere;
} EnSi; // size = 0x1A0

#endif // Z_EN_SI_H
