#ifndef _Z_EN_OWL_H_
#define _Z_EN_OWL_H_

#include <global.h>

struct EnOwl;

typedef struct EnOwl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2D4];
} EnOwl; // size = 0x418

extern const ActorInit En_Owl_InitVars;

#endif
