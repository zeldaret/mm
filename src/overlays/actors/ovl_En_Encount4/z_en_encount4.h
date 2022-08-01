#ifndef Z_EN_ENCOUNT4_H
#define Z_EN_ENCOUNT4_H

#include "global.h"

struct EnEncount4;

typedef void (*EnEncount4ActionFunc)(struct EnEncount4*, PlayState*);

typedef struct EnEncount4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnEncount4ActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x4];
    /* 0x014C */ s16 unk_14C;
    /* 0x014E */ s16 unk_14E;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ char unk_152[0x6];
} EnEncount4; // size = 0x158

extern const ActorInit En_Encount4_InitVars;

#endif // Z_EN_ENCOUNT4_H
