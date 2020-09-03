#ifndef Z_OBJ_HSSTUMP_H
#define Z_OBJ_HSSTUMP_H

#include <global.h>

struct ObjHsStump;

typedef struct ObjHsStump {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} ObjHsStump; // size = 0x16C

extern const ActorInit Obj_HsStump_InitVars;

#endif // Z_OBJ_HSSTUMP_H
