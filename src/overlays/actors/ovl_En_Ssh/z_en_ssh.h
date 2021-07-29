#ifndef Z_EN_SSH_H
#define Z_EN_SSH_H

#include "global.h"

struct EnSsh;

typedef void (*EnSshActionFunc)(struct EnSsh* this, GlobalContext* globalCtx);

typedef struct EnSsh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1AC];
    /* 0x02F0 */ EnSshActionFunc actionFunc;
    /* 0x02F4 */ char unk_2F4[0x2D8];
} EnSsh; // size = 0x5CC

extern const ActorInit En_Ssh_InitVars;

#endif // Z_EN_SSH_H
