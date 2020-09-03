#ifndef _Z_EN_SDA_H_
#define _Z_EN_SDA_H_

#include <global.h>

struct EnSda;

typedef struct EnSda {
    /* 0x000 */ Actor actor;
} EnSda; // size = 0x144

extern const ActorInit En_Sda_InitVars;

#endif
