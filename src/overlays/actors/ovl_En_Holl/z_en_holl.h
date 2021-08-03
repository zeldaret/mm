#ifndef Z_EN_HOLL_H
#define Z_EN_HOLL_H

#include <global.h>

struct EnHoll;

typedef void (*EnHollActionFunc)(struct EnHoll* this, GlobalContext* globalCtx);

typedef struct EnHoll {
    /* 0x000 */ Actor actor;
    /* 0x144 */ UNK_TYPE1 type;
    /* 0x145 */ u8 opacity;
    /* 0x146 */ UNK_TYPE1 alwaysOne;
    /* 0x147 */ UNK_TYPE1 alwaysZero;
    /* 0x148 */ EnHollActionFunc actionFunc;
} EnHoll; // size = 0x14C

extern const ActorInit En_Holl_InitVars;

#endif // Z_EN_HOLL_H
