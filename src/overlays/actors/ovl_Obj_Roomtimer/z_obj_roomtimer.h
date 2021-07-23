#ifndef Z_OBJ_ROOMTIMER_H
#define Z_OBJ_ROOMTIMER_H

#include "global.h"

struct ObjRoomtimer;

typedef struct ObjRoomtimer {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ObjRoomtimer; // size = 0x14C

extern const ActorInit Obj_Roomtimer_InitVars;

#endif // Z_OBJ_ROOMTIMER_H
