#ifndef Z_EN_OSN_H
#define Z_EN_OSN_H

#include "global.h"

struct EnOsn;

typedef void (*EnOsnActionFunc)(struct EnOsn*, GlobalContext*);

typedef struct EnOsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnOsnActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x28];
} EnOsn; // size = 0x200

extern const ActorInit En_Osn_InitVars;

#endif // Z_EN_OSN_H
