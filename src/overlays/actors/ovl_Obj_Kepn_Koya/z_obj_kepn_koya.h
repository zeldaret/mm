#ifndef Z_OBJ_KEPN_KOYA_H
#define Z_OBJ_KEPN_KOYA_H

#include <global.h>

struct ObjKepnKoya;

typedef struct ObjKepnKoya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} ObjKepnKoya; // size = 0x160

extern const ActorInit Obj_Kepn_Koya_InitVars;

#endif // Z_OBJ_KEPN_KOYA_H
