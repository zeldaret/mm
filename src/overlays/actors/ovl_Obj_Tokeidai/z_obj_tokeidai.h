#ifndef _Z_OBJ_TOKEIDAI_H_
#define _Z_OBJ_TOKEIDAI_H_

#include <global.h>

struct ObjTokeidai;

typedef struct ObjTokeidai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x34];
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif
