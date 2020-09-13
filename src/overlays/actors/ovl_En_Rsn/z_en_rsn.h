#ifndef Z_EN_RSN_H
#define Z_EN_RSN_H

#include <global.h>

struct EnRsn;

typedef struct EnRsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA0];
} EnRsn; // size = 0x1E4

extern const ActorInit En_Rsn_InitVars;

#endif // Z_EN_RSN_H
