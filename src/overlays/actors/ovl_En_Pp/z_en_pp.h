#ifndef Z_EN_PP_H
#define Z_EN_PP_H

#include "global.h"

struct EnPp;

typedef void (*EnPpActionFunc)(struct EnPp*, GlobalContext*);

typedef struct EnPp {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x17C];
    /* 0x02C0 */ EnPpActionFunc actionFunc;
    /* 0x02C4 */ char unk_2C4[0x328];
} EnPp; // size = 0x5EC

extern const ActorInit En_Pp_InitVars;

#endif // Z_EN_PP_H
