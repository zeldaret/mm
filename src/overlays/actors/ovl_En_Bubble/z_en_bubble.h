#ifndef Z_EN_BUBBLE_H
#define Z_EN_BUBBLE_H

#include "global.h"

struct EnBubble;

typedef void (*EnBubbleActionFunc)(struct EnBubble*, PlayState*);

typedef struct EnBubble {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnBubbleActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x110];
} EnBubble; // size = 0x258

extern const ActorInit En_Bubble_InitVars;

#endif // Z_EN_BUBBLE_H
