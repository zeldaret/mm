#ifndef Z_EN_PR2_H
#define Z_EN_PR2_H

#include <global.h>

struct EnPr2;

typedef struct EnPr2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x184];
} EnPr2; // size = 0x2C8

extern const ActorInit En_Pr2_InitVars;

#endif // Z_EN_PR2_H
