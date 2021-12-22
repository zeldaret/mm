#ifndef Z_EN_MINIDEATH_H
#define Z_EN_MINIDEATH_H

#include "global.h"

struct EnMinideath;

typedef void (*EnMinideathActionFunc)(struct EnMinideath*, GlobalContext*);

typedef struct EnMinideath {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMinideathActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x164];
} EnMinideath; // size = 0x2AC

extern const ActorInit En_Minideath_InitVars;

#endif // Z_EN_MINIDEATH_H
