#ifndef Z_EN_ESTONE_H
#define Z_EN_ESTONE_H

#include "global.h"

struct EnEstone;

typedef void (*EnEstoneActionFunc)(struct EnEstone*, PlayState*);

typedef struct EnEstone {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnEstoneActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x2C2C];
} EnEstone; // size = 0x2D74

#endif // Z_EN_ESTONE_H
