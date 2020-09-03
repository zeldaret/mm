#ifndef _Z_EN_HANABI_H_
#define _Z_EN_HANABI_H_

#include <global.h>

struct EnHanabi;

typedef struct EnHanabi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x4514];
} EnHanabi; // size = 0x4658

extern const ActorInit En_Hanabi_InitVars;

#endif
