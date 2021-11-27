#ifndef Z_EN_ONPUMAN_H
#define Z_EN_ONPUMAN_H

#include "global.h"

struct EnOnpuman;

typedef void (*EnOnpumanActionFunc)(struct EnOnpuman*, GlobalContext*);

typedef struct EnOnpuman {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x164];
    /* 0x02A8 */ EnOnpumanActionFunc actionFunc;
} EnOnpuman; // size = 0x2AC

extern const ActorInit En_Onpuman_InitVars;

#endif // Z_EN_ONPUMAN_H
