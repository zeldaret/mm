#ifndef Z_EN_OWL_H
#define Z_EN_OWL_H

#include "global.h"

struct EnOwl;

typedef void (*EnOwlActionFunc)(struct EnOwl*, GlobalContext*);

typedef struct EnOwl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x2CC];
    /* 0x0410 */ EnOwlActionFunc actionFunc;
    /* 0x0414 */ char unk_414[0x4];
} EnOwl; // size = 0x418

extern const ActorInit En_Owl_InitVars;

#endif // Z_EN_OWL_H
