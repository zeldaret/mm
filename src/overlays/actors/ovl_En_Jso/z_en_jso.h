#ifndef _Z_EN_JSO_H_
#define _Z_EN_JSO_H_

#include <global.h>

struct EnJso;

typedef struct EnJso {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xEA8];
} EnJso; // size = 0xFEC

extern const ActorInit En_Jso_InitVars;

#endif
