#ifndef _Z_EN_CHA_H_
#define _Z_EN_CHA_H_

#include <global.h>

struct EnCha;

typedef struct EnCha {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} EnCha; // size = 0x194

extern const ActorInit En_Cha_InitVars;

#endif
