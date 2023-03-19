#ifndef Z_EN_BSB_H
#define Z_EN_BSB_H

#include "global.h"

struct EnBsb;

typedef void (*EnBsbActionFunc)(struct EnBsb*, PlayState*);

typedef struct EnBsb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBsbActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0x54];
    /* 0x02DC */ s32 unk2DC;
    /* 0x02E0 */ char unk2E0[0xE78];
} EnBsb; // size = 0x1158

#endif // Z_EN_BSB_H
