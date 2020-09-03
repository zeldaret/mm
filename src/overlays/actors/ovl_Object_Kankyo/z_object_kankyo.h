#ifndef _Z_OBJECT_KANKYO_H_
#define _Z_OBJECT_KANKYO_H_

#include <global.h>

struct ObjectKankyo;

typedef struct ObjectKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1010];
} ObjectKankyo; // size = 0x1154

extern const ActorInit Object_Kankyo_InitVars;

#endif
