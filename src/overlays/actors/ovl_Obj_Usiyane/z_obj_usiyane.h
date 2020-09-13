#ifndef Z_OBJ_USIYANE_H
#define Z_OBJ_USIYANE_H

#include <global.h>

struct ObjUsiyane;

typedef struct ObjUsiyane {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x604];
} ObjUsiyane; // size = 0x748

extern const ActorInit Obj_Usiyane_InitVars;

#endif // Z_OBJ_USIYANE_H
