#ifndef Z_EN_MNK_H
#define Z_EN_MNK_H

#include "global.h"
#include "z64snap.h"

struct EnMnk;

typedef void (*EnMnkActionFunc)(struct EnMnk*, PlayState*);

typedef struct EnMnk {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ char unk_148[0x2A0];
    /* 0x3E8 */ EnMnkActionFunc actionFunc;
} EnMnk; // size = 0x3EC

#endif // Z_EN_MNK_H
