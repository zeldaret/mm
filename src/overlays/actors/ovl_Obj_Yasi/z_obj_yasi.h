#ifndef Z_OBJ_YASI_H
#define Z_OBJ_YASI_H

#include <global.h>

struct ObjYasi;

typedef struct ObjYasi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} ObjYasi; // size = 0x15C

extern const ActorInit Obj_Yasi_InitVars;

#endif // Z_OBJ_YASI_H
