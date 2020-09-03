#ifndef _Z_EN_OSN_H_
#define _Z_EN_OSN_H_

#include <global.h>

struct EnOsn;

typedef struct EnOsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xBC];
} EnOsn; // size = 0x200

extern const ActorInit En_Osn_InitVars;

#endif
