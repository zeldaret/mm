#ifndef _Z_OBJ_DORA_H_
#define _Z_OBJ_DORA_H_

#include <global.h>

struct ObjDora;

typedef struct ObjDora {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x268];
} ObjDora; // size = 0x3AC

extern const ActorInit Obj_Dora_InitVars;

#endif
