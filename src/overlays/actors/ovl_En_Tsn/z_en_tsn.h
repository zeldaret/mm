#ifndef _Z_EN_TSN_H_
#define _Z_EN_TSN_H_

#include <global.h>

struct EnTsn;

typedef struct EnTsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xF0];
} EnTsn; // size = 0x234

extern const ActorInit En_Tsn_InitVars;

#endif
