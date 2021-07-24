#ifndef Z_EN_BUBBLE_H
#define Z_EN_BUBBLE_H

#include "global.h"

struct EnBubble;

typedef struct EnBubble {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x114];
} EnBubble; // size = 0x258

extern const ActorInit En_Bubble_InitVars;

#endif // Z_EN_BUBBLE_H
