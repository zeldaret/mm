#ifndef _Z_OBJ_SMORK_H_
#define _Z_OBJ_SMORK_H_

#include <global.h>

struct ObjSmork;

typedef struct ObjSmork {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x84];
} ObjSmork; // size = 0x1C8

extern const ActorInit Obj_Smork_InitVars;

#endif
