#ifndef Z_EN_MINIDEATH_H
#define Z_EN_MINIDEATH_H

#include "global.h"

struct EnMinideath;

typedef void (*EnMinideathActionFunc)(struct EnMinideath*, PlayState*);

typedef struct EnMinideath {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnMinideathActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x164];
} EnMinideath; // size = 0x2AC

#endif // Z_EN_MINIDEATH_H
