#ifndef Z_EN_SDA_H
#define Z_EN_SDA_H

#include "global.h"

struct EnSda;

#define ENSDA_1 1

typedef struct EnSda {
    /* 0x000 */ Actor actor;
} EnSda; // size = 0x144

extern const ActorInit En_Sda_InitVars;

#endif // Z_EN_SDA_H
