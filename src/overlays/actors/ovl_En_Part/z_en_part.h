#ifndef Z_EN_PART_H
#define Z_EN_PART_H

#include <global.h>

struct EnPart;

typedef struct EnPart {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10];
} EnPart; // size = 0x154

extern const ActorInit En_Part_InitVars;

#endif // Z_EN_PART_H
