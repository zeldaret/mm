#ifndef Z_EN_MT_TAG_H
#define Z_EN_MT_TAG_H

#include "global.h"

struct EnMttag;

typedef void (*EnMttagActionFunc)(struct EnMttag*, GlobalContext*);

typedef struct EnMttag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnMttagActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x10];
    /* 0x158 */ s16 unk_158;
    /* 0x15A */ s16 unk_15A;
    /* 0x15C */ char unk_15C[0xC];
} EnMttag; // size = 0x168

extern const ActorInit En_Mt_tag_InitVars;

#endif // Z_EN_MT_TAG_H
