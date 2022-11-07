#ifndef Z_EN_DT_H
#define Z_EN_DT_H

#include "global.h"

struct EnDt;

typedef void (*EnDtActionFunc)(struct EnDt*, PlayState*);

typedef struct EnDt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xF8];
    /* 0x23C */ EnDtActionFunc actionFunc;
    /* 0x240 */ char unk_240[0xA0];
} EnDt; // size = 0x2E0

#endif // Z_EN_DT_H
