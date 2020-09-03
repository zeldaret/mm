#ifndef _Z_EN_DNS_H_
#define _Z_EN_DNS_H_

#include <global.h>

struct EnDns;

typedef struct EnDns {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1BC];
} EnDns; // size = 0x300

extern const ActorInit En_Dns_InitVars;

#endif
