#ifndef _Z_OBJ_ICEBLOCK_H_
#define _Z_OBJ_ICEBLOCK_H_

#include <global.h>

struct ObjIceblock;

typedef struct ObjIceblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x174];
} ObjIceblock; // size = 0x2B8

extern const ActorInit Obj_Iceblock_InitVars;

#endif
