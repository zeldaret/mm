#ifndef Z_EN_ENCOUNT2_H
#define Z_EN_ENCOUNT2_H

#include <global.h>

struct EnEncount2;

typedef struct EnEncount2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x292C];
} EnEncount2; // size = 0x2A70

extern const ActorInit En_Encount2_InitVars;

#endif // Z_EN_ENCOUNT2_H
