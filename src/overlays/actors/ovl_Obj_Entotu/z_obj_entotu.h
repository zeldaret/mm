#ifndef _Z_OBJ_ENTOTU_H_
#define _Z_OBJ_ENTOTU_H_

#include <global.h>

struct ObjEntotu;

typedef struct ObjEntotu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x84];
} ObjEntotu; // size = 0x1C8

extern const ActorInit Obj_Entotu_InitVars;

#endif
