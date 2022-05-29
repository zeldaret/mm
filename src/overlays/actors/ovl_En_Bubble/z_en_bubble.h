#ifndef Z_EN_BUBBLE_H
#define Z_EN_BUBBLE_H

#include "global.h"

struct EnBubble;

typedef void (*EnBubbleActionFunc)(struct EnBubble*, GlobalContext*);

typedef struct EnBubble {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBubbleActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x110];
} EnBubble; // size = 0x258

extern const ActorInit En_Bubble_InitVars;

#endif // Z_EN_BUBBLE_H
