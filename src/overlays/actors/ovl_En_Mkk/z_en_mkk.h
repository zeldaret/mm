#ifndef Z_EN_MKK_H
#define Z_EN_MKK_H

#include "global.h"

struct EnMkk;

typedef void (*EnMkkActionFunc)(struct EnMkk*, GlobalContext*);

typedef struct EnMkk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMkkActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x8C];
} EnMkk; // size = 0x1D4

extern const ActorInit En_Mkk_InitVars;

#endif // Z_EN_MKK_H
