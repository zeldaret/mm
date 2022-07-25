#ifndef Z_EN_MNK_H
#define Z_EN_MNK_H

#include "global.h"

struct EnMnk;

typedef void (*EnMnkActionFunc)(struct EnMnk*, PlayState*);

typedef struct EnMnk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2A4];
    /* 0x3E8 */ EnMnkActionFunc actionFunc;
} EnMnk; // size = 0x3EC

#endif // Z_EN_MNK_H
