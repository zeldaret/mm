#ifndef _Z_EN_INVISIBLE_RUPPE_H_
#define _Z_EN_INVISIBLE_RUPPE_H_

#include <global.h>

struct EnInvisibleRuppe;

typedef struct EnInvisibleRuppe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnInvisibleRuppe; // size = 0x198

extern const ActorInit En_Invisible_Ruppe_InitVars;

#endif
