#ifndef Z_EN_DNS_H
#define Z_EN_DNS_H

#include "global.h"

struct EnDns;

typedef void (*EnDnsActionFunc)(struct EnDns*, GlobalContext*);

typedef struct EnDns {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDnsActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x174];
} EnDns; // size = 0x300

extern const ActorInit En_Dns_InitVars;

#endif // Z_EN_DNS_H
