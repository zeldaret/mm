#ifndef _Z_OBJ_BLOCKSTOP_H_
#define _Z_OBJ_BLOCKSTOP_H_

#include <global.h>

struct ObjBlockstop;

typedef struct ObjBlockstop {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjBlockstop; // size = 0x148

extern const ActorInit Obj_Blockstop_InitVars;

#endif
