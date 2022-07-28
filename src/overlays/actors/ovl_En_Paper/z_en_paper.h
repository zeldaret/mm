#ifndef Z_EN_PAPER_H
#define Z_EN_PAPER_H

#include "global.h"

struct EnPaper;

typedef void (*EnPaperActionFunc)(struct EnPaper*, PlayState*);

typedef struct EnPaper {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnPaperActionFunc actionFunc;
    /* 0x148 */ char unk_148[0xC40];
} EnPaper; // size = 0xD88

extern const ActorInit En_Paper_InitVars;

#endif // Z_EN_PAPER_H
