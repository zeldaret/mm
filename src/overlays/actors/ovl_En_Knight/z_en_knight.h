#ifndef _Z_EN_KNIGHT_H_
#define _Z_EN_KNIGHT_H_

#include <global.h>

struct EnKnight;

typedef struct EnKnight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x590];
} EnKnight; // size = 0x6D4

extern const ActorInit En_Knight_InitVars;

#endif
