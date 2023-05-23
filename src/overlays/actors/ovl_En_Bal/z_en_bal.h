#ifndef Z_EN_BAL_H
#define Z_EN_BAL_H

#include "global.h"
#include "z64snap.h"

struct EnBal;

typedef void (*EnBalActionFunc)(struct EnBal*, PlayState*);

typedef struct EnBal {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ char unk_148[0x44];
    /* 0x18C */ EnBalActionFunc actionFunc;
    /* 0x190 */ char unk_190[0x224];
} EnBal; // size = 0x3B4

#endif // Z_EN_BAL_H
