#ifndef Z_EN_PAPER_H
#define Z_EN_PAPER_H

#include "global.h"

struct EnPaper;

typedef struct EnPaper {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC44];
} EnPaper; // size = 0xD88

extern const ActorInit En_Paper_InitVars;

#endif // Z_EN_PAPER_H
