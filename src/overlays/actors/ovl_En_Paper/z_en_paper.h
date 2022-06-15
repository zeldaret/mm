#ifndef Z_EN_PAPER_H
#define Z_EN_PAPER_H

#include "global.h"

struct EnPaper;

typedef void (*EnPaperActionFunc)(struct EnPaper*, GlobalContext*);

typedef struct EnPaper {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnPaperActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0xC40];
} EnPaper; // size = 0xD88

extern const ActorInit En_Paper_InitVars;

#endif // Z_EN_PAPER_H
