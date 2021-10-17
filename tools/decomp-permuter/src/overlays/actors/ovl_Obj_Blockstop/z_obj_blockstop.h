#ifndef Z_OBJ_BLOCKSTOP_H
#define Z_OBJ_BLOCKSTOP_H

#include <global.h>

struct ObjBlockstop;

typedef struct ObjBlockstop {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjBlockstop; // size = 0x148

extern const ActorInit Obj_Blockstop_InitVars;

#endif // Z_OBJ_BLOCKSTOP_H
