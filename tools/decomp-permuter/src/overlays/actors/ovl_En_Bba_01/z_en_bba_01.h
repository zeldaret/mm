#ifndef Z_EN_BBA_01_H
#define Z_EN_BBA_01_H

#include <global.h>

struct EnBba01;

typedef struct EnBba01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4D8];
} EnBba01; // size = 0x61C

extern const ActorInit En_Bba_01_InitVars;

#endif // Z_EN_BBA_01_H
