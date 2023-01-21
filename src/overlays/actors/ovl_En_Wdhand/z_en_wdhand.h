#ifndef Z_EN_WDHAND_H
#define Z_EN_WDHAND_H

#include "global.h"

struct EnWdhand;

typedef void (*EnWdhandActionFunc)(struct EnWdhand*, PlayState*);

typedef struct EnWdhand {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA4];
    /* 0x1E8 */ EnWdhandActionFunc actionFunc;
    /* 0x1EC */ char unk_1EC[0x268];
} EnWdhand; // size = 0x454

#endif // Z_EN_WDHAND_H
