#ifndef Z_EN_KNIGHT_H
#define Z_EN_KNIGHT_H

#include <global.h>

struct EnKnight;

typedef struct EnKnight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x590];
} EnKnight; // size = 0x6D4

extern const ActorInit En_Knight_InitVars;

#endif // Z_EN_KNIGHT_H
