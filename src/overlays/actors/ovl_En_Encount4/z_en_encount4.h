#ifndef Z_EN_ENCOUNT4_H
#define Z_EN_ENCOUNT4_H

#include "global.h"

struct EnEncount4;

typedef void (*EnEncount4ActionFunc)(struct EnEncount4*, PlayState*);

typedef struct EnEncount4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnEncount4ActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x4];
    /* 0x14C */ s16 unk_14C;
    /* 0x14E */ s16 unk_14E;
    /* 0x150 */ char unk_150[0x8];
} EnEncount4; // size = 0x158

extern const ActorInit En_Encount4_InitVars;

#endif // Z_EN_ENCOUNT4_H
