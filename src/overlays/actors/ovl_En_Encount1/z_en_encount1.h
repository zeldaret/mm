#ifndef Z_EN_ENCOUNT1_H
#define Z_EN_ENCOUNT1_H

#include "global.h"

struct EnEncount1;

typedef void (*EnEncount1ActionFunc)(struct EnEncount1*, PlayState*);

typedef struct EnEncount1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnEncount1ActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x6];
    /* 0x14E */ s16 unk_14E;
    /* 0x150 */ char unk_150[0xA];
    /* 0x15A */ s16 unk_15A;
    /* 0x15C */ char unk_15C[0x8];
} EnEncount1; // size = 0x164

extern const ActorInit En_Encount1_InitVars;

#endif // Z_EN_ENCOUNT1_H
