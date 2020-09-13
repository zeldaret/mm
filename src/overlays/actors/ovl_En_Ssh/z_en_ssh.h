#ifndef Z_EN_SSH_H
#define Z_EN_SSH_H

#include <global.h>

struct EnSsh;

typedef struct EnSsh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x488];
} EnSsh; // size = 0x5CC

extern const ActorInit En_Ssh_InitVars;

#endif // Z_EN_SSH_H
