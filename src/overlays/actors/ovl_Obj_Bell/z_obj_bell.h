#ifndef Z_OBJ_BELL_H
#define Z_OBJ_BELL_H

#include <global.h>

struct ObjBell;

typedef struct ObjBell {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xE4];
} ObjBell; // size = 0x228

extern const ActorInit Obj_Bell_InitVars;

#endif // Z_OBJ_BELL_H
