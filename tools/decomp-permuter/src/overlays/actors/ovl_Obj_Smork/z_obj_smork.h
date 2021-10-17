#ifndef Z_OBJ_SMORK_H
#define Z_OBJ_SMORK_H

#include <global.h>

struct ObjSmork;

typedef struct ObjSmork {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x84];
} ObjSmork; // size = 0x1C8

extern const ActorInit Obj_Smork_InitVars;

#endif // Z_OBJ_SMORK_H
