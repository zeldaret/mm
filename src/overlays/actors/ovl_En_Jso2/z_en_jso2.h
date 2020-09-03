#ifndef _Z_EN_JSO2_H_
#define _Z_EN_JSO2_H_

#include <global.h>

struct EnJso2;

typedef struct EnJso2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0xF4C];
} EnJso2; // size = 0x1090

extern const ActorInit En_Jso2_InitVars;

#endif
